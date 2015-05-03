#ifndef _TESTS_SOUNDPLAYERMOC_HPP_
#define	_TESTS_SOUNDPLAYERMOC_HPP_

#include <mvp-player-core/IFilePlayer.hpp>

#include <iostream>

namespace mvpplayer
{
namespace tests
{

/**
 * @brief Dummy sound player for tests
 */
class SoundPlayerMOC : public IFilePlayer
{
public:
    SoundPlayerMOC();
    virtual ~SoundPlayerMOC();

    /**
     * @brief unload all resources
     */
    virtual void terminate() override
    {}

    /**
     * @brief sound volume control for the current played track
     * @param v volume value
     */
    virtual void setVolume( const float v ) override
    { volume = v; }

    /**
     * @brief muted the current played track
     * @param m mute
     */
    void mute( const bool m = true ) override
    { muted = m; }

    /**
     * @brief is track paused?
     */
    bool isPaused() const override
    { return !playing; }
    
    /**
     * @brief is track playing?
     */
    bool isPlaying() const override
    { return playing; }

    /**
     * @brief load a given file
     * @param filename given file
     */
    virtual void load( const std::string & filename ) override
    { trackFilename = filename; }

    /**
     * @brief plays a sound
     * @param pause pause playing
     * @return false on success, true if error
     */
    virtual bool play( const bool pause = false ) override
    {
        playing = !pause;
        position = 1; // Simulate sample step
        return false;
    }

    /**
     * @brief restart current track
     */
    virtual bool restart() override
    {
        position = 0;
        return false;
    }
    
    /**
     * @brief stop and free the current played track
     */
    virtual void unload() override
    {
        playing = false;
        trackFilename = std::string();
    }

    /**
     * @brief pause or unpause the current track
     * @param pause boolean setting the pause
     */
    virtual void setPause( const bool pause ) override
    { playing = !pause; }

    /**
     * @brief switch sound off/on
     * @param sound sound on/off
     */
    virtual void setSound( const bool sound ) override
    { muted = !sound; }

    /**
     * @brief toggle sound on or off
     */
    virtual void toggleSound() override
    { muted = false; }

    /**
     * @brief toggle pause on or off
     */
    virtual void togglePause() override
    { playing = false; }
    
    /**
     * @brief get track position
     * @return position
     */
    std::size_t getPosition() const override
    { return 0; }

    /**
     * @brief get track length
     */
    std::size_t getLength() const override
    { return 123; }

    /**
     * @brief set track position
     */
    void setPosition( const std::size_t position, const ESeekPosition seekType = eSeekPositionPercent )
    { }
// Signals
public:
    int position = 1;
    float volume = 1.0f;
    std::string trackFilename;
    bool playing = false;
    bool muted = false;
};

}
}

#endif
