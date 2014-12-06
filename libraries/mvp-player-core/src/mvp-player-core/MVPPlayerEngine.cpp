#include "MVPPlayerEngine.hpp"


namespace mvpplayer
{

MVPPlayerEngine::MVPPlayerEngine( ISoundPlayer *soundPlayer )
: _soundPlayer( soundPlayer )
{
    _currentPosition = _playlist.begin();
}

MVPPlayerEngine::~MVPPlayerEngine()
{
}

bool MVPPlayerEngine::playFile( const boost::filesystem::path & filename )
{
    stop();
    _currentPosition = _playlist.end(); // We are not playing from the playlist
    _currentPlayedTrack = filename;
    _soundPlayer->load( filename.string() );
    // Subscribe to sound player's end of track notifications
    _soundPlayer->signalEndOfTrack.connect( boost::bind( &MVPPlayerEngine::stop, this ) );
    return _soundPlayer->play();
}

void MVPPlayerEngine::playList()
{
    stop();
    _currentPosition = _playlist.begin();
    // Subscribe to sound player's end of track notifications
    _soundPlayer->signalEndOfTrack.connect( boost::bind( &MVPPlayerEngine::playNext, this ) );
    playCurrent();
}

void MVPPlayerEngine::playPrevious()
{
    if ( --_currentPosition != _playlist.end() )
    {
        stop();
        playCurrent();
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
    // Unsubscribe to sound player's end of track notifications
    _soundPlayer->signalEndOfTrack.disconnect( boost::bind( &MVPPlayerEngine::playNext, this ) );
    // Unsubscribe to sound player's end of track notifications
    _soundPlayer->signalEndOfTrack.disconnect( boost::bind( &MVPPlayerEngine::stop, this ) );
    // Stop all
    _soundPlayer->unload();
}

bool MVPPlayerEngine::playCurrent()
{
    if ( _currentPosition != _playlist.end() )
    {
        _currentPlayedTrack = *_currentPosition;
        _soundPlayer->load( _currentPlayedTrack.string() );
        _soundPlayer->play();
        return false;
    }
    return true;
}

}
