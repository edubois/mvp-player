#ifndef _STATEMACHINEEVENTS_HPP_
#define	_STATEMACHINEEVENTS_HPP_

#include <boost/statechart/event.hpp>
#include <boost/filesystem.hpp>

namespace mvpplayer
{
namespace logic
{

namespace fs = boost::filesystem;
namespace sc = boost::statechart;

/**
 * @brief event stop
 */
struct EvStop : sc::event< EvStop > {};

/**
 * @brief event restart track
 */
struct EvRestartTrack : sc::event< EvRestartTrack > {};

/**
 * @brief event previous track
 */
struct EvPreviousTrack : sc::event< EvPreviousTrack > {};

/**
 * @brief event next track
 */
struct EvNextTrack : sc::event< EvNextTrack > {};

/**
 * @brief event clear playlist
 */
struct EvClearPlaylist : sc::event< EvClearPlaylist > {};

/**
 * @brief event start playlist
 */
struct EvStartPlaylist : sc::event< EvStartPlaylist > {};

/**
 * @brief event end of track
 */
struct EvEndOfTrack : sc::event< EvEndOfTrack > {};

/**
 * @brief event play
 */
struct EvPlay : sc::event< EvPlay >
{
    EvPlay( const boost::filesystem::path & filename )
    : _filename( filename )
    {}

    inline const boost::filesystem::path & filename() const
    { return _filename; }

private:
    boost::filesystem::path _filename;      ///< Filename we want to play
};

/**
 * @brief event triggered when playing an item of the playlist
 */
struct EvPlayingItemIndex : sc::event< EvPlayingItemIndex >
{
    EvPlayingItemIndex( const boost::filesystem::path & filename, const int playlistIndex )
    : _filename( filename )
    , _playlistIndex( playlistIndex )
    {}

    inline const boost::filesystem::path & filename() const
    { return _filename; }

    inline const int playlistIndex() const
    { return _playlistIndex; }

private:
    boost::filesystem::path _filename;      ///< Filename we want to play
    int _playlistIndex;                     ///< Playlist index
};


/**
 * @brief event triggered when playing an item of the playlist
 */
struct EvPlayItemAtIndex : sc::event< EvPlayItemAtIndex >
{
    EvPlayItemAtIndex( const int index )
    : _playlistIndex( index )
    {}

    inline const int playlistIndex() const
    { return _playlistIndex; }

private:
    int _playlistIndex;                     ///< Playlist index
};

/**
 * @brief event reset
 */
struct EvReset : sc::event< EvReset > {};


}
}

#endif
