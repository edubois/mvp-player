#include "MVPPlayerEngine.hpp"

#include <iterator>

namespace mvpplayer
{

MVPPlayerEngine::MVPPlayerEngine( ISoundPlayer *soundPlayer )
: _soundPlayer( soundPlayer )
{
    // Subscribe to sound player's end of track notifications
    _soundPlayer->signalEndOfTrack.connect( boost::bind( &MVPPlayerEngine::notifyEndOfTrack, this ) );
    _currentPosition = _playlist.begin();
}

MVPPlayerEngine::~MVPPlayerEngine()
{
}

bool MVPPlayerEngine::playFile( const boost::filesystem::path & filename )
{
    stop();
    _currentPlayedTrack = filename;
    _soundPlayer->load( filename.string() );
    return _soundPlayer->play();
}

void MVPPlayerEngine::playList()
{
    stop();
    _currentPosition = _playlist.begin();
    playCurrent();
}

/**
 * @brief Plays a playlist item
 * @param index playlist index
 */
void MVPPlayerEngine::playPlaylistItem( const int index )
{
    stop();
    _currentPosition = _playlist.begin();
    std::advance( _currentPosition, index );
    playCurrent();
}


bool MVPPlayerEngine::restart()
{
    return _soundPlayer->restart();
}

void MVPPlayerEngine::playPrevious()
{
    if ( --_currentPosition != _playlist.end() )
    {
        stop();
        playCurrent();
    }
    else
    {
        _currentPosition = _playlist.begin();
    }
}

void MVPPlayerEngine::playNext()
{
    if ( ++_currentPosition != _playlist.end() )
    {
        stop();
        playCurrent();
    }
}

void MVPPlayerEngine::stop()
{
    _currentPlayedTrack = boost::filesystem::path();
    // Stop all
    _soundPlayer->stop();
}

bool MVPPlayerEngine::playCurrent()
{
    if ( _currentPosition != _playlist.end() )
    {
        _currentPlayedTrack = *_currentPosition;
        _soundPlayer->load( _currentPlayedTrack.string() );
        _soundPlayer->play();
        signalPlayingItemIndex( _currentPlayedTrack, std::distance( _playlist.cbegin(), _currentPosition ) );
        return false;
    }
    return true;
}

}
