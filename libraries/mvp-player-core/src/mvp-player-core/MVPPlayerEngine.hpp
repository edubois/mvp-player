#ifndef _CORE_MVPPLAYERENGINE_HPP_
#define	_CORE_MVPPLAYERENGINE_HPP_

#include "IMVPPlayerEngine.hpp"
#include "SoundPlayer.hpp"

namespace mvpplayer
{

/**
 * @brief Engine for music player
 */
class MVPPlayerEngine : public IMVPPlayerEngine
{
public:
    MVPPlayerEngine();
    virtual ~MVPPlayerEngine();

    void stop();

    bool playCurrent();
    bool playFile( const boost::filesystem::path & filename );

public:
    boost::filesystem::path _currentPlayedTrack;                            ///< Current played track
    std::list<boost::filesystem::path>::const_iterator _currentPosition;    ///< Current playing position
    std::list<boost::filesystem::path> _playlist;                           ///< Track playlist
    boost::signals2::signal<void()> signalEndOfTrack;                       ///< Signals that the track has ended
};

}

#endif
