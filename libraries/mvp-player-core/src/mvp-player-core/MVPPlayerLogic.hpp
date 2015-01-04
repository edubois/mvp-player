#ifndef _MVPPLAYERLOGIC_HPP_
#define	_MVPPLAYERLOGIC_HPP_

#include "translation.hpp"

#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>
#include <boost/filesystem.hpp>
#include <boost/signals2.hpp>
#include <boost/format.hpp>
#include <chrono>

#include <string>
#include <iostream>

#include <QtCore/QFile>

namespace mvpplayer
{
namespace logic
{

namespace fs = boost::filesystem;
namespace sc = boost::statechart;

// Number of seconds to transform a 'restart track' event into 'previous track' event
static const std::size_t kDecideToSendPreviousThreshold( 2 );

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

struct Active;

/**
 * @brief mvp-player's state machine
 */
struct PlayerStateMachine : sc::state_machine< PlayerStateMachine, Active >
{
    PlayerStateMachine()
    { initiate(); }
    
    /**
     * @brief playing item at a given index (status change)
     * @param ev playing event
     */
    inline void playingItemIndex( const EvPlayingItemIndex & ev )
    {
        lastPlayTime = std::chrono::system_clock::now();
        signalPlayedTrack( ev.filename() );
        signalPlayingItemIndex( ev.filename(), ev.playlistIndex() );
    }

    /**
     * @brief played track (status)
     * @param filename track filename
     */
    inline void played( const boost::filesystem::path & filename )
    {
        lastPlayTime = std::chrono::system_clock::now();
        signalPlayedTrack( filename );
    }

    /**
     * @brief play item at a given index (action)
     * @param ev playing event
     */
    inline void playItemAtIndex( const EvPlayItemAtIndex & ev )
    { signalPlayItemAtIndex( ev.playlistIndex() ); }
    
    inline void stopped( const EvStop & )
    { signalStopTrack(); }

    inline void previousTrack( const EvPreviousTrack & )
    { signalPreviousTrack(); }

    inline void restartTrack( const EvRestartTrack & )
    { signalRestartTrack(); }

    inline void nextTrack( const EvNextTrack & )
    { signalNextTrack(); }

    inline void clearPlaylist( const EvClearPlaylist & )
    { signalClearPlaylist(); }

    inline void startPlaylist( const EvStartPlaylist & )
    { signalStartPlaylist(); }

    inline void failed( const std::string & msg )
    { signalFailed( msg ); }

    boost::optional<boost::filesystem::path> askForFile( const std::string & question )
    { return signalAskForFile( question ); }

    /**
     * @brief send 'play item at given index' event
     * @param index playlist index
     */
    inline void processPlayItemAtIndex( const int index )
    { process_event( EvPlayItemAtIndex( index ) ); }

    /**
     * @brief send 'playing item at given index (status)' event
     * @param filename track filename
     * @param index playlist index
     */
    inline void processPlayingItemIndex( const boost::filesystem::path & filename, const int index )
    { post_event( EvPlayingItemIndex( filename, index ) ); }

    inline void processPlay( const boost::filesystem::path & filename )
    { process_event( EvPlay( filename ) ); }

    inline void processStop()
    { process_event( EvStop() ); }

    inline void processRestart()
    { process_event( EvRestartTrack() ); }

    inline void processPrevious()
    { process_event( EvPreviousTrack() ); }

    inline void processNext()
    { process_event( EvNextTrack() ); }

    inline void processClearPlaylist()
    { process_event( EvClearPlaylist() ); }

    inline void processStartPlaylist()
    { process_event( EvStartPlaylist() ); }

    boost::signals2::signal<void(const boost::filesystem::path&)> signalPlayedTrack;
    boost::signals2::signal<void()> signalStopTrack;
    boost::signals2::signal<void()> signalRestartTrack;
    boost::signals2::signal<void()> signalPreviousTrack;
    boost::signals2::signal<void()> signalNextTrack;
    boost::signals2::signal<void()> signalClearPlaylist;
    boost::signals2::signal<void()> signalStartPlaylist;
    boost::signals2::signal<void(const int)> signalPlayItemAtIndex;
    boost::signals2::signal<void(const boost::filesystem::path&, const int)> signalPlayingItemIndex;
    boost::signals2::signal<void(const std::string&)> signalFailed;
    boost::signals2::signal<boost::filesystem::path(const std::string&)> signalAskForFile;
    std::chrono::system_clock::time_point lastPlayTime;      ///< Last clock since we hit play
};

struct Stopped;

/**
 * @brief Active is the outermost state and therefore needs to pass the
 * state machine class it belongs to.
 */
struct Active : sc::simple_state< Active, PlayerStateMachine, Stopped >
{
    typedef sc::transition< EvReset, Active > reactions; ///< From active we can reset via EvReset
};

/**
 * @brief playing state
 */
struct Playing : sc::simple_state< Playing, Active >
{
    typedef boost::mpl::list<
      sc::custom_reaction< EvStop >,
      sc::custom_reaction< EvPlay >,
      sc::custom_reaction< EvPreviousTrack >,
      sc::custom_reaction< EvNextTrack >,
      sc::custom_reaction< EvRestartTrack >,
      sc::custom_reaction< EvStartPlaylist >,
      sc::custom_reaction< EvClearPlaylist >,
      sc::custom_reaction< EvPlayingItemIndex >,
      sc::custom_reaction< EvPlayItemAtIndex >
    > reactions;

    /**
     * @brief reaction on stop track event
     */
    sc::result react( const EvStop & ev )
    { return transit< Stopped >( &PlayerStateMachine::stopped, ev ); }

    /**
     * @brief reaction on clear playlist event
     */
    sc::result react( const EvClearPlaylist & ev )
    { return transit< Stopped >( &PlayerStateMachine::clearPlaylist, ev ); }

    /**
     * @brief reaction on start playlist event
     */
    sc::result react( const EvStartPlaylist & ev )
    { return transit< Playing >( &PlayerStateMachine::startPlaylist, ev ); }

    /**
     * @brief reaction on playlist item playing event (status)
     */
    sc::result react( const EvPlayingItemIndex & ev )
    { return transit< Playing >( &PlayerStateMachine::playingItemIndex, ev ); }

    /**
     * @brief reaction on play item at index event (action)
     */
    sc::result react( const EvPlayItemAtIndex & ev )
    { return transit< Playing >( &PlayerStateMachine::playItemAtIndex, ev ); }

    /**
     * @brief reaction on previous track event
     */
    sc::result react( const EvRestartTrack & ev )
    { return discard_event(); }

    /**
     * @brief reaction on previous track event
     */
    sc::result react( const EvPreviousTrack & ev )
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        if ( std::chrono::duration_cast<std::chrono::seconds>( now - context< PlayerStateMachine >().lastPlayTime ).count() >= kDecideToSendPreviousThreshold )
        {
            context< PlayerStateMachine >().lastPlayTime = now;
            return transit< Playing >( &PlayerStateMachine::restartTrack, EvRestartTrack() );
        }
        else
        {
            return transit< Playing >( &PlayerStateMachine::previousTrack, ev );
        }
    }

    /**
     * @brief reaction on next track event
     */
    sc::result react( const EvNextTrack & ev )
    { return transit< Playing >( &PlayerStateMachine::nextTrack, ev ); }

    /**
     * @brief reaction on play event
     */
    sc::result react( const EvPlay & ev )
    {
        // Check if file exists
        if ( boost::filesystem::exists( ev.filename() ) )
        {
            return transit< Playing >( &PlayerStateMachine::played, ev.filename() );
        }
        else
        {
            // Signalize that we are playing the file
            context< PlayerStateMachine >().failed( ( boost::format( _tr( "The file %1% doesn't exists!" ) ) % ev.filename() ).str() );
            return discard_event();
        }
    }
};

/**
 * @brief stopped state
 */
struct Stopped : sc::simple_state< Stopped, Active >
{
    typedef boost::mpl::list<
      sc::custom_reaction< EvPlay >,
      sc::custom_reaction< EvClearPlaylist >,
      sc::custom_reaction< EvStartPlaylist >,
      sc::custom_reaction< EvPreviousTrack >,
      sc::custom_reaction< EvNextTrack >,
      sc::custom_reaction< EvPlayItemAtIndex >
    > reactions;

    /**
     * @brief reaction on clear playlist event
     */
    sc::result react( const EvClearPlaylist & ev )
    { return transit< Stopped >( &PlayerStateMachine::clearPlaylist, ev ); }

    /**
     * @brief reaction on start playlist event
     */
    sc::result react( const EvStartPlaylist & ev )
    { return transit< Playing >( &PlayerStateMachine::startPlaylist, ev ); }

    /**
     * @brief reaction on previous track event
     */
    sc::result react( const EvPreviousTrack & ev )
    { return transit< Playing >( &PlayerStateMachine::previousTrack, ev ); }

    /**
     * @brief reaction on next track event
     */
    sc::result react( const EvNextTrack & ev )
    { return transit< Playing >( &PlayerStateMachine::nextTrack, ev ); }

    /**
     * @brief reaction on play item at index event (action)
     */
    sc::result react( const EvPlayItemAtIndex & ev )
    { return transit< Playing >( &PlayerStateMachine::playItemAtIndex, ev ); }

    /**
     * @brief reaction on play event
     */
    sc::result react( const EvPlay & ev )
    {
        // Check if file exists
        if ( boost::filesystem::exists( ev.filename() ) )
        {
            return transit< Playing >( &PlayerStateMachine::played, ev.filename() );
        }
        else
        {
            boost::optional<boost::filesystem::path> answer = context< PlayerStateMachine >().askForFile( _tr( "Select a music filename!" ) );
            if ( answer && !answer.get().empty() )
            {
                // Signalize that we are playing the file
                return transit< Playing >( &PlayerStateMachine::played, answer.get() );
            }
            // Signalize that we are playing the file
            if ( answer )
            {
                if ( answer.get().empty() )
                {
                    context< PlayerStateMachine >().failed( _tr( "Empty filename!" ) );
                }
                else
                {
                    context< PlayerStateMachine >().failed( ( boost::format( _tr( "The file %1% doesn't exists!" ) ) % answer.get().filename() ).str() );
                }
            }
            return discard_event();
        }
    }
};

}
}

#endif
