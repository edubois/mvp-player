#ifndef _MVPPLAYER_QTGUI_DIALOGINIT_HPP_
#define	_MVPPLAYER_QTGUI_DIALOGINIT_HPP_

#include <mvp-player-gui/IMVPPlayerDialog.hpp>

#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QDesktopWidget>

namespace mvpplayer
{
namespace gui
{
namespace qt
{

/**
 * @brief this function factorize code for player qt GUI
 *        This is not very clean, but Qt is not well done for genericity
 * @param dlg dialog (non pointer)
 */
template<class Dlg>
void initDialog( Dlg & dlg )
{
#ifndef ANDROID
    dlg.setAcceptDrops(true);
#endif

    // Transform descriptor into real player buttons
    for( const ButtonDescriptor & desc: dlg.buttonsBar().buttons() )
    {
        // Checkable button
        QToolButton * button = new QToolButton( &dlg );
        dlg.widget.layoutButtonsBar->addWidget( button );
        if ( desc.property<std::string>( "captionPushed" ).size() )
        {
            button->setCheckable( true );
        }

        button->setText( desc.property<std::string>( "captionNormal" ).c_str() );
        button->setStyleSheet( desc.property<std::string>( "styleSheet" ).c_str() );
        // Connect the right signals according to buttons' names
        const std::string buttonName = desc.property<std::string>( "name" );
        button->setObjectName( buttonName.c_str() );
        dlg._playerButtonsWidgets[ buttonName ] = button;

        if ( buttonName == "Play" )
        {
            dlg._btnPlayPause = button;
        }
        else
        {
            QObject::connect( button, SIGNAL( clicked(bool) ), &dlg, SLOT( slotViewHitButton() ) );
        }

        if ( buttonName == "Previous" )
        {
            dlg._btnPrevious = button;
        }
        else if ( buttonName == "Next" )
        {
            dlg._btnNext = button;
        }
    }

    QObject::connect( dlg.widget.sliderPosition, SIGNAL( valueChanged( int ) ), &dlg, SLOT( changeTrackPosition( int ) ) );

    // Center window
#ifndef ANDROID
    dlg.move( QApplication::desktop()->screen()->rect().center() - dlg.rect().center() );
#else
    dlg.showMaximized();
#endif
}

}
}
}

#endif
