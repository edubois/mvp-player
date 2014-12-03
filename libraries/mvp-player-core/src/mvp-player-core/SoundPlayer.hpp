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
    
    /**
     * @brief load a given file
     * @param filename given file
     */
    static void load( const std::string & filename );
    
    /**
     * @brief frees the sound object
     */
    static void unload();

    /**
     * @brief plays a sound
     * @param pause pause playing
     * @return false on success, true if error
     */
    static bool play (const bool pause = false);

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
