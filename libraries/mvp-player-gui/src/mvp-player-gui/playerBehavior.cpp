#include "playerBehavior.hpp"

namespace mvpplayer
{
namespace gui
{

/**
 * @brief Setup music player's behavior (connect signals between the model/view/presenter)
 */
void setupMainBehavior( mvpplayer::IMVPPlayerEngine & m, mvpplayer::gui::IMVPPlayerDialog & v, mvpplayer::logic::PlayerStateMachine & p )
{
    //@{ Connections (behavior), note that the order is important
    // When we hit play button, we want to react by sending a play event to the state machine
    v.signalViewHitPlay.connect( boost::bind( &mvpplayer::logic::PlayerStateMachine::processPlay, &p, _1 ) );
    // When we hit stop button, we want to react by sending a stop event to the state machine
    v.signalViewHitStop.connect( boost::bind( &mvpplayer::logic::PlayerStateMachine::processStop, &p ) );
    // Connect played event to the engine play file function
    p.signalPlayedTrack.connect( boost::bind( &mvpplayer::IMVPPlayerEngine::playFile, &m, _1 ) );
    // Connect stop event to stop the current played track
    p.signalStopTrack.connect( boost::bind( &mvpplayer::IMVPPlayerEngine::stop, &m ) );

    // Connect stop event to change play button to [*]
    p.signalPlayedTrack.connect( boost::bind( &mvpplayer::gui::IMVPPlayerDialog::setIconStop, &v ) );
    // Connect played event to display track filename function
    p.signalPlayedTrack.connect( boost::bind( &mvpplayer::gui::IMVPPlayerDialog::setCurrentTrack, &v, _1 ) );
    // Connect stop event to display empty track filename
    p.signalStopTrack.connect( boost::bind( &mvpplayer::gui::IMVPPlayerDialog::setCurrentTrack, &v, boost::filesystem::path() ) );
    // Connect stop event to change play button to |>
    p.signalStopTrack.connect( boost::bind( &mvpplayer::gui::IMVPPlayerDialog::setIconPlay, &v ) );
    //@}
}

}
}
