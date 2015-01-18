#include "MVPPlayerRemoteDialog.hpp"

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

#include <iostream>

namespace mvpplayer
{
namespace gui
{
namespace qt
{

MVPPlayerRemoteDialog::MVPPlayerRemoteDialog( QWidget *parent )
: QDialog( parent )
{
    widget.setupUi(this);
    
    setAcceptDrops(true);

    connect( widget.cbMute, SIGNAL( clicked(bool) ), this, SLOT( slotViewHitMute(const bool) ) );
    connect( widget.btnPlayStop, SIGNAL( clicked(bool) ), this, SLOT( slotViewHitPlayStopBtn() ) );
    connect( widget.btnPrevious, SIGNAL( clicked(bool) ), this, SLOT( slotViewHitPreviousBtn() ) );
    connect( widget.btnNext, SIGNAL( clicked(bool) ), this, SLOT( slotViewHitNextBtn() ) );
    connect( widget.btnServer, SIGNAL( clicked(bool) ), this, SLOT( connectDisconnectClient( const bool ) ) );
    connect( widget.playlist, SIGNAL( currentRowChanged(int) ), this, SLOT( playPlaylistItemAtIndex(int) ) );
}

MVPPlayerRemoteDialog::~MVPPlayerRemoteDialog()
{
}

boost::filesystem::path MVPPlayerRemoteDialog::openFile( const std::string & title, const std::string & extensions )
{
    QString result;
    QMetaObject::invokeMethod( this, "slotOpenFile", Qt::BlockingQueuedConnection, Q_RETURN_ARG( QString, result ), Q_ARG( QString, QString::fromStdString( title ) ), Q_ARG( QString, QString::fromStdString( extensions ) ) );
    return result.toStdString();
}

void MVPPlayerRemoteDialog::slotViewHitPlayStopBtn()
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

void MVPPlayerRemoteDialog::slotViewHitPreviousBtn()
{
    signalViewHitPrevious();
}

void MVPPlayerRemoteDialog::slotViewHitNextBtn()
{
    signalViewHitNext();
}

void MVPPlayerRemoteDialog::playPlaylistItemAtIndex( const int playlistIndex )
{
    signalViewHitPlaylistItem( playlistIndex );
}

void MVPPlayerRemoteDialog::openedPlaylist( const std::vector<m3uParser::PlaylistItem> & playlistItems )
{
    QStringList filenames;
    for( const m3uParser::PlaylistItem & item: playlistItems )
    {
        filenames.append( item.filename.string().c_str() );
    }
    QMetaObject::invokeMethod( this, "slotOpenedPlaylist", Qt::BlockingQueuedConnection, Q_ARG( QStringList, filenames ) );
}

void MVPPlayerRemoteDialog::dropEvent( QDropEvent *de )
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

void MVPPlayerRemoteDialog::dragEnterEvent( QDragEnterEvent *event )
{
    event->acceptProposedAction();
}

void MVPPlayerRemoteDialog::dragMoveEvent( QDragMoveEvent *event )
{
    event->acceptProposedAction();
}

void MVPPlayerRemoteDialog::dragLeaveEvent( QDragLeaveEvent *event )
{
    event->accept();
}

void MVPPlayerRemoteDialog::connectDisconnectClient( const bool start )
{
    if ( start )
    {
        signalViewConnect();
    }
    else
    {
        signalViewDisconnect();
    }
}

void MVPPlayerRemoteDialog::slotViewHitMute( const bool checked )
{
    signalViewMute( checked );
}

void MVPPlayerRemoteDialog::slotSetIconStop()
{
    widget.btnPlayStop->setText( kStopCaption.c_str() );
    widget.btnPlayStop->setIcon( QIcon( ":/mvpplayer/action/stop.png" ) );
}

void MVPPlayerRemoteDialog::slotSetIconPlay()
{
    widget.btnPlayStop->setText( kPlayCaption.c_str() );
    widget.btnPlayStop->setIcon( QIcon( ":/mvpplayer/action/play.png" ) );
}

void MVPPlayerRemoteDialog::slotSetPlaylistItemIndex( const int row )
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

QString MVPPlayerRemoteDialog::slotOpenFile( const QString & title, const QString & extensions )
{
    return QFileDialog::getOpenFileName( QApplication::activeWindow(), title, QDir::currentPath(), extensions );
}

void MVPPlayerRemoteDialog::slotOpenedPlaylist( const QStringList & filenames )
{
    widget.playlist->blockSignals( true ); // Don't forget to put this to avoid dead locks
    widget.playlist->clear();
    widget.playlist->addItems( filenames );
    widget.playlist->blockSignals( false );
    signalViewStartPlaylist();
}

void MVPPlayerRemoteDialog::slotClearPlaylist()
{
    widget.playlist->blockSignals( true ); // Don't forget to put this to avoid dead locks
    widget.playlist->clear();
    widget.playlist->blockSignals( false );
}

void MVPPlayerRemoteDialog::slotAddTrack( const QString & filename )
{
    widget.playlist->blockSignals( true ); // Don't forget to put this to avoid dead locks
    widget.playlist->addItem( filename );
    widget.playlist->blockSignals( false );
}

void MVPPlayerRemoteDialog::slotDisplayError( const QString & msg )
{
    QMessageBox::critical( QApplication::activeWindow(), QObject::tr( "Error!" ), msg, QMessageBox::Ok | QMessageBox::Default);
}

}
}
}
