#ifndef _MVPPLAYERDIALOG_HPP
#define	_MVPPLAYERDIALOG_HPP

#include "ui_MVPPlayerDialog.hpp"

#include <mvp-player-gui/IMVPPlayerDialog.hpp>

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
class MVPPlayerDialog : public QDialog, public IMVPPlayerDialog
{
    Q_OBJECT
public:
    MVPPlayerDialog( QWidget *parent = NULL );
    virtual ~MVPPlayerDialog();

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
    { QMetaObject::invokeMethod( widget.lblCurrentTrack, "setText", Qt::BlockingQueuedConnection, Q_ARG( QString, QString::fromStdString( filename.string() ) ) ); }

    inline void setPlaylistItemIndex( const int row )
    { QMetaObject::invokeMethod( this, "slotSetPlaylistItemIndex", Qt::BlockingQueuedConnection, Q_ARG( int, row ) ); }

private:
    void dropEvent( QDropEvent *de );
    void dragEnterEvent( QDragEnterEvent *event );
    void dragMoveEvent( QDragMoveEvent *event );
    void dragLeaveEvent( QDragLeaveEvent *event );

private Q_SLOTS:
    void playPlaylistItemAtIndex( const int playlistIndex );
    void slotViewHitPlayStopBtn();
    void slotViewHitPreviousBtn();
    void slotViewHitNextBtn();
    void slotSetPlaylistItemIndex( const int row );
    void slotSetIconStop()
    { widget.btnPlay->setText( kStopCaption.c_str() ); }
    void slotSetIconPlay()
    { widget.btnPlay->setText( kPlayCaption.c_str() ); }
    QString slotOpenFile( const QString & title, const QString & extensions );
    void slotDisplayError( const QString & msg );

private:
    Ui::MVPPlayerDialog widget;
};

}
}
}

#endif
