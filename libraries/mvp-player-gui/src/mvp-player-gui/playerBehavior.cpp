#include "playerBehavior.hpp"

namespace mvpplayer
{
namespace gui
{

/**
 * @brief Setup music player's behavior (connect signals between the model/view/presenter)
 * Connections should be done anywhere else than here.
 */
void setupMainBehavior( mvpplayer::MVPPlayerEngine & m, mvpplayer::gui::IMVPPlayerDialog & v, mvpplayer::logic::PlayerStateMachine & p )
{
    //@{ Connections (behavior), note that the order is important
    // When we hit play button, we want to react by sending a play event to the state machine
    v.signalViewHitPlay.connect( boost::bind( &mvpplayer::logic::PlayerStateMachine::processPlay, &p, _1 ) );
    // When we hit stop button, we want to react by sending a stop event to the state machine
    v.signalViewHitStop.connect( boost::bind( &mvpplayer::logic::PlayerStateMachine::processStop, &p ) );
    // When we hit clear playlist button, we want to react by sending a clear playlist event to the state machine
    v.signalViewClearPlaylist.connect( boost::bind( &mvpplayer::logic::PlayerStateMachine::processClearPlaylist, &p ) );
    // When we hit start playlist button, we want to react by sending a start playlist event to the state machine
    v.signalViewStartPlaylist.connect( boost::bind( &mvpplayer::logic::PlayerStateMachine::processStartPlaylist, &p ) );
    // When we add a track on the view, we want to react by adding the track in the engine's playlist
    v.signalViewAddTrack.connect( boost::bind( &mvpplayer::MVPPlayerEngine::addTrack, &m, _1 ) );
    // When the view want to play a playlist item, react by sending the event to the state machine
    v.signalViewHitPlaylistItem.connect( boost::bind( &mvpplayer::logic::PlayerStateMachine::processPlayItemAtIndex, &p, _1 ) );
    // Connect play item event to the engine play item function
    p.signalPlayItemAtIndex.connect( boost::bind( &mvpplayer::MVPPlayerEngine::playPlaylistItem, &m, _1 ) );
    // Connect played event to the engine play file function
    p.signalPlayedTrack.connect( boost::bind( &mvpplayer::MVPPlayerEngine::playFile, &m, _1 ) );
    // Connect stop event to stop the current played track
    p.signalStopTrack.connect( boost::bind( &mvpplayer::MVPPlayerEngine::stop, &m ) );
    // Connect clear playlist event to clear the engine's playlist
    p.signalClearPlaylist.connect( boost::bind( &mvpplayer::MVPPlayerEngine::clearPlaylist, &m ) );
    // Connect start playlist event to start the engine's playlist
    p.signalStartPlaylist.connect( boost::bind( &mvpplayer::MVPPlayerEngine::playList, &m ) );
    // Connect stop event to change play button to [*]
    p.signalPlayedTrack.connect( boost::bind( &mvpplayer::gui::IMVPPlayerDialog::setIconStop, &v ) );
    // Connect played event to display track filename function
    p.signalPlayedTrack.connect( boost::bind( &mvpplayer::gui::IMVPPlayerDialog::setCurrentTrack, &v, _1 ) );
    // Connect stop event to display empty track filename
    p.signalStopTrack.connect( boost::bind( &mvpplayer::gui::IMVPPlayerDialog::setCurrentTrack, &v, boost::filesystem::path() ) );
    // Connect stop event to change play button to |>
    p.signalStopTrack.connect( boost::bind( &mvpplayer::gui::IMVPPlayerDialog::setIconPlay, &v ) );
    // When we hit previous button, we want to react by sending a 'previous track' event to the state machine
    v.signalViewHitPrevious.connect( boost::bind( &mvpplayer::logic::PlayerStateMachine::processPrevious, &p ) );
    // When we hit next button, we want to react by sending a 'next track' event to the state machine
    v.signalViewHitNext.connect( boost::bind( &mvpplayer::logic::PlayerStateMachine::processNext, &p ) );
    // When the logic asks next track, we want to play next track
    p.signalNextTrack.connect( boost::bind( &mvpplayer::MVPPlayerEngine::playNext, &m ) );
    // When the logic asks previous track, we want to play previous track
    p.signalPreviousTrack.connect( boost::bind( &mvpplayer::MVPPlayerEngine::playPrevious, &m ) );
    // When the logic asks for 'restart track' play restart track
    p.signalRestartTrack.connect( boost::bind( &mvpplayer::MVPPlayerEngine::restart, &m ) );
    // When the model plays another playlist track, inform the view
    m.signalPlayingItemIndex.connect( boost::bind( &mvpplayer::logic::PlayerStateMachine::processPlayingItemIndex, &p, _1, _2 ) );
    p.signalPlayingItemIndex.connect( boost::bind( &mvpplayer::gui::IMVPPlayerDialog::setPlaylistItemIndex, &v, _2 ) );
    //@}
}

}
}
