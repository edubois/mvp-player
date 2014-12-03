#include "MVPPlayerEngine.hpp"

namespace mvpplayer
{

MVPPlayerEngine::MVPPlayerEngine()
{
    SoundPlayer::initialize();
    _currentPosition = _playlist.begin();
}

MVPPlayerEngine::~MVPPlayerEngine()
{
}

bool MVPPlayerEngine::playFile( const boost::filesystem::path & filename )
{
    IMVPPlayerEngine::playFile( filename );

    SoundPlayer::load( filename.string() );
    return SoundPlayer::play();
}


bool MVPPlayerEngine::playCurrent()
{
    if ( IMVPPlayerEngine::playCurrent() )
    {
        SoundPlayer::load( _currentPlayedTrack.string() );
        SoundPlayer::play();
        return false;
    }
    return true;
}

void MVPPlayerEngine::stop()
{
    SoundPlayer::unload();
}

}
