#ifndef _MVPPLAYERLOGIC_HPP_
#define	_MVPPLAYERLOGIC_HPP_

#include "m3uParser.hpp"
#include "MVPPlayerPresenter.hpp"
#include "stateMachineEvents.hpp"

#include "translation.hpp"

#include <boost/statechart/asynchronous_state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include <chrono>
#include <string>
#include <iostream>

namespace mvpplayer
{
namespace logic
{

namespace fs = boost::filesystem;
namespace sc = boost::statechart;

// Number of seconds to transform a 'restart track' event into 'previous track' event
static const std::size_t kDecideToSendPreviousThreshold( 2 );

struct Active;

struct Stopped;

struct Playing;

/**
 * @brief mvp-player's state machine (asynchronous is needed to be thread safe)
 */
struct PlayerStateMachine : sc::asynchronous_state_machine< PlayerStateMachine, Active>
{
    PlayerStateMachine( my_context ctx, MVPPlayerPresenter & presenter )
    : my_base( ctx )
    , presenter( presenter )
    {}

    int currentPlaylistIndex = -1;
    std::size_t nItemsPlaylist = 0;
    MVPPlayerPresenter & presenter;                         ///< The state machine owner
    std::chrono::system_clock::time_point lastPlayTime;     ///< Last clock since we hit play
    boost::optional<boost::filesystem::path> lastTrackFilename;              ///< Last played track
};

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
      sc::custom_reaction< EvPlayed >,
      sc::custom_reaction< EvTrackLengthChanged >,
      sc::custom_reaction< EvPreviousTrack >,
      sc::custom_reaction< EvNextTrack >,
      sc::custom_reaction< EvRestartTrack >,
      sc::custom_reaction< EvStartPlaylist >,
      sc::custom_reaction< EvOpenedPlaylist >,
      sc::custom_reaction< EvSetTrackPosition >,
      sc::custom_reaction< EvTrackPositionChanged >,
      sc::custom_reaction< EvAddTrack >,
      sc::custom_reaction< EvAddedTrack >,
      sc::custom_reaction< EvAppendPlaylistTrack >,
      sc::custom_reaction< EvClearPlaylist >,
      sc::custom_reaction< EvModelClearedPlaylist >,
      sc::custom_reaction< EvPlayingItemIndex >,
      sc::custom_reaction< EvPlayItemAtIndex >,
      sc::custom_reaction< EvEndOfTrack >,
      sc::custom_reaction< EvCustomState >,
      sc::custom_reaction< EvCommandActive >
    > reactions;

    /**
     * @brief reaction on stop track event
     */
    sc::result react( const EvStop & ev )
    {
        context< PlayerStateMachine >().presenter.stopped();
        return transit< Stopped >();
    }

    /**
     * @brief reaction on 'command active' event
     */
    sc::result react( const EvCommandActive & ev )
    {
        context< PlayerStateMachine >().presenter.commandActive( ev.commandName(), ev.active() );
        return transit< Playing >();
    }

    /**
     * @brief reaction on end of track event
     */
    sc::result react( const EvEndOfTrack & ev )
    {
        context< PlayerStateMachine >().presenter.processNext();
        return transit< Playing >();
    }

    /**
     * @brief reaction on track position set
     */
    sc::result react( const EvSetTrackPosition & ev )
    {
        context< PlayerStateMachine >().presenter.setTrackPosition( ev.position() );
        return transit< Playing >();
    }

    /**
     * @brief reaction on track length event
     */
    sc::result react( const EvTrackLengthChanged & ev )
    {
        context< PlayerStateMachine >().presenter.trackLengthChanged( ev.length() );
        return transit< Playing >();
    }

    /**
     * @brief reaction on track position update
     */
    sc::result react( const EvTrackPositionChanged & ev )
    {
        context< PlayerStateMachine >().presenter.trackPositionChanged( ev.position(), ev.length() );
        return transit< Playing >();
    }

    /**
     * @brief reaction on custom events
     */
    sc::result react( const EvCustomState & ev )
    {
        auto result = context< PlayerStateMachine >().presenter.askPlayingStateExternalTransition( ev.action(), boost::ref( *this ) );
        // First boost::option level is happening when no slot is connected to the signal
        if ( result != boost::none )
        {
            // Second boost::option level is happening when the action has been rejected
            return sc::detail::result_utility::make_result( *result );
        }
        else
        {
            // action has been rejected
            return discard_event();
        }
    }

    /**
     * @brief reaction on clear playlist event
     */
    sc::result react( const EvClearPlaylist & ev )
    {
        context< PlayerStateMachine >().presenter.clearPlaylist();
        return transit< Playing >();
    }

    /**
     * @brief reaction on model clear playlist event
     */
    sc::result react( const EvModelClearedPlaylist & ev )
    {
        context< PlayerStateMachine >().presenter.modelClearedPlaylist();
        context< PlayerStateMachine >().nItemsPlaylist = 0;
        context< PlayerStateMachine >().currentPlaylistIndex = -1;
        return transit< Stopped >();
    }

    /**
     * @brief reaction on start playlist event
     */
    sc::result react( const EvStartPlaylist & )
    {
        context< PlayerStateMachine >().presenter.startPlaylist();
        context< PlayerStateMachine >().currentPlaylistIndex = 0;
        return transit< Playing >();
    }

    /**
     * @brief reaction to playlist open
     */
    sc::result react( const EvOpenedPlaylist & ev )
    {
        context< PlayerStateMachine >().nItemsPlaylist = ev.playlistItems().size();
        context< PlayerStateMachine >().currentPlaylistIndex = 0;
        context< PlayerStateMachine >().presenter.openedPlaylist( ev.playlistItems() );
        return transit< Playing >();
    }

    /**
     * @brief reaction on playlist item playing event (status)
     */
    sc::result react( const EvPlayingItemIndex & ev )
    {
        context< PlayerStateMachine >().currentPlaylistIndex = ev.playlistIndex();
        context< PlayerStateMachine >().lastPlayTime = std::chrono::system_clock::now();
        context< PlayerStateMachine >().presenter.playingItemIndex( ev.filename(), ev.playlistIndex() );
        return transit< Playing >();
    }

    /**
     * @brief reaction on play item at index event (action)
     */
    sc::result react( const EvPlayItemAtIndex & ev )
    {
        context< PlayerStateMachine >().presenter.playItemAtIndex( ev.playlistIndex() );
        return transit< Playing >();
    }

    /**
     * @brief reaction on previous track event
     */
    sc::result react( const EvRestartTrack & ev )
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        context< PlayerStateMachine >().lastPlayTime = now;
        context< PlayerStateMachine >().presenter.restartTrack();
        return transit< Playing >();
    }

    /**
     * @brief reaction on previous track event
     */
    sc::result react( const EvPreviousTrack & ev )
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        if ( context< PlayerStateMachine >().nItemsPlaylist == 1 || 
             std::chrono::duration_cast<std::chrono::seconds>( now - context< PlayerStateMachine >().lastPlayTime ).count() >= kDecideToSendPreviousThreshold )
        {
            context< PlayerStateMachine >().presenter.processRestart();
            return discard_event();
        }
        else
        {
            context< PlayerStateMachine >().presenter.previousTrack();
            return transit< Playing >();
        }
    }

    /**
     * @brief reaction on next track event
     */
    sc::result react( const EvNextTrack & ev )
    {
        if ( context< PlayerStateMachine >().currentPlaylistIndex == context< PlayerStateMachine >().nItemsPlaylist - 1 )
        {
            context< PlayerStateMachine >().presenter.processStop();
        }
        else
        {
            context< PlayerStateMachine >().presenter.nextTrack();
        }
        return transit< Playing >();
    }

    /**
     * @brief reaction on add track event
     */
    sc::result react( const EvAddTrack & ev )
    {
        // Check if the file is not a playlist and if the file exists
        if ( boost::filesystem::exists( ev.filename() ) )
        {
            if ( !boost::iends_with( ev.filename().string(), ".m3u" ) )
            {
                context< PlayerStateMachine >().presenter.addTrack( ev.filename() );
                return transit< Playing >();
            }
            else
            {
                context< PlayerStateMachine >().presenter.appendPlaylistTracks( ev.filename() );
                return transit< Playing >();
            }
        }
        return discard_event();
    }

    /**
     * @brief reaction on track added event
     */
    sc::result react( const EvAddedTrack & ev )
    {
        if ( context< PlayerStateMachine >().currentPlaylistIndex == -1 )
        {
            context< PlayerStateMachine >().currentPlaylistIndex = 0;
        }
        ++context< PlayerStateMachine >().nItemsPlaylist;
        context< PlayerStateMachine >().presenter.addedTrack( ev.filename() );
        return transit< Playing >();
    }

    /**
     * @brief reaction on append playlist items event
     */
    sc::result react( const EvAppendPlaylistTrack & ev )
    {
        context< PlayerStateMachine >().presenter.appendPlaylistTracks( ev.playlistFilename() );
        return transit< Playing >();
    }

    /**
     * @brief reaction on played event
     */
    sc::result react( const EvPlayed & ev )
    {
        context< PlayerStateMachine >().presenter.played( ev.filename() );
        context< PlayerStateMachine >().lastTrackFilename = ev.filename();
        return transit< Playing >();
    }

    /**
     * @brief reaction on play event
     */
    sc::result react( const EvPlay & ev )
    {
        // Check if we want to resume the track
        if ( !ev.hasFilename() )
        {
            if ( context< PlayerStateMachine >().nItemsPlaylist )
            {
                if ( context< PlayerStateMachine >().currentPlaylistIndex >= 0 )
                {
                    context< PlayerStateMachine >().presenter.playItemAtIndex( context< PlayerStateMachine >().currentPlaylistIndex );
                }
                else
                {
                    context< PlayerStateMachine >().presenter.startPlaylist();
                }
                return transit< Playing >();
            }
            else
            {
                return discard_event();
            }
        }
        else
        {
            // Check if file exists
            const boost::filesystem::path filename = ev.filename().get();
            if ( boost::filesystem::exists( filename ) )
            {
                context< PlayerStateMachine >().lastPlayTime = std::chrono::system_clock::now();
                context< PlayerStateMachine >().presenter.playTrack( filename );

                if ( context< PlayerStateMachine >().nItemsPlaylist == 0 )
                {
                    context< PlayerStateMachine >().currentPlaylistIndex = -1;
                }
                return transit< Playing >();
            }
            else
            {
                // Signalize that we are playing the file
                context< PlayerStateMachine >().presenter.failed( ( boost::format( _tr( "The file %1% doesn't exists!" ) ) % filename ).str() );
                return discard_event();
            }
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
      sc::custom_reaction< EvPlayed >,
      sc::custom_reaction< EvTrackLengthChanged >,
      sc::custom_reaction< EvTrackPositionChanged >,
      sc::custom_reaction< EvSetTrackPosition >,
      sc::custom_reaction< EvClearPlaylist >,
      sc::custom_reaction< EvModelClearedPlaylist >,
      sc::custom_reaction< EvAddTrack >,
      sc::custom_reaction< EvAddedTrack >,
      sc::custom_reaction< EvAppendPlaylistTrack >,
      sc::custom_reaction< EvStartPlaylist >,
      sc::custom_reaction< EvOpenedPlaylist >,
      sc::custom_reaction< EvPreviousTrack >,
      sc::custom_reaction< EvNextTrack >,
      sc::custom_reaction< EvPlayItemAtIndex >,
      sc::custom_reaction< EvEndOfTrack >,
      sc::custom_reaction< EvCustomState >,
      sc::custom_reaction< EvCommandActive >
    > reactions;

    /**
     * @brief reaction on custom events
     */
    sc::result react( const EvCustomState & ev )
    {
        auto result = context< PlayerStateMachine >().presenter.askStoppedStateExternalTransition( boost::ref( ev.action() ), boost::ref( *this ) );
        if ( result != boost::none )
        {
            return sc::detail::result_utility::make_result( *result );
        }
        else
        {
            return discard_event();
        }
    }

    /**
     * @brief reaction on 'command active' event
     */
    sc::result react( const EvCommandActive & ev )
    {
        context< PlayerStateMachine >().presenter.commandActive( ev.commandName(), ev.active() );
        return transit< Playing >();
    }

    /**
     * @brief reaction to playlist open
     */
    sc::result react( const EvOpenedPlaylist & ev )
    {
        context< PlayerStateMachine >().presenter.openedPlaylist( ev.playlistItems() );
        return transit< Playing >();
    }

    /**
     * @brief reaction on add track event
     */
    sc::result react( const EvAddTrack & ev )
    {
        // Check if the file is not a playlist and if the file exists
        if ( boost::filesystem::exists( ev.filename() ) )
        {
            if ( !boost::iends_with( ev.filename().string(), ".m3u" ) )
            {
                context< PlayerStateMachine >().presenter.addTrack( ev.filename() );
                return transit< Stopped >();
            }
            else
            {
                context< PlayerStateMachine >().presenter.appendPlaylistTracks( ev.filename() );
                return transit< Stopped >();
            }
        }
        return discard_event();
    }

    /**
     * @brief reaction on append playlist items event
     */
    sc::result react( const EvAppendPlaylistTrack & ev )
    {
        context< PlayerStateMachine >().presenter.appendPlaylistTracks( ev.playlistFilename() );
        return transit< Stopped >();
    }

    /**
     * @brief reaction on track added event
     */
    sc::result react( const EvAddedTrack & ev )
    {
        context< PlayerStateMachine >().presenter.addedTrack( ev.filename() );
        ++context< PlayerStateMachine >().nItemsPlaylist;
        return transit< Stopped >();
    }

    /**
     * @brief reaction on track position update
     */
    sc::result react( const EvSetTrackPosition & ev )
    {
        context< PlayerStateMachine >().presenter.setTrackPosition( ev.position() );
        return transit< Stopped >();
    }

    /**
     * @brief reaction on track position update
     */
    sc::result react( const EvTrackPositionChanged & ev )
    {
        context< PlayerStateMachine >().presenter.trackPositionChanged( ev.position(), ev.length() );
        return transit< Stopped >();
    }

    /**
     * @brief reaction on track length event
     */
    sc::result react( const EvTrackLengthChanged & ev )
    {
        context< PlayerStateMachine >().presenter.trackLengthChanged( ev.length() );
        return transit< Stopped >();
    }

    /**
     * @brief reaction on clear playlist event
     */
    sc::result react( const EvClearPlaylist & ev )
    {
        context< PlayerStateMachine >().presenter.clearPlaylist();
        context< PlayerStateMachine >().nItemsPlaylist = 0;
        context< PlayerStateMachine >().currentPlaylistIndex = -1;
        return transit< Stopped >();
    }

    /**
     * @brief reaction on model clear playlist event
     */
    sc::result react( const EvModelClearedPlaylist & ev )
    {
        context< PlayerStateMachine >().presenter.modelClearedPlaylist();
        return transit< Stopped >();
    }

    /**
     * @brief reaction on start playlist event
     */
    sc::result react( const EvStartPlaylist & ev )
    {
        context< PlayerStateMachine >().presenter.processStartPlaylist();
        return transit< Playing >();
    }

    /**
     * @brief reaction on previous track event
     */
    sc::result react( const EvPreviousTrack & ev )
    {
        context< PlayerStateMachine >().presenter.previousTrack();
        return transit< Stopped >();
    }

    /**
     * @brief reaction on next track event
     */
    sc::result react( const EvNextTrack & ev )
    {
        if ( context< PlayerStateMachine >().currentPlaylistIndex != context< PlayerStateMachine >().nItemsPlaylist - 1 )
        {
            context< PlayerStateMachine >().presenter.nextTrack();
        }
        return transit< Stopped >();
    }

    /**
     * @brief reaction on play item at index event (action)
     */
    sc::result react( const EvPlayItemAtIndex & ev )
    {
        context< PlayerStateMachine >().currentPlaylistIndex = ev.playlistIndex();
        context< PlayerStateMachine >().presenter.playItemAtIndex( ev.playlistIndex() );
        return transit< Playing >();
    }

    /**
     * @brief reaction on play event
     */
    sc::result react( const EvPlay & ev )
    {
        // Check if file exists
        if ( ev.hasFilename() && boost::filesystem::exists( ev.filename().get() ) )
        {
            context< PlayerStateMachine >().lastPlayTime = std::chrono::system_clock::now();
            context< PlayerStateMachine >().presenter.processPlay( ev.filename().get() );
            return transit< Playing >();
        }
        else if ( context< PlayerStateMachine >().lastTrackFilename != boost::none )
        {
            context< PlayerStateMachine >().presenter.processPlay( *context< PlayerStateMachine >().lastTrackFilename );
            return transit< Playing >();
        }
        else
        {
            boost::optional<boost::filesystem::path> answer = context< PlayerStateMachine >().presenter.askForFile( _tr( "Select a music filename!" ), eFileDialogModeOpen );
            if ( answer && !answer.get().empty() )
            {
                context< PlayerStateMachine >().presenter.processClearPlaylist();
                context< PlayerStateMachine >().presenter.processAddTrack( *answer );
                context< PlayerStateMachine >().presenter.processStartPlaylist();
                return transit< Playing >();
            }
            else if ( answer )
            {
                if ( answer.get().empty() )
                {
                    context< PlayerStateMachine >().presenter.failed( _tr( "Empty filename!" ) );
                }
                else
                {
                    context< PlayerStateMachine >().presenter.failed( ( boost::format( _tr( "The file %1% doesn't exists!" ) ) % answer.get().filename() ).str() );
                }
            }
            return discard_event();
        }
    }

    /**
     * @brief reaction on end of track event
     */
    sc::result react( const EvEndOfTrack & )
    { return discard_event(); }

    /**
     * @brief reaction on played event
     */
    sc::result react( const EvPlayed & ev )
    {
        context< PlayerStateMachine >().presenter.played( ev.filename() );
        context< PlayerStateMachine >().lastTrackFilename = ev.filename();
        return transit< Playing >();
    }
};

/**
 * @brief playing state
 */
struct Paused : sc::simple_state< Paused, Active >
{
    typedef boost::mpl::list<
      sc::custom_reaction< EvStop >,
      sc::custom_reaction< EvPlay >,
      sc::custom_reaction< EvPreviousTrack >,
      sc::custom_reaction< EvNextTrack >,
      sc::custom_reaction< EvStartPlaylist >,
      sc::custom_reaction< EvPlayItemAtIndex >
    > reactions;

    /**
     * @brief reaction on stop track event
     */
    sc::result react( const EvPlay & )
    {
        transit< Playing >();
        return forward_event();
    }

    /**
     * @brief reaction on stop track event
     */
    sc::result react( const EvStop & )
    {
        transit< Stopped >();
        return forward_event();
    }

    /**
     * @brief reaction on start playlist event
     */
    sc::result react( const EvStartPlaylist & )
    {
        transit< Playing >();
        return forward_event();
    }

    /**
     * @brief reaction on previous track event
     */
    sc::result react( const EvPreviousTrack & )
    {
        transit< Playing >();
        return forward_event();
    }

    /**
     * @brief reaction on previous track event
     */
    sc::result react( const EvNextTrack & )
    {
        transit< Playing >();
        return forward_event();
    }

    /**
     * @brief reaction on play item at index event
     */
    sc::result react( const EvPlayItemAtIndex & )
    {
        transit< Playing >();
        return forward_event();
    }

};

}
}

#endif
