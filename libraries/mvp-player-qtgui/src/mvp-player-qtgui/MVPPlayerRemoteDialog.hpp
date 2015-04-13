#ifndef _MVPPLAYERREMOTEDIALOG_HPP
#define	_MVPPLAYERREMOTEDIALOG_HPP

#include "ui_MVPPlayerRemoteDialog.hpp"

#include "MVPPlayerDialog.hpp"

#include <QtGui/QDropEvent>
#include <QtGui/QDragMoveEvent>
#include <QtCore/QMimeData>

#include <boost/signals2.hpp>
#include <boost/filesystem/path.hpp>
#include <string>

namespace mvpplayer
{
namespace gui
{
namespace qt
{

/**
 * @brief mvp-player qt dialog
 */
class MVPPlayerRemoteDialog : public MVPPlayerDialog
{
    Q_OBJECT
private:
    typedef MVPPlayerDialog Parent;
public:
    MVPPlayerRemoteDialog( QWidget *parent = NULL );
    virtual ~MVPPlayerRemoteDialog();

    void displayError( const std::string & msg )
    { QMetaObject::invokeMethod( this, "slotDisplayError", Qt::BlockingQueuedConnection, Q_ARG( QString, msg.c_str() ) ); }

    boost::filesystem::path openFile( const std::string & title, const std::string & extensions );

    /**
     * In the following sections, we use invokeMethod because of asynchronous
     * calls that might come from other threads.
     */
    inline void setIconStop()
    { QMetaObject::invokeMethod( this, "slotSetIconStop", Qt::BlockingQueuedConnection ); }

    inline void setIconPlay()
    { QMetaObject::invokeMethod( this, "slotSetIconPlay", Qt::BlockingQueuedConnection ); }

    inline void setCurrentTrack( const boost::filesystem::path & filename )
    { QMetaObject::invokeMethod( widget.lblCurrentTrack, "setText", Qt::BlockingQueuedConnection, Q_ARG( QString, QString::fromStdString( filename.filename().string() ) ) ); }

    inline void setPlaylistItemIndex( const int row )
    { QMetaObject::invokeMethod( this, "slotSetPlaylistItemIndex", Qt::BlockingQueuedConnection, Q_ARG( int, row ) ); }

    void openedPlaylist( const std::vector<m3uParser::PlaylistItem> & playlistItems );

    inline void clearPlaylist()
    { QMetaObject::invokeMethod( this, "slotClearPlaylist", Qt::BlockingQueuedConnection ); }

    inline void addTrack( const boost::filesystem::path & filename )
    { QMetaObject::invokeMethod( this, "slotAddTrack", Qt::BlockingQueuedConnection, Q_ARG( QString, QString::fromStdString( filename.filename().string() ) ) ); }


private:
    void dropEvent( QDropEvent *de );
    void dragEnterEvent( QDragEnterEvent *event );
    void dragMoveEvent( QDragMoveEvent *event );
    void dragLeaveEvent( QDragLeaveEvent *event );

private Q_SLOTS:
    void connectDisconnectClient( const bool start = true );
    void playPlaylistItemAtIndex( const int playlistIndex );
    void slotViewHitPlayStopBtn();
    void slotViewHitMute( const bool mute );
    void slotSetPlaylistItemIndex( const int row );
    void slotSetIconStop();
    void slotSetIconPlay();
    QString slotOpenFile( const QString & title, const QString & extensions );
    void slotDisplayError( const QString & msg );
    void slotOpenedPlaylist( const QStringList & filenames );
    void slotClearPlaylist();
    void slotAddTrack( const QString & filename );

private:
    Ui::MVPPlayerRemoteDialog widget;

public:
    boost::signals2::signal<void(const bool)> signalViewMute;                   ///< Mute sound player
    boost::signals2::signal<void()> signalViewConnect;      ///< Signal connect
    boost::signals2::signal<void()> signalViewDisconnect;   ///< Signal disconnect
};

}
}
}

#endif
