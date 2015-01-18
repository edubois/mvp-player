#include "MVPPlayerRemote.hpp"

namespace mvpplayer
{
namespace network
{
namespace server
{

MVPPlayerRemote::MVPPlayerRemote( Server & server )
: _server( server )
{
}

MVPPlayerRemote::~MVPPlayerRemote()
{
}

void MVPPlayerRemote::setCurrentTrack( const boost::filesystem::path & filename )
{
    
}

void MVPPlayerRemote::setPlaylistItemIndex( const int row )
{
    
}

void MVPPlayerRemote::setIconStop()
{
    
}

void MVPPlayerRemote::setIconPlay()
{
    
}

void MVPPlayerRemote::openedPlaylist( const std::vector<m3uParser::PlaylistItem> & playlistItems )
{
    
}

void MVPPlayerRemote::clearPlaylist()
{
    
}

void MVPPlayerRemote::addTrack( const boost::filesystem::path & filename )
{
    
}

}
}
}
