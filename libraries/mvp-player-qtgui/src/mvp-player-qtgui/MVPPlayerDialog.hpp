#ifndef _GUI_MVPPLAYERDIALOG_HPP_
#define	_GUI_MVPPLAYERDIALOG_HPP_

#include <mvp-player-gui/IMVPPlayerDialog.hpp>
#include <mvp-player-core/MVPPlayerPresenter.hpp>

#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QToolButton>

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
public:
    MVPPlayerDialog( QWidget *parent = NULL );
    virtual ~MVPPlayerDialog();

    inline void setTrackPosition( const std::size_t positionInMS, const std::size_t trackLength ) override
    { QMetaObject::invokeMethod( this, "slotSetTrackPosition", Qt::BlockingQueuedConnection, Q_ARG( int, positionInMS ), Q_ARG( int, trackLength ) ); }

    void displayError( const std::string & msg )
    { QMetaObject::invokeMethod( this, "slotDisplayError", Qt::BlockingQueuedConnection, Q_ARG( QString, msg.c_str() ) ); }

    boost::optional<boost::filesystem::path> openFile( const std::string & title, const logic::EFileDialogMode mode, const std::string & extensions );

protected:
    template<class Dlg>
    void initDialog( Dlg & widget )
    {
#ifndef ANDROID
        setAcceptDrops(true);
#endif

        // Transform descriptor into real player buttons
        for( const ButtonDescriptor & desc: _buttonsBar.buttons() )
        {
            // Checkable button
            QToolButton * button = new QToolButton( this );
            widget.layoutButtonsBar->addWidget( button );
            if ( desc.property<std::string>( "captionPushed" ).size() )
            {
                button->setCheckable( true );
            }

            button->setText( desc.property<std::string>( "captionNormal" ).c_str() );
            button->setStyleSheet( desc.property<std::string>( "styleSheet" ).c_str() );
            // Connect the right signals according to buttons' names
            const std::string buttonName = desc.property<std::string>( "name" );
            button->setObjectName( buttonName.c_str() );
            _playerButtonsWidgets[ buttonName ] = button;

            if ( buttonName == "Play" )
            {
                _btnPlayPause = button;
            }
            else
            {
                connect( button, SIGNAL( clicked(bool) ), this, SLOT( slotViewHitButton() ) );
            }

            if ( buttonName == "Previous" )
            {
                _btnPrevious = button;
            }
            else if ( buttonName == "Next" )
            {
                _btnNext = button;
            }
        }

        connect( widget.sliderPosition, SIGNAL( valueChanged( int ) ), this, SLOT( changeTrackPosition( int ) ) );

        // Center window
    #ifndef ANDROID
        move( QApplication::desktop()->screen()->rect().center() - rect().center() );
    #else
        showMaximized();
    #endif
    }
    
    void setButtonChecked( const std::string & buttonName, const bool checked );

protected Q_SLOTS:
    QString slotOpenFile( const QString & title, const QString & extensions, const logic::EFileDialogMode mode );
    void slotDisplayError( const QString & msg );
    void slotViewHitButton();
    void changeTrackPosition( const int positionInPercent );

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
