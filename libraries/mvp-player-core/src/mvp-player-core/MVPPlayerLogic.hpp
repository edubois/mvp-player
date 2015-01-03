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
    
    inline void played( const boost::filesystem::path & filename )
    { signalPlayedTrack( filename ); }

    inline void stopped( const EvStop & )
    { signalStopTrack(); }

    inline void previousTrack( const EvPreviousTrack & )
    { signalPreviousTrack(); }

    inline void restartTrack( const EvRestartTrack & )
    { signalRestartTrack(); }

    inline void nextTrack( const EvNextTrack & )
    { signalNextTrack(); }

    inline void failed( const std::string & msg )
    { signalFailed( msg ); }

    boost::filesystem::path askForFile( const std::string & question )
    {
        boost::optional<boost::filesystem::path> answer = signalAskForFile( question );
        boost::filesystem::path filename;
        if ( answer )
        {
            filename = answer.get();
        }
        return filename;
    }
    
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

    boost::signals2::signal<void(const boost::filesystem::path&)> signalPlayedTrack;
    boost::signals2::signal<void()> signalStopTrack;
    boost::signals2::signal<void()> signalRestartTrack;
    boost::signals2::signal<void()> signalPreviousTrack;
    boost::signals2::signal<void()> signalNextTrack;
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
      sc::custom_reaction< EvRestartTrack >
    > reactions;

    /**
     * @brief reaction on stop track event
     */
    sc::result react( const EvStop & ev )
    { return transit< Stopped >( &PlayerStateMachine::stopped, ev ); }

    /**
     * @brief reaction on previous track event
     */
    sc::result react( const EvRestartTrack & ev )
    {
        return discard_event();
    }

    /**
     * @brief reaction on previous track event
     */
    sc::result react( const EvPreviousTrack & ev )
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        if ( ( now - context< PlayerStateMachine >().lastPlayTime ).count() >= kDecideToSendPreviousThreshold )
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
        if ( QFile::exists( QString::fromStdString( ev.filename().string() ) ) )
        {
            context< PlayerStateMachine >().lastPlayTime = std::chrono::system_clock::now();
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
      sc::custom_reaction< EvPlay >
    > reactions;

    /**
     * @brief reaction on play event
     */
    sc::result react( const EvPlay & ev )
    {
        // Check if file exists
        if ( QFile::exists( QString( QString::fromStdString( ev.filename().string()) ) ) )
        {
            context< PlayerStateMachine >().lastPlayTime = std::chrono::system_clock::now();
            return transit< Playing >( &PlayerStateMachine::played, ev.filename() );
        }
        else
        {
            boost::filesystem::path answer = context< PlayerStateMachine >().askForFile( _tr( "Select a music filename!" ) );
            if ( !answer.empty() )
            {
                // Signalize that we are playing the file
                context< PlayerStateMachine >().lastPlayTime = std::chrono::system_clock::now();
                return transit< Playing >( &PlayerStateMachine::played, answer );
            }
            // Signalize that we are playing the file
            if ( answer.empty() )
            {
                context< PlayerStateMachine >().failed( _tr( "Empty filename!" ) );
            }
            else
            {
                context< PlayerStateMachine >().failed( ( boost::format( _tr( "The file %1% doesn't exists!" ) ) % answer.filename() ).str() );
            }
            return discard_event();
        }
    }
};

}
}

#endif
