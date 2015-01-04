#include "dlgUtils.hpp"

#include <sstream>

namespace mvpplayer
{
namespace gui
{
namespace ncurses
{

void displayError( CDKSCREEN* cdkscreen, const std::string & msg )
{
    char* messgs[1] = { const_cast<char*>( msg.c_str() ) };
    char* buttons[1] = { "Ok" };
    CDKDIALOG *dlg = newCDKDialog( cdkscreen, CENTER, CENTER, messgs, 1, buttons, 1, A_REVERSE | A_BOLD, TRUE, TRUE, FALSE );
    setCDKDialogBackgroundColor( dlg, "</2>" );
    refreshCDKScreen( cdkscreen );
    while( dlg->exitType != vESCAPE_HIT )
    {
        const int selection = activateCDKDialog( dlg, NULL );
        switch( selection )
        {
            case 0:
            {
                dlg->exitType = vESCAPE_HIT;
                break;
            }
        }
        refreshCDKScreen( cdkscreen );
    }
    destroyCDKDialog( dlg );
}

}


}
}
