#ifndef _GUI_MVPPLAYERDIALOG_HPP_
#define	_GUI_MVPPLAYERDIALOG_HPP_

#include <mvp-player-gui/IMVPPlayerDialog.hpp>

#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QToolButton>

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

protected:
    template<class Dlg>
    void initDialog( Dlg & widget )
    {
        setAcceptDrops(true);

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
            if ( buttonName == "Play" )
            {
                _btnPlayPause = button;
            }
            else if ( buttonName == "Previous" )
            {
                _btnPrevious = button;
            }
            else if ( buttonName == "Next" )
            {
                _btnNext = button;
            }
        }

        // Center window
    #ifndef ANDROID
        move( QApplication::desktop()->screen()->rect().center() - rect().center() );
    #else
        showMaximized();
    #endif
    }

protected:
    QToolButton *_btnPlayPause;
    QToolButton *_btnPrevious;
    QToolButton *_btnNext;
};

}
}
}

#endif
