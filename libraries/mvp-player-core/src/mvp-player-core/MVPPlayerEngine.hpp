#ifndef _CORE_MVPPLAYERENGINE_HPP_
#define	_CORE_MVPPLAYERENGINE_HPP_

#include "IFilePlayer.hpp"
#include "m3uParser.hpp"

#include <boost/signals2.hpp>
#include <boost/signals2/trackable.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

#include <list>
#include <iterator>
#include <string>
#include <iostream>

namespace mvpplayer
{

class MVPPlayerEngine : public boost::signals2::trackable
{
public:
    MVPPlayerEngine( IFilePlayer *soundPlayer );
    virtual ~MVPPlayerEngine();

    /**
     * @brief stop current track
     */
    virtual void stop();

    /**
     * @brief play a given file (if m3u, playlist will be changed)
     * @return false on success, true if error
     */
    virtual bool playFile( const boost::filesystem::path & filename );

    /**
     * @brief open a given playlist
     * @param playlistFilename given playlist
     */
    void openPlaylist( const boost::filesystem::path & playlistFilename );

    /**
     * @brief set current track position
     * @param position position in percent (0-100) or ms
     * @param seekType seek position in percent or milliseconds
     */
    void setTrackPosition( const std::size_t position, const ESeekPosition seekType = eSeekPositionPercent );

    /**
     * @brief restart current track
     * @return false if success, true otherwise
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
     * @brief Plays a playlist item
     * @param index playlist index
     */
    virtual void playPlaylistItem( const int index );

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
     * @brief add track items to the playlist
     */
    void addTrackItems( const std::vector<boost::filesystem::path> & filename );

    /**
     * @brief clear the playlist
     */
    void clearPlaylist();

    /**
     * @brief set volume
     * @param volume volume in [0;1]
     */
    void setVolume( const float volume )
    { _soundPlayer->setVolume( volume ); }

    /**
     * @brief get current played track
     * @return the current track
     * @todo threadsafe this
     */
    inline const boost::filesystem::path & currentPlayedTrack() const
    { return _currentPlayedTrack; }

    /**
     * @brief notifies that we ended track playing
     */
    inline void notifyEndOfTrack() const
    { signalEndOfTrack(); }

    /**
     * @brief notifies the track's length
     * @param length track length (in milliseconds)
     */
    inline void notifyTrackLength( const std::size_t length ) const
    { signalTrackLength( length ); }

// Signals
public:
    boost::signals2::signal<void(const std::vector<m3uParser::PlaylistItem>&)> signalOpenedPlaylist;///< Signals that we opened a playlist
    boost::signals2::signal<void(const boost::filesystem::path&)> signalTrackAddedToPlaylist;       ///< Signals that a track has been added to the playlist
    boost::signals2::signal<void(const boost::filesystem::path&)> signalPlayedTrack;                ///< Signals that a track has been played
    boost::signals2::signal<void(const std::size_t len)> signalTrackLength;                         ///< Signals that the track has a certain length
    boost::signals2::signal<void(const std::size_t pos, const std::size_t len)> signalPositionChanged;                     ///< Signals that the track position has changed
    boost::signals2::signal<void()> signalEndOfTrack;                                               ///< Signals that the track has ended
    boost::signals2::signal<void()> signalClearedPlaylist;                                          ///< Signals that we cleared the playlist
    boost::signals2::signal<void(const boost::filesystem::path&, const int)> signalPlayingItemIndex;///< Signals that we are playing the 'index' track of the playlist

protected:
    IFilePlayer *_soundPlayer;                                             ///< Pointer to a sound player instance
    boost::filesystem::path _currentPlayedTrack;                            ///< Current played track
    std::list<boost::filesystem::path>::const_iterator _currentPosition;    ///< Current playing position
    std::list<boost::filesystem::path> _playlist;                           ///< Track playlist
    mutable boost::mutex _mutex;                                            ///< Used for thread safetyness
};

}

#endif
