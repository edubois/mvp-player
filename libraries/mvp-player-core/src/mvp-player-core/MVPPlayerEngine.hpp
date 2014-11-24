#ifndef _MVPPLAYERENGINE_HPP_
#define	_MVPPLAYERENGINE_HPP_

#include <QtMultimedia/QSound>

#include <boost/signals2.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>

#include <list>
#include <iterator>
#include <string>

namespace mvpplayer
{

/**
 * @brief Engine for music player
 */
class MVPPlayerEngine
{
public:
    MVPPlayerEngine();
    virtual ~MVPPlayerEngine();

    void stop();

    void playFile( const boost::filesystem::path & filename );
    void playList();
    void playPrevious();

    void playNext();

    inline void addTrack( const boost::filesystem::path & filename )
    {
        _playlist.push_back( filename );
    }
    
    inline void clearPlaylist()
    {
        _playlist.clear();
        _currentPosition = _playlist.begin();
    }

public:
    std::auto_ptr<QSound> _currentPlayedTrack;
    std::list<boost::filesystem::path>::const_iterator _currentPosition;    ///< Current playing position
    std::list<boost::filesystem::path> _playlist;                   ///< Track playlist
    boost::signals2::signal<void()> signalEndOfTrack;   ///< Signals that the track has ended
};

}

#endif
