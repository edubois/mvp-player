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

#include <string>
#include <iostream>

#include <QtCore/QFile>

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

    boost::signals2::signal<void(const boost::filesystem::path&)> signalPlayedTrack;
    boost::signals2::signal<void()> signalStopTrack;
    boost::signals2::signal<void(const std::string&)> signalFailed;
    boost::signals2::signal<boost::filesystem::path(const std::string&)> signalAskForFile;
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
      sc::custom_reaction< EvPlay >
    > reactions;

    /**
     * @brief reaction on stop event
     */
    sc::result react( const EvStop & ev )
    { return transit< Stopped >( &PlayerStateMachine::stopped, ev ); }

    /**
     * @brief reaction on play event
     */
    sc::result react( const EvPlay & ev )
    {
        // Check if file exists
        if ( QFile::exists( QString::fromStdString( ev.filename().string() ) ) )
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
            return transit< Playing >( &PlayerStateMachine::played, ev.filename() );
        }
        else
        {
            boost::filesystem::path answer = context< PlayerStateMachine >().askForFile( _tr( "Select a music filename!" ) );
            if ( !answer.empty() )
            {
                // Signalize that we are playing the file
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
