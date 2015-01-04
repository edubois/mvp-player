#include "MVPPlayerDialog.hpp"

#include <QtWidgets/QFileDialog>

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

    connect( widget.btnPlay, SIGNAL( clicked(bool) ), this, SLOT( slotViewHitPlayStopBtn() ) );
    connect( widget.btnPrevious, SIGNAL( clicked(bool) ), this, SLOT( slotViewHitPreviousBtn() ) );
    connect( widget.btnNext, SIGNAL( clicked(bool) ), this, SLOT( slotViewHitNextBtn() ) );
    connect( widget.playlist, SIGNAL( currentRowChanged(int) ), this, SLOT( playPlaylistItemAtIndex(int) ) );
}

MVPPlayerDialog::~MVPPlayerDialog()
{
}

void MVPPlayerDialog::slotViewHitPlayStopBtn()
{
    if ( widget.btnPlay->text().toStdString() == kStopCaption )
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

void MVPPlayerDialog::dropEvent( QDropEvent *de )
{
    // Unpack dropped data and handle it
    if ( de->mimeData()->hasUrls() )
    {
        QList<QUrl> urlList = de->mimeData()->urls();
        widget.playlist->clear();
        signalViewClearPlaylist();
        for ( int i = 0; i < urlList.size(); ++i )
        {
            const QString url = urlList.at( i ).path();
            widget.playlist->addItem( url );
            signalViewAddTrack( url.toStdString() );
        }
        if ( urlList.size() )
        {
            signalViewStartPlaylist();
        }
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

void MVPPlayerDialog::setCurrentTrack( const boost::filesystem::path & filename )
{
    widget.lblCurrentTrack->setText( QString::fromStdString( filename.string() ) );
}

void MVPPlayerDialog::setPlaylistItemIndex( const int row )
{
    if ( row == -1 )
    {
        widget.playlist->selectionModel()->clearSelection();
    }
    else if ( row < widget.playlist->count() )
    {
        widget.playlist->setCurrentRow( row );
    }
}

}
}
}
