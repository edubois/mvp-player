#ifndef _CORE_IMVPPLAYERENGINE_HPP_
#define	_CORE_IMVPPLAYERENGINE_HPP_

#include <boost/signals2.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>

#include <list>
#include <iterator>
#include <string>
#include <iostream>

namespace mvpplayer
{

class IMVPPlayerEngine
{
public:
    IMVPPlayerEngine() {}
    virtual ~IMVPPlayerEngine() = 0;

    virtual void stop()
    { _currentPlayedTrack = boost::filesystem::path(); }

    /**
     * @brief play a given file
     * @return false on success, true if error
     */
    virtual bool playFile( const boost::filesystem::path & filename )
    {
        stop();
        _currentPosition = _playlist.end(); // We are not playing from the playlist
        _currentPlayedTrack = filename;
        return false;
    }
    
    /**
     * @brief play current track
     * @return false on success, true if error
     */
    virtual bool playCurrent()
    {
        if ( _currentPosition != _playlist.end() )
        {
            stop();
            _currentPlayedTrack = *_currentPosition;
            return false;
        }
        return true;
    }


    virtual void playList();

    virtual void playPrevious();
    virtual void playNext();

    inline void addTrack( const boost::filesystem::path & filename )
    { _playlist.push_back( filename ); }
    
    inline void clearPlaylist()
    {
        _playlist.clear();
        _currentPosition = _playlist.begin();
    }

    inline const boost::filesystem::path & currentPlayedTrack() const
    { return _currentPlayedTrack; }

// Signals
public:
    boost::signals2::signal<void()> signalEndOfTrack;                       ///< Signals that the track has ended

private:
    boost::filesystem::path _currentPlayedTrack;                            ///< Current played track
    std::list<boost::filesystem::path>::const_iterator _currentPosition;    ///< Current playing position
    std::list<boost::filesystem::path> _playlist;                           ///< Track playlist
};

}

#endif	/* IMVPPLAYERENGINE_HPP */

