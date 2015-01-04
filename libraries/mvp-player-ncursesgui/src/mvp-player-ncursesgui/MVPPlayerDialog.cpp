#include "MVPPlayerDialog.hpp"
#include "fileUtils.hpp"

#include <mvp-player-core/m3uParser.hpp>

#include <boost/algorithm/string/predicate.hpp>

#include <iostream>

namespace mvpplayer
{
namespace gui
{
namespace ncurses
{
    
MVPPlayerDialog::MVPPlayerDialog( CDKSCREEN *cdkScreen, const int width, const int height, const int x, const int y )
: _cdkScreen( cdkScreen )
, _childwin( nullptr )
, _playlist( nullptr )
, _isPlaying( false )
{
    initWin( "Hit play to select a track or a playlist..." );
}

MVPPlayerDialog::~MVPPlayerDialog()
{
    destroyCDKDialog( _childwin );
    if ( _playlist )
    {
        destroyCDKItemlist( _playlist );
    }
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

void MVPPlayerDialog::openPlaylist( const boost::filesystem::path & playlistFilename )
{
   // Create the playlist widget
    std::vector<m3uParser::PlaylistItem> items = m3uParser::parse( playlistFilename );
    if ( !items.size() )
    { return; }

    std::vector<char*> itemsChars( items.size() );
    std::vector<std::unique_ptr<char[]> > itemsAlloc( items.size() );
    std::size_t i = 0;
    for( const m3uParser::PlaylistItem & item: items )
    {
        const std::string itemStr = item.infos.size() ? item.infos : item.filename.string();
        signalViewAddTrack( item.filename.string() );
        itemsAlloc[i].reset( new char[ itemStr.size() + 1 ] );
        strcpy( itemsAlloc[i].get(), itemStr.c_str() );
        itemsChars[i] = itemsAlloc[i].get();
        ++i;
    }

    if ( _playlist )
    { destroyCDKItemlist( _playlist ); }

    _playlist = newCDKScroll( _cdkScreen, CENTER, TOP, RIGHT, 10, 78, "<C>Playlist", &itemsChars[0], itemsChars.size(), TRUE, A_REVERSE | A_BOLD, TRUE, FALSE );
    setCDKScrollBackgroundColor( _playlist, "</5>" );
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
    if ( _playlist )
    {
        setCDKScrollCurrentItem( _playlist, row );
    }
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
                signalViewHitPrevious();
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
                    boost::filesystem::path item = openFile( _cdkScreen, "Open file or playlist", "*" );
                    if ( boost::iends_with( item.string(), ".m3u" ) )
                    {
                        signalViewClearPlaylist();
                        openPlaylist( item );
                        signalViewStartPlaylist();
                    }
                    else
                    {
                        signalViewHitPlay( item.string() );
                    }
                }
                break;
            }
            case 2:
            {
                signalViewHitNext();
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
