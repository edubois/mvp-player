#ifndef _MVPPLAYERDIALOG_HPP
#define	_MVPPLAYERDIALOG_HPP

#include "ui_MVPPlayerDialog.hpp"

#include <boost/signals2.hpp>
#include <boost/filesystem/path.hpp>
#include <string>

namespace mvpplayer
{
namespace gui
{
namespace qt
{
static const QString kStopCaption( "[*]" );
static const QString kPlayCaption( "|>" );

/**
 * @brief mvp-player dialog
 */
class MVPPlayerDialog : public QDialog
{
    Q_OBJECT
public:
    MVPPlayerDialog( QWidget *parent = NULL );
    virtual ~MVPPlayerDialog();
    
    inline void setCurrentTrack( const boost::filesystem::path & filename )
    { widget.lblCurrentTrack->setText( QString::fromStdString( filename.string() ) ); }

    inline void setIconStop()
    { widget.btnPlay->setText( kStopCaption ); }
    
    inline void setIconPlay()
    { widget.btnPlay->setText( kPlayCaption ); }

private Q_SLOTS:
    void slotViewHitPlayStopBtn();

public:
    boost::signals2::signal<void( const std::string& )> signalViewHitPlay; ///< Signals that user hit play button
    boost::signals2::signal<void()> signalViewHitStop; ///< Signals that user hit stop button

private:
    Ui::MVPPlayerDialog widget;
};

}
}
}

#endif
