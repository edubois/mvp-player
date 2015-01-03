#ifndef _CORE_MVPPLAYERENGINE_HPP_
#define	_CORE_MVPPLAYERENGINE_HPP_

#include "ISoundPlayer.hpp"

#include <boost/signals2.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>

#include <list>
#include <iterator>
#include <string>
#include <iostream>

namespace mvpplayer
{

class MVPPlayerEngine
{
public:
    MVPPlayerEngine( ISoundPlayer *soundPlayer );
    virtual ~MVPPlayerEngine();

    /**
     * @brief stop current track
     */
    virtual void stop();

    /**
     * @brief play a given file
     * @return false on success, true if error
     */
    virtual bool playFile( const boost::filesystem::path & filename );

    /**
     * @brief restart current track
     * @return 
     */
    virtual bool restart();

    /**
     * @brief play current track
     * @return false on success, true if error
     */
    virtual bool playCurrent();

    /**
     * @brief Play the current playlist
     */
    virtual void playList();

    /**
     * @brief Play the previous item of the playlist
     */
    virtual void playPrevious();

    /**
     * @brief Play the next item of the playlist
     */
    virtual void playNext();

    /**
     * @brief add a track to the playlist
     */
    inline void addTrack( const boost::filesystem::path & filename )
    {
        _playlist.push_back( filename );
        signalTrackAddedToPlaylist( filename );
    }

    /**
     * @brief clear the playlist
     */
    inline void clearPlaylist()
    {
        stop();
        _playlist.clear();
        _currentPosition = _playlist.begin();
    }

    /**
     * @brief get current played track
     * @return the current track
     * @todo threadsafe this
     */
    inline const boost::filesystem::path & currentPlayedTrack() const
    { return _currentPlayedTrack; }

// Signals
public:
    boost::signals2::signal<void(const boost::filesystem::path&)> signalTrackAddedToPlaylist; ///< Signals that a track has been added to the playlist
    boost::signals2::signal<void()> signalEndOfTrack;                       ///< Signals that the track has ended

protected:
    ISoundPlayer *_soundPlayer;                                             ///< Pointer to a sound player instance
    boost::filesystem::path _currentPlayedTrack;                            ///< Current played track
    std::list<boost::filesystem::path>::const_iterator _currentPosition;    ///< Current playing position
    std::list<boost::filesystem::path> _playlist;                           ///< Track playlist
};

}

#endif
