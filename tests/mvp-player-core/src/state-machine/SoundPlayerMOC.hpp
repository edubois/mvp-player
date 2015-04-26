#ifndef _TESTS_SOUNDPLAYERMOC_HPP_
#define	_TESTS_SOUNDPLAYERMOC_HPP_

#include <mvp-player-core/ISoundPlayer.hpp>

#include <iostream>

namespace mvpplayer
{
namespace tests
{

/**
 * @brief Dummy sound player for tests
 */
class SoundPlayerMOC : public ISoundPlayer
{
public:
    SoundPlayerMOC();
    virtual ~SoundPlayerMOC();

    /**
     * @brief sound volume control for the current played track
     * @param v volume value
     */
    virtual void setVolume( const float v )
    { volume = v; }

    /**
     * @brief load a given file
     * @param filename given file
     */
    virtual void load( const std::string & filename )
    { trackFilename = filename; }

    /**
     * @brief plays a sound
     * @param pause pause playing
     * @return false on success, true if error
     */
    virtual bool play( const bool pause = false )
    {
        isPlaying = !pause;
        position = 1; // Simulate sample step
        return false;
    }

    /**
     * @brief restart current track
     */
    virtual bool restart()
    {
        position = 0;
        return false;
    }
    
    /**
     * @brief stop and free the current played track
     */
    virtual void unload()
    {
        isPlaying = false;
        trackFilename = std::string();
    }

    /**
     * @brief pause or unpause the current track
     * @param pause boolean setting the pause
     */
    virtual void setPause( const bool pause )
    { isPlaying = !pause; }

    /**
     * @brief switch sound off/on
     * @param sound sound on/off
     */
    virtual void setSound( const bool sound )
    { mute = !sound; }

    /**
     * @brief toggle sound on or off
     */
    virtual void toggleSound()
    { mute = false; }

    /**
     * @brief toggle pause on or off
     */
    virtual void togglePause()
    { isPlaying = false; }

// Signals
public:
    int position;
    float volume;
    std::string trackFilename;
    bool isPlaying;
    bool mute;
};

}
}

#endif
