#include "MVPPlayerLocalDialog.hpp"
#include <mvp-player-core/trackTools.hpp>

#include <QtWidgets/QDesktopWidget>

namespace mvpplayer
{
namespace gui
{
namespace qt
{

MVPPlayerLocalDialog::MVPPlayerLocalDialog( QWidget *parent )
: Parent( parent )
{
    widget.setupUi(this);

    initDialog( widget );
    connect( _btnPlayPause, SIGNAL( toggled(bool) ), this, SLOT( slotViewHitPlayStopBtn() ) );
    connect( widget.btnServer, SIGNAL( toggled(bool) ), this, SLOT( startStopServer( const bool ) ) );
    connect( widget.playlist, SIGNAL( currentRowChanged(int) ), this, SLOT( playPlaylistItemAtIndex(int) ) );
    connect( widget.btnSettings, SIGNAL( released() ), this, SLOT( editSettings() ) );
}

MVPPlayerLocalDialog::~MVPPlayerLocalDialog()
{
}

void MVPPlayerLocalDialog::slotViewHitPlayStopBtn()
{
    if ( _btnPlayPause->isChecked() == false )
    {
        signalViewHitButton( "Stop", true );
    }
    else
    {
        signalViewHitButton( "Play", true );
    }
}

void MVPPlayerLocalDialog::playPlaylistItemAtIndex( const int playlistIndex )
{
    signalViewHitPlaylistItem( playlistIndex );
}

void MVPPlayerLocalDialog::openedPlaylist( const std::vector<m3uParser::PlaylistItem> & playlistItems )
{
    QStringList filenames;
    for( const m3uParser::PlaylistItem & item: playlistItems )
    {
        filenames.append( item.filename.string().c_str() );
    }
    QMetaObject::invokeMethod( this, "slotOpenedPlaylist", Qt::BlockingQueuedConnection, Q_ARG( QStringList, filenames ) );
}

void MVPPlayerLocalDialog::dropEvent( QDropEvent *de )
{
    // Unpack dropped data and handle it
    if ( de->mimeData()->hasUrls() )
    {
        QList<QUrl> urlList = de->mimeData()->urls();
        if ( urlList.size() && urlList.first().path().endsWith( ".m3u" ) )
        {
            signalViewAppendPlaylistTracks( urlList.first().path().toStdString() );
        }
        else
        {
            for ( int i = 0; i < urlList.size(); ++i )
            {
                const QString url = urlList.at( i ).path();
                signalViewAddTrack( url.toStdString() );
            }
        }
    }
}

void MVPPlayerLocalDialog::editSettings()
{
    signalViewHitEditSettings();
}

void MVPPlayerLocalDialog::dragEnterEvent( QDragEnterEvent *event )
{
    event->acceptProposedAction();
}

void MVPPlayerLocalDialog::dragMoveEvent( QDragMoveEvent *event )
{
    event->acceptProposedAction();
}

void MVPPlayerLocalDialog::dragLeaveEvent( QDragLeaveEvent *event )
{
    event->accept();
}

void MVPPlayerLocalDialog::startStopServer( const bool start )
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

void MVPPlayerLocalDialog::slotSetIconStop()
{
    _btnPlayPause->setChecked( true );
}

void MVPPlayerLocalDialog::slotSetIconPlay()
{
    _btnPlayPause->setChecked( false );
}

void MVPPlayerLocalDialog::slotSetPlaylistItemIndex( const int row )
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

void MVPPlayerLocalDialog::slotOpenedPlaylist( const QStringList & filenames )
{
    widget.playlist->blockSignals( true ); // Don't forget to put this to avoid dead locks
    widget.playlist->clear();
    widget.playlist->addItems( filenames );
    widget.playlist->blockSignals( false );
    signalViewStartPlaylist();
}

void MVPPlayerLocalDialog::slotClearPlaylist()
{
    widget.playlist->blockSignals( true ); // Don't forget to put this to avoid dead locks
    widget.playlist->clear();
    widget.playlist->blockSignals( false );
}

void MVPPlayerLocalDialog::slotAddTrack( const QString & filename )
{
    widget.playlist->blockSignals( true ); // Don't forget to put this to avoid dead locks
    widget.playlist->addItem( filename );
    widget.playlist->blockSignals( false );
}

void MVPPlayerLocalDialog::slotSetTrackLength( const std::size_t lengthInMS )
{
    widget.lblTrackLength->setText( QString::fromStdString( trackLengthToString( lengthInMS ) ) );
}

void MVPPlayerLocalDialog::slotSetTrackPosition( const int positionInMS, const int trackLength )
{
    widget.sliderPosition->blockSignals( true ); // Don't forget to put this to avoid dead locks
    widget.sliderPosition->setValue( 100 * positionInMS / trackLength );
    widget.sliderPosition->blockSignals( false );
}

}
}
}
