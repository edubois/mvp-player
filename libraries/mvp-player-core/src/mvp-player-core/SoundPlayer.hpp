#ifndef _CORE_SOUNDPLAYER_HPP_
#define	_CORE_SOUNDPLAYER_HPP_

#include "Singleton.hpp"
#include "ISoundPlayer.hpp"

#include <fmod.hpp>
#include <string>

namespace mvpplayer
{

class SoundPlayer : public ISoundPlayer, public Singleton<SoundPlayer>
{
public:
    SoundPlayer()
    : on( true )
    , possible( true )
    , fmodsystem( nullptr )
    , sound( nullptr )
    , channel( nullptr )
    {
        initialize();
    }
    virtual ~SoundPlayer() {}

public:
    void initialize(); //initialises sound

    /**
     * @brief sound volume control for the current played track
     * @param v volume value
     */
    void setVolume( const float v );
    
    /**
     * @brief load a given file
     * @param filename given file
     */
    void load( const std::string & filename );

    /**
     * @brief frees the sound object
     */
    void unload();

    /**
     * @brief plays a sound
     * @param pause pause playing
     * @return false on success, true if error
     */
    bool play (const bool pause = false);

    /**
     * @brief restart track
     */
    bool restart();

    /**
     * @brief checks whether the sound is on or off
     */
    bool getSound();

    /**
     * @brief pause or unpause the current track
     * @param pause boolean setting the pause
     */
    void setPause( const bool pause );

    /**
     * @brief switch sound off/on
     * @param sound sound on/off
     */
    void setSound( const bool sound );

    /**
     * @brief toggle sound on or off
     */
    void toggleSound();

    /**
     * @brief toggle pause on or off
     */
    void togglePause();

private:
    bool on; //is sound on?
    bool possible; //is it possible to play sound?
    std::string currentSound; //currently played sound
    //FMOD-specific stuff
    FMOD_RESULT result;
    FMOD::System* fmodsystem;
    FMOD::Sound* sound;
    FMOD::Channel* channel;
};

FMOD_RESULT playEndedCallback(FMOD_CHANNELCONTROL *channelcontrol, FMOD_CHANNELCONTROL_TYPE controltype, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype, void *commanddata1, void *commanddata2);

}

#endif
