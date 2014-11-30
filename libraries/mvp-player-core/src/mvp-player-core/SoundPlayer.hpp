#ifndef _CORE_SOUNDPLAYER_HPP_
#define	_CORE_SOUNDPLAYER_HPP_

#include <fmod.hpp>

#include <string>

namespace mvpplayer
{

class SoundPlayer
{
private:
    static bool on; //is sound on?
    static bool possible; //is it possible to play sound?
    static std::string currentSound; //currently played sound
    //FMOD-specific stuff
    static FMOD_RESULT result;
    static FMOD::System* fmodsystem;
    static FMOD::Sound* sound;
    static FMOD::Channel* channel;

public:
    static void initialize(); //initialises sound

    //sound control
    static void setVolume( const float v ); //sets the actual playing sound's volume
    static void load( const std::string & filename ); //loads a soundfile
    static void unload(); //frees the sound object
    static void play (const bool pause = false); //plays a sound (may be started paused; no argument for unpaused)

    //getters
    static bool getSound(); //checks whether the sound is on

    //setters
    static void setPause( const bool pause ); //pause or unpause the sound
    static void setSound( const bool sound ); //set the sound on or off

    //toggles
    static void toggleSound(); //toggles sound on and off
    static void togglePause(); //toggle pause on/off
};

}

#endif
