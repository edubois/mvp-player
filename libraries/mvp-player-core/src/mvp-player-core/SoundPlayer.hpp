#ifndef _CORE_SOUNDPLAYER_HPP_
#define	_CORE_SOUNDPLAYER_HPP_

#include "Singleton.hpp"
#include "ISoundPlayer.hpp"

#include <fmod.hpp>
#include <string>

#include <boost/thread.hpp>
#include <boost/scoped_ptr.hpp>

namespace mvpplayer
{

class SoundPlayer : public ISoundPlayer, public Singleton<SoundPlayer>
{
public:
    SoundPlayer()
    : on( false )
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
     * @brief is the player playing sound
     */
    inline bool isPlaying() const override
    { return on; }

    /**
     * @brief sound volume control for the current played track
     * @param v volume value
     */
    void setVolume( const float v ) override;
    
    /**
     * @brief load a given file
     * @param filename given file
     */
    void load( const std::string & filename ) override;

    /**
     * @brief frees the sound object
     */
    void unload() override;

    /**
     * @brief plays a sound
     * @param pause pause playing
     * @return false on success, true if error
     */
    bool play (const bool pause = false) override;

    /**
     * @brief set current track position
     * @param position position in percent (0-100) or ms
     * @param seekType seek position in percent or milliseconds
     */
    void setPosition( const std::size_t positionInPercent, const ESeekPosition seekType = eSeekPositionPercent ) override;

    /**
     * @brief get the current track's position
     * @return the current position in milliseconds
     */
    std::size_t getPosition() const override;

    /**
     * @brief get the current track's length
     * @return the current length in milliseconds
     */
    std::size_t getLength() const override;

    /**
     * @brief restart track
     */
    bool restart() override;

    /**
     * @brief checks whether the sound is on or off
     */
    bool getSound();

    /**
     * @brief pause or unpause the current track
     * @param pause boolean setting the pause
     */
    void setPause( const bool pause ) override;

    /**
     * @brief switch sound off/on
     * @param sound sound on/off
     */
    void setSound( const bool sound ) override;

    /**
     * @brief toggle sound on or off
     */
    void toggleSound() override;

    /**
     * @brief toggle pause on or off
     */
    void togglePause() override;

    inline boost::mutex & mutexPlayer()
    { return _mutexPlayer; }

private:
    void updater();

private:
    bool on; //is sound on?
    bool possible; //is it possible to play sound?
    std::string currentSound; //currently played sound
    //FMOD-specific stuff
    FMOD_RESULT result;
    FMOD::System* fmodsystem;
    FMOD::Sound* sound;
    FMOD::Channel* channel;

    boost::scoped_ptr<boost::thread> _updaterThread; ///< Updater thread
    mutable boost::mutex _mutexPlayer;               ///< For thread safetyness
};

FMOD_RESULT playEndedCallback(FMOD_CHANNELCONTROL *channelcontrol, FMOD_CHANNELCONTROL_TYPE controltype, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype, void *commanddata1, void *commanddata2);

}

#endif
