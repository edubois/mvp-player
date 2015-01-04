#ifndef _CORE_ISOUNDPLAYER_HPP_
#define	_CORE_ISOUNDPLAYER_HPP_

#include <boost/signals2.hpp>

namespace mvpplayer
{

/**
 * Interface for sound players
 */
class ISoundPlayer
{
public:
    ISoundPlayer() {}
    virtual ~ISoundPlayer() {}
    
    /**
     * @brief restart track
     */
    virtual bool restart() = 0;

    /**
     * @brief sound volume control for the current played track
     * @param v volume value
     */
    virtual void setVolume( const float v ) = 0;

    /**
     * @brief load a given file
     * @param filename given file
     */
    virtual void load( const std::string & filename ) = 0;

    /**
     * @brief plays a sound
     * @param pause pause playing
     * @return false on success, true if error
     */
    virtual bool play (const bool pause = false) = 0;

    /**
     * @brief stop the current played track
     */
    virtual void stop()
    { unload(); }

    /**
     * @brief stop and free the current played track
     */
    virtual void unload() = 0;

    /**
     * @brief pause or unpause the current track
     * @param pause boolean setting the pause
     */
    virtual void setPause( const bool pause ) = 0;

    /**
     * @brief switch sound off/on
     * @param sound sound on/off
     */
    virtual void setSound( const bool sound ) = 0;

    /**
     * @brief toggle sound on or off
     */
    virtual void toggleSound() = 0;

    /**
     * @brief toggle pause on or off
     */
    virtual void togglePause() = 0;

// Signals
public:
    boost::signals2::signal<void()> signalEndOfTrack;                        ///< Signalize end of track
    boost::signals2::signal<void( const long, const long)> signalTrackPos;   ///< Signalize track position
};

}

#endif
