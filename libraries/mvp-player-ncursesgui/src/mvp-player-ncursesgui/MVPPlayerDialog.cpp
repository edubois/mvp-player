#include "MVPPlayerDialog.hpp"

#include <iostream>

namespace mvpplayer
{
namespace gui
{
namespace ncurses
{
    
MVPPlayerDialog::MVPPlayerDialog( CDKSCREEN *cdkScreen, const int width, const int height, const int x, const int y )
: _cdkScreen( cdkScreen )
, _childwin( NULL )
, _isPlaying( false )
{
    initWin( "Hit play to select a track..." );
}

MVPPlayerDialog::~MVPPlayerDialog()
{
    destroyCDKDialog( _childwin );
}

void MVPPlayerDialog::initWin( const std::string & currentTrack, const bool playButton )
{
    if ( _childwin )
    {
        destroyCDKDialog( _childwin );
    }
    init_pair( kColorMessage, COLOR_WHITE, COLOR_BLUE );
    char* msg[1];
    if ( currentTrack.length() == 0 )
    {
        msg[0] = "Music player";
    }
    else
    {
        msg[0] = const_cast<char*>( currentTrack.c_str() );
    }
    char* buttons[10];
    buttons[0] = "<<   ";
    if ( playButton )
    {
        buttons[1] = "</48>|> ";
    }
    else
    {
        buttons[1] = "</49>|| ";
    }
    buttons[2] = "   >>";
    buttons[3] = "\nExit";
    _childwin = newCDKDialog( _cdkScreen, CENTER, CENTER, msg, 1, buttons, 4, COLOR_PAIR(kColorMessage) | A_REVERSE | A_BOLD, true, true, false );
    setCDKDialogBackgroundColor( _childwin, "</5>" );
    assert( _childwin != NULL );
    refreshCDKScreen( _cdkScreen );
}

void MVPPlayerDialog::setCurrentTrack( const boost::filesystem::path & filename )
{
    initWin( filename.string(), !_isPlaying );
}

void MVPPlayerDialog::setIconStop()
{
    _isPlaying = true;
    initWin( "", !_isPlaying );
}

void MVPPlayerDialog::setIconPlay()
{
    _isPlaying = false;
    initWin( "Hit play to resume track", !_isPlaying );
}

void MVPPlayerDialog::setPlaylistItemIndex( const int row )
{
    ///@todo
}

int MVPPlayerDialog::exec()
{
    // Loop until user hits 'q' to quit
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
                if ( _isPlaying )
                {
                    signalViewHitStop();
                }
                else
                {
                    signalViewHitPlay( std::string() );
                }
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
