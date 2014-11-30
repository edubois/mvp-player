#include "MVPPlayerDialog.hpp"
#include "winFun.hpp"

#include <iostream>

namespace mvpplayer
{
namespace gui
{
namespace ncurses
{

namespace
{

void btnPlayPressed( CDKBUTTON *button )
{
    std::cout << "pressed" << std::endl;
    exit(1);
}

int actionBtnPlay( EObjectType cdktype, void *object, void *clientData, chtype key)
{
    CDKBUTTON * button = (CDKBUTTON *)object;
    MVPPlayerDialog * dlg = static_cast<MVPPlayerDialog *>( clientData );
    dlg->signalViewHitPlay( std::string() );
    std::cout << "Play!" << std::endl;
    exit(1);
    return 0;
}

}
    
MVPPlayerDialog::MVPPlayerDialog( CDKSCREEN *cdkScreen, const int width, const int height, const int x, const int y )
: _cdkScreen( cdkScreen )
{
    init_pair( kColorMessage, COLOR_WHITE, COLOR_BLUE );
    char* msg[1] = { "Music player" };
    char* buttons[10];
    buttons[0] = "<<   ";
    buttons[1] = "</48>|>";
    buttons[2] = "   >>";
    buttons[3] = "\nExit";
    _childwin = newCDKDialog( cdkScreen, CENTER, CENTER, msg, 1, buttons, 4, COLOR_PAIR(kColorMessage) | A_REVERSE | A_BOLD, true, true, false );
    setCDKDialogBackgroundColor( _childwin, "</4>" );
}

MVPPlayerDialog::~MVPPlayerDialog()
{
    destroyCDKDialog( _childwin );
}

void MVPPlayerDialog::initWin()
{
    assert( _childWin != NULL );
}

void MVPPlayerDialog::setCurrentTrack( const boost::filesystem::path & filename )
{
    
}

void MVPPlayerDialog::setIconStop()
{
    
}

void MVPPlayerDialog::setIconPlay()
{
    
}

int MVPPlayerDialog::exec()
{
    // Loop until user hits 'q' to quit
    int ch;
    refreshCDKScreen( _cdkScreen );
    while( _childwin->exitType != vESCAPE_HIT )
    {
        const int selection = activateCDKDialog( _childwin, NULL );
        switch( selection )
        {
            case 0:
            {
                break;
            }
            case 1:
            {
                signalViewHitPlay( std::string() );
                break;
            }
            case 2:
            {
                break;
            }
            case 3:
            {
                _childwin->exitType = vESCAPE_HIT;
                break;
            }
        }
        refreshCDKScreen( _cdkScreen );
    }
    
    return 0;
}

}
}
}
