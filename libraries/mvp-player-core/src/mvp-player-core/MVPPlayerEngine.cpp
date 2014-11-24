#include "MVPPlayerEngine.hpp"

namespace mvpplayer
{

MVPPlayerEngine::MVPPlayerEngine()
{
    _currentPosition = _playlist.begin();
}

MVPPlayerEngine::~MVPPlayerEngine()
{
}

void MVPPlayerEngine::playFile( const boost::filesystem::path & filename )
{
    _currentPlayedTrack.reset( new QSound( QString::fromStdString( filename.string() ) ) );
    _currentPlayedTrack->play();
}

void MVPPlayerEngine::playList()
{
    _currentPosition = _playlist.begin();
    for( std::size_t i = 0; i < _playlist.size(); ++i )
    {
        playNext();
        ///@todo: wait until end
    }
}

void MVPPlayerEngine::stop()
{
    if ( _currentPlayedTrack.get() )
    {
        _currentPlayedTrack->stop();
    }
}

void MVPPlayerEngine::playPrevious()
{
    stop();
    if ( --_currentPosition != _playlist.end() )
    {
        playFile( *_currentPosition );
    }
}

void MVPPlayerEngine::playNext()
{
    stop();
    if ( ++_currentPosition != _playlist.end() )
    {
        playFile( *_currentPosition );
    }
}

}
