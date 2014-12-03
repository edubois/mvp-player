#include "IMVPPlayerEngine.hpp"


namespace mvpplayer
{

IMVPPlayerEngine::~IMVPPlayerEngine()
{
}

void IMVPPlayerEngine::playList()
{
    _currentPosition = _playlist.begin();
    for( std::size_t i = 0; i < _playlist.size(); ++i )
    {
        playNext();
        ///@todo: wait until end
    }
}

void IMVPPlayerEngine::playPrevious()
{
    stop();
    if ( --_currentPosition != _playlist.end() )
    {
        playCurrent();
    }
}

void IMVPPlayerEngine::playNext()
{
    stop();
    if ( ++_currentPosition != _playlist.end() )
    {
        playCurrent();
    }
}

}
