#ifndef _CORE_SOUNDPLAYER_HPP_
#define	_CORE_SOUNDPLAYER_HPP_

#include <mvp-player-core/Singleton.hpp>
#include <mvp-player-core/IFilePlayer.hpp>

#include <fmod.hpp>
#include <string>

#include <boost/thread.hpp>
#include <boost/scoped_ptr.hpp>

namespace mvpplayer
{

static const std::size_t kDecideToSendPositionThreshold = 250; // in ms

class SoundPlayer : public IFilePlayer, public Singleton<SoundPlayer>
{
public:
    SoundPlayer()
    { initialize(); }

    virtual ~SoundPlayer();

public:

    /**
     * @brief initialize all
     */
    void initialize();

    /**
     * @brief free all
     */
    void terminate();

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
     * @brief mute sound
     */
    void mute( const bool active = true ) override;

    /**
     * @brief load a given file
     * @param filename given file
     */
    void load( const boost::filesystem::path & filename ) override;

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
     * @return false on success, true if error
     */
    bool setPosition( const std::size_t positionInPercent, const ESeekPosition seekType = eSeekPositionPercent ) override;

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

    /**
     * @brief is track paused
     */
    bool isPaused() const override;
    
    inline boost::mutex & mutexPlayer()
    { return _mutexPlayer; }

    inline FMOD::Channel* channel()
    { return _channel; }

private:
    void updater();

private:
    bool on = false;                    ///< is sound on?
    bool possible = true;              ///< is it possible to play sound?
    boost::filesystem::path _currentSound;  ///< currently played sound
    //FMOD-specific stuff
    FMOD_RESULT result;
    FMOD::System* _fmodsystem = nullptr;
    FMOD::Sound* _sound = nullptr;
    FMOD::Channel* _channel = nullptr;

    boost::scoped_ptr<boost::thread> _updaterThread; ///< Updater thread
    mutable boost::mutex _mutexPlayer;               ///< For thread safetyness
};

FMOD_RESULT playEndedCallback(FMOD_CHANNELCONTROL *channelcontrol, FMOD_CHANNELCONTROL_TYPE controltype, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype, void *commanddata1, void *commanddata2);

}

#endif
