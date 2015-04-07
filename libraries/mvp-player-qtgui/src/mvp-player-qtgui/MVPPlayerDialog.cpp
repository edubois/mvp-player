#include "MVPPlayerDialog.hpp"
#include "MVPPlayerSettingsDialog.hpp"

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QDesktopWidget>

#include <iostream>

namespace mvpplayer
{
namespace gui
{
namespace qt
{

MVPPlayerDialog::MVPPlayerDialog( QWidget *parent )
: QDialog( parent )
{
    widget.setupUi(this);
    
    setAcceptDrops(true);

    connect( widget.btnPlayStop, SIGNAL( clicked(bool) ), this, SLOT( slotViewHitPlayStopBtn() ) );
    connect( widget.btnPrevious, SIGNAL( clicked(bool) ), this, SLOT( slotViewHitPreviousBtn() ) );
    connect( widget.btnNext, SIGNAL( clicked(bool) ), this, SLOT( slotViewHitNextBtn() ) );
    connect( widget.btnServer, SIGNAL( clicked(bool) ), this, SLOT( startStopServer( const bool ) ) );
    connect( widget.playlist, SIGNAL( currentRowChanged(int) ), this, SLOT( playPlaylistItemAtIndex(int) ) );
    connect( widget.btnSettings, SIGNAL( clicked(bool) ), this, SLOT( editSettings() ) );

    // Center window
#ifndef ANDROID
    move( QApplication::desktop()->screen()->rect().center() - rect().center() );
#else
    showMaximized();
#endif
}

MVPPlayerDialog::~MVPPlayerDialog()
{
}

boost::filesystem::path MVPPlayerDialog::openFile( const std::string & title, const std::string & extensions )
{
    QString result;
    QMetaObject::invokeMethod( this, "slotOpenFile", Qt::BlockingQueuedConnection, Q_RETURN_ARG( QString, result ), Q_ARG( QString, QString::fromStdString( title ) ), Q_ARG( QString, QString::fromStdString( extensions ) ) );
    return result.toStdString();
}

void MVPPlayerDialog::slotViewHitPlayStopBtn()
{
    if ( widget.btnPlayStop->text().toStdString() == kStopCaption )
    {
        signalViewHitStop();
    }
    else
    {
        if ( widget.playlist->count() )
        {
            if ( widget.playlist->currentRow() >= 0 )
            {
                signalViewHitPlaylistItem( widget.playlist->currentRow() );
            }
            else
            {
                signalViewStartPlaylist();
            }
        }
        else
        {
            signalViewHitPlay( std::string() );
        }
    }
}

void MVPPlayerDialog::slotViewHitPreviousBtn()
{
    signalViewHitPrevious();
}

void MVPPlayerDialog::slotViewHitNextBtn()
{
    signalViewHitNext();
}

void MVPPlayerDialog::playPlaylistItemAtIndex( const int playlistIndex )
{
    signalViewHitPlaylistItem( playlistIndex );
}

void MVPPlayerDialog::openedPlaylist( const std::vector<m3uParser::PlaylistItem> & playlistItems )
{
    QStringList filenames;
    for( const m3uParser::PlaylistItem & item: playlistItems )
    {
        filenames.append( item.filename.string().c_str() );
    }
    QMetaObject::invokeMethod( this, "slotOpenedPlaylist", Qt::BlockingQueuedConnection, Q_ARG( QStringList, filenames ) );
}

void MVPPlayerDialog::dropEvent( QDropEvent *de )
{
    // Unpack dropped data and handle it
    if ( de->mimeData()->hasUrls() )
    {
        QList<QUrl> urlList = de->mimeData()->urls();
        if ( urlList.size() && urlList.first().path().endsWith( ".m3u" ) )
        {
            signalSequencial(
                [this, &urlList]()
                {
                    signalViewClearPlaylist();
                    signalViewHitPlay( urlList.first().path().toStdString() );
                }
            );
        }
        else
        {
            signalSequencial(
                [this, &urlList](){
                    signalViewHitStop();
                    signalViewClearPlaylist();
                    for ( int i = 0; i < urlList.size(); ++i )
                    {
                        const QString url = urlList.at( i ).path();
                        signalViewAddTrack( url.toStdString() );
                    }
                    if ( urlList.size() )
                    {
                        signalViewStartPlaylist();
                    }
                }
            );
        }
    }
}

void MVPPlayerDialog::editSettings()
{
    MVPPlayerSettingsDialog settingsDialog( this );
    if ( settingsDialog.exec() )
    {
        
    }
}

void MVPPlayerDialog::dragEnterEvent( QDragEnterEvent *event )
{
    event->acceptProposedAction();
}

void MVPPlayerDialog::dragMoveEvent( QDragMoveEvent *event )
{
    event->acceptProposedAction();
}

void MVPPlayerDialog::dragLeaveEvent( QDragLeaveEvent *event )
{
    event->accept();
}

void MVPPlayerDialog::startStopServer( const bool start )
{
    if ( start )
    {
        signalViewStartServer();
    }
    else
    {
        signalViewStopServer();
    }
}

void MVPPlayerDialog::slotSetIconStop()
{
    widget.btnPlayStop->setText( kStopCaption.c_str() );
    widget.btnPlayStop->setIcon( QIcon( ":/mvpplayer/action/stop.png" ) );
}

void MVPPlayerDialog::slotSetIconPlay()
{
    widget.btnPlayStop->setText( kPlayCaption.c_str() );
    widget.btnPlayStop->setIcon( QIcon( ":/mvpplayer/action/play.png" ) );
}

void MVPPlayerDialog::slotSetPlaylistItemIndex( const int row )
{
    widget.playlist->blockSignals( true ); // Don't forget to put this to avoid dead locks

    if ( row == -1 )
    {
        widget.playlist->selectionModel()->clearSelection();
    }
    else if ( row < widget.playlist->count() )
    {
        widget.playlist->setCurrentRow( row );
    }

    widget.playlist->blockSignals( false );
}

QString MVPPlayerDialog::slotOpenFile( const QString & title, const QString & extensions )
{
    return QFileDialog::getOpenFileName( QApplication::activeWindow(), title, QDir::currentPath(), extensions );
}

void MVPPlayerDialog::slotOpenedPlaylist( const QStringList & filenames )
{
    widget.playlist->blockSignals( true ); // Don't forget to put this to avoid dead locks
    widget.playlist->clear();
    widget.playlist->addItems( filenames );
    widget.playlist->blockSignals( false );
    signalViewStartPlaylist();
}

void MVPPlayerDialog::slotClearPlaylist()
{
    widget.playlist->blockSignals( true ); // Don't forget to put this to avoid dead locks
    widget.playlist->clear();
    widget.playlist->blockSignals( false );
}

void MVPPlayerDialog::slotAddTrack( const QString & filename )
{
    widget.playlist->blockSignals( true ); // Don't forget to put this to avoid dead locks
    widget.playlist->addItem( filename );
    widget.playlist->blockSignals( false );
}

void MVPPlayerDialog::slotDisplayError( const QString & msg )
{
    QMessageBox::critical( QApplication::activeWindow(), QObject::tr( "Error!" ), msg, QMessageBox::Ok | QMessageBox::Default);
}

}
}
}
