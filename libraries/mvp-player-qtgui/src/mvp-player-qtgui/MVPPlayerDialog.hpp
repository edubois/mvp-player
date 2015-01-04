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

    void setCurrentTrack( const boost::filesystem::path & filename );

    void setPlaylistItemIndex( const int row );

    inline void setIconStop()
    { widget.btnPlay->setText( kStopCaption.c_str() ); }

    inline void setIconPlay()
    { widget.btnPlay->setText( kPlayCaption.c_str() ); }

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

private:
    Ui::MVPPlayerDialog widget;
};

}
}
}

#endif
