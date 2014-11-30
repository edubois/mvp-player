#ifndef _MVPPLAYERDIALOG_HPP
#define	_MVPPLAYERDIALOG_HPP

#include "ui_MVPPlayerDialog.hpp"

#include <mvp-player-gui/IMVPPlayerDialog.hpp>

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

    inline void setCurrentTrack( const boost::filesystem::path & filename )
    { widget.lblCurrentTrack->setText( QString::fromStdString( filename.string() ) ); }

    inline void setIconStop()
    { widget.btnPlay->setText( kStopCaption.c_str() ); }

    inline void setIconPlay()
    { widget.btnPlay->setText( kPlayCaption.c_str() ); }

private Q_SLOTS:
    void slotViewHitPlayStopBtn();

private:
    Ui::MVPPlayerDialog widget;
};

}
}
}

#endif
