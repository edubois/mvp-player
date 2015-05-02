#ifndef _GUI_MVPPLAYERDIALOG_HPP_
#define	_GUI_MVPPLAYERDIALOG_HPP_

#include "dialogInit.hpp"

#include <mvp-player-core/MVPPlayerPresenter.hpp>
#include <mvp-player-qtgui/dialogInit.hpp>

#include <boost/optional.hpp>

namespace mvpplayer
{
namespace gui
{
namespace qt
{

class MVPPlayerDialog : public QDialog, public IMVPPlayerDialog
{
    Q_OBJECT
private:
    typedef MVPPlayerDialog This;
protected:
    friend void initDialog<This>( This & dlg );

public:
    MVPPlayerDialog( QWidget *parent = NULL );
    virtual ~MVPPlayerDialog();

    inline void setTrackPosition( const std::size_t positionInMS, const std::size_t trackLength ) override
    { QMetaObject::invokeMethod( this, "slotSetTrackPosition", Qt::BlockingQueuedConnection, Q_ARG( int, positionInMS ), Q_ARG( int, trackLength ) ); }

    void displayError( const std::string & msg )
    { QMetaObject::invokeMethod( this, "slotDisplayError", Qt::BlockingQueuedConnection, Q_ARG( QString, msg.c_str() ) ); }

    boost::optional<boost::filesystem::path> openFile( const std::string & title, const logic::EFileDialogMode mode, const std::string & extensions );

protected:
    void setButtonChecked( const std::string & buttonName, const bool checked );

protected Q_SLOTS:
    QString slotOpenFile( const QString & title, const QString & extensions, const logic::EFileDialogMode mode );
    void slotDisplayError( const QString & msg );
    void slotViewHitButton();
    void changeTrackPosition( const int positionInPercent );
    void changeVolume( const int volume );

protected:
    std::size_t _currentTrackLength = 0;
    QToolButton *_btnPlayPause;
    QToolButton *_btnPrevious;
    QToolButton *_btnNext;
    std::map<std::string, QToolButton*> _playerButtonsWidgets;
};

}
}
}

#endif
