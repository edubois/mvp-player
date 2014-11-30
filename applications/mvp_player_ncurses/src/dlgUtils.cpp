#include "dlgUtils.hpp"

namespace mvpplayer
{
namespace gui
{
namespace ncurses
{

boost::filesystem::path openFile( CDKSCREEN* cdkscreen, const std::string & title, const std::string & extensions )
{
    CDKFSELECT *fileSelect = newCDKFselect( cdkscreen,
                                            CENTER,
                                            CENTER,
                                            19,
                                            64,
                                            title.c_str(), "Music file:", A_NORMAL, '_', A_REVERSE,
                                            "</5>", "</48>", "</N>", "</N>",
                                            TRUE,
                                            FALSE );

    const char* filename = activateCDKFselect( fileSelect, NULL );
    destroyCDKFselect( fileSelect );
    refreshCDKScreen( cdkscreen );
    if ( filename )
    {
        return std::string( filename );
    }
    else
    {
        return boost::filesystem::path();
    }
}

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
