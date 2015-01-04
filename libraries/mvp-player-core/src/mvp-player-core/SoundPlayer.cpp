#include "SoundPlayer.hpp"

#include <cassert>
#include <iostream>

namespace mvpplayer
{

//initialises sound
void SoundPlayer::initialize()
{
    //create the sound system. If fails, sound is set to impossible
    result = FMOD::System_Create( &fmodsystem );
    if ( result != FMOD_OK) possible = false;
    //if initialise the sound system. If fails, sound is set to impossible
    if (possible) result = fmodsystem->init( 2, FMOD_INIT_NORMAL, 0 );
    if (result != FMOD_OK) possible = false;
}

//sets the actual playing sound's volume
void SoundPlayer::setVolume( const float v )
{
    if ( channel && possible && on && v >= 0.0f && v <= 1.0f )
    {
        channel->setVolume( v );
    }
}

//loads a soundfile
void SoundPlayer::load( const std::string & filename )
{
    currentSound = filename;
    if ( fmodsystem )
    {
        if ( on && sound )
        {
            stop();
        }
        result = fmodsystem->createStream( currentSound.c_str(), FMOD_DEFAULT, 0, &sound );
        possible = ( result == FMOD_OK );
    }
}

//frees the sound object
void SoundPlayer::unload()
{
    if ( sound )
    {
        channel->stop();
        result = sound->release();
        sound = nullptr;
        channel = nullptr;
    }
    on = false;
}

/**
 * @brief restart track
 */
bool SoundPlayer::restart()
{
    if ( possible && on && channel )
    {
        return channel->setPosition( 0, FMOD_TIMEUNIT_MS ) == FMOD_OK && 
               fmodsystem->update() == FMOD_OK;
    }
    return true;
}

//plays a sound (no argument to leave pause as dafault)
bool SoundPlayer::play( const bool pause )
{
    if ( possible && sound )
    {
        result = fmodsystem->playSound( sound, NULL, pause, &channel );
        assert( channel != NULL );
        channel->setMode( FMOD_LOOP_NORMAL );
        setVolume( 1.0f );
        channel->setUserData( this );
        channel->setCallback( &playEndedCallback );
        on = true;
        return false;
    }
    return true;
}

//toggles sound on and off
void SoundPlayer::toggleSound()
{
    on = !on;
    if (on == true) { load( currentSound ); play(); }
    if (on == false) { stop(); }
}

//pause or unpause the sound
void SoundPlayer::setPause( const bool pause )
{
    channel->setPaused( pause );
}

//turn sound on or off
void SoundPlayer::setSound( const bool s )
{
    on = s;
}

//toggle pause on and off
void SoundPlayer::togglePause()
{
    bool p = false;
    channel->getPaused( &p );
    channel->setPaused( !p );
}

//tells whether the sound is on or off
bool SoundPlayer::getSound()
{
    return on;
}

FMOD_RESULT playEndedCallback(FMOD_CHANNELCONTROL *cchannelcontrol, FMOD_CHANNELCONTROL_TYPE controltype, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype, void *commanddata1, void *commanddata2)
{
    FMOD::ChannelControl *channelcontrol = reinterpret_cast<FMOD::ChannelControl *>( cchannelcontrol );
    mvpplayer::SoundPlayer* player;
    channelcontrol->getUserData( reinterpret_cast<void**>( &player ) );
    if ( player )
    {
        switch( controltype )
        {
            case FMOD_CHANNELCONTROL_CALLBACK_END:
            {
                player->getInstance().signalEndOfTrack();
                channelcontrol->setCallback( nullptr );
                break;
            }
            default:
            {
                break;
            }
        }
    }
    else
    {
        return FMOD_ERR_INTERNAL;
    }
    return FMOD_OK;
}

}
