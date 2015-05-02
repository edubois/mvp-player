#define BOOST_TEST_MODULE player_state_machine_test
#include <unittest.hpp>

#include "MVPPlayerGuiMoc.hpp"
#include "SoundPlayerMOC.hpp"
#include <mvp-player-core/MVPPlayerEngine.hpp>
#include <mvp-player-core/MVPPlayerLogic.hpp>
#include <mvp-player-gui/playerBehavior.hpp>
#include <chrono>
#include <thread>

using namespace mvpplayer::tests;

namespace mvpplayer
{
namespace tests
{

static const std::string kDummyExistingMusicFile1( "tests/mvp-player-core/src/state-machine/dummyExistingFile1.ogg" );
static const std::string kDummyExistingMusicFile2( "tests/mvp-player-core/src/state-machine/dummyExistingFile2.ogg" );

inline void printError( const std::string & error )
{
    std::cerr << "Error: " << error << std::endl;
}

}
}

BOOST_AUTO_TEST_SUITE( play_statie_machine_test_suite )

BOOST_AUTO_TEST_CASE( play_stop_music )
{
    SoundPlayerMOC player;
    mvpplayer::MVPPlayerEngine engine( &player ); // model with a dummy player
    MVPPlayerGuiMoc viewMoc;      // dummy view
    mvpplayer::logic::MVPPlayerPresenter presenter;     // logic (presenter)
    presenter.startStateMachine<mvpplayer::logic::PlayerStateMachine>();
    
    // Bind the whole thing
    mvpplayer::gui::setupMainBehavior( engine, viewMoc, presenter );

    // Print on console on errors
    presenter.signalFailed.connect( boost::bind( &mvpplayer::tests::printError, _1 ) );

    // Simulate play
    std::vector<boost::filesystem::path> fileItems;
    fileItems.push_back( kDummyExistingMusicFile1 );
    viewMoc.signalViewAppendTrackItems( fileItems );
    viewMoc.signalViewHitPlaylistItem( 0 );
    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ) );

    // Check if the engine is playing the "dummyFile.ogg"
    BOOST_CHECK( player.trackFilename == kDummyExistingMusicFile1 );

    // Simulate stop
    viewMoc.signalViewHitButton( "Stop", true );
    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ) );

    // Check if the engine is stopped
    BOOST_CHECK( player.trackFilename == std::string() );
}

BOOST_AUTO_TEST_CASE( play_restart_previous_music )
{
    SoundPlayerMOC player;
    mvpplayer::MVPPlayerEngine engine( &player ); // model with a dummy player
    MVPPlayerGuiMoc viewMoc;      // dummy view
    mvpplayer::logic::MVPPlayerPresenter presenter;     // logic (presenter)
    presenter.startStateMachine<mvpplayer::logic::PlayerStateMachine>();

    // Bind the whole thing
    mvpplayer::gui::setupMainBehavior( engine, viewMoc, presenter );
    
    engine.addTrack( kDummyExistingMusicFile1 );
    engine.addTrack( kDummyExistingMusicFile2 );
    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ) );

    // Print on console on errors
    presenter.signalFailed.connect( boost::bind( &mvpplayer::tests::printError, _1 ) );

    // Simulate play
    viewMoc.signalViewStartPlaylist();
    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ) );

    // Check if the engine is playing the "dummyFile.ogg"
    BOOST_CHECK( player.trackFilename == kDummyExistingMusicFile1 );

    // Check if we are "playing" a file
    BOOST_CHECK( player.position > 0 );

    // Simulate next track
    viewMoc.signalViewHitButton( "Next", true );
    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ) );

    // Check if the engine is playing the "dummyFile2.ogg"
    BOOST_CHECK( player.trackFilename == kDummyExistingMusicFile2 );

    // Check if we are "playing" a file
    BOOST_CHECK( player.position > 0 );

    // Sleep, necessary to make 'previous track' event a 'restart track' event
    std::this_thread::sleep_for( std::chrono::milliseconds( 2010 ) );

    // Simulate previous
    viewMoc.signalViewHitButton( "Previous", true );
    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ) );

    // Check if the position is 0 (restart)
    BOOST_CHECK( player.position == 0 );

    // Check if the engine is still playing the track (because of track restart)
    BOOST_CHECK( player.trackFilename == kDummyExistingMusicFile2 );
}


BOOST_AUTO_TEST_CASE( play_restart_next_previous_music )
{
    SoundPlayerMOC player;
    mvpplayer::MVPPlayerEngine engine( &player ); // model with a dummy player
    MVPPlayerGuiMoc viewMoc;      // dummy view
    mvpplayer::logic::MVPPlayerPresenter presenter;     // logic (presenter)
    presenter.startStateMachine<mvpplayer::logic::PlayerStateMachine>();

    // Bind the whole thing
    mvpplayer::gui::setupMainBehavior( engine, viewMoc, presenter );
    
    engine.addTrack( kDummyExistingMusicFile1 );
    engine.addTrack( kDummyExistingMusicFile2 );
    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ) );

    // Print on console on errors
    presenter.signalFailed.connect( boost::bind( &mvpplayer::tests::printError, _1 ) );

    // Simulate play
    viewMoc.signalViewStartPlaylist();
    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ) );

    // Check if the engine is playing the "dummyFile.ogg"
    BOOST_CHECK( player.trackFilename == kDummyExistingMusicFile1 );

    // Check if we are "playing" a file
    BOOST_CHECK( player.position > 0 );

    // Simulate next track
    viewMoc.signalViewHitButton( "Next", true );
    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ) );

    // Check if the engine is playing the "dummyFile2.ogg"
    BOOST_CHECK( player.trackFilename == kDummyExistingMusicFile2 );

    // Sleep, necessary to make 'previous track' event a 'restart track' event
    std::this_thread::sleep_for( std::chrono::milliseconds( 2010 ) );

    // Simulate previous
    viewMoc.signalViewHitButton( "Previous", true );
    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ) );

    // Check if the position is 0 (restart)
    BOOST_CHECK( player.position == 0 );

    // Sleep, necessary to make 'previous track' event a 'restart track' event
    std::this_thread::sleep_for( std::chrono::milliseconds( 2010 ) );

    // Simulate previous
    viewMoc.signalViewHitButton( "Previous", true );
    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ) );

    // Check if the position is 0 (restart)
    BOOST_CHECK( player.position == 0 );

    // Simulate previous
    viewMoc.signalViewHitButton( "Previous", true );
    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ) );

    // Check if the position is 0 (playing)
    BOOST_CHECK( player.position != 0 );

    // Check if the engine is still playing the track (because of track restart)
    BOOST_CHECK( player.trackFilename == kDummyExistingMusicFile1 );
}

BOOST_AUTO_TEST_CASE( play_playlist_item )
{
    SoundPlayerMOC player;
    mvpplayer::MVPPlayerEngine engine( &player ); // model with a dummy player
    MVPPlayerGuiMoc viewMoc;      // dummy view
    mvpplayer::logic::MVPPlayerPresenter presenter;     // logic (presenter)
    presenter.startStateMachine<mvpplayer::logic::PlayerStateMachine>();

    // Bind the whole thing
    mvpplayer::gui::setupMainBehavior( engine, viewMoc, presenter );
    
    engine.addTrack( kDummyExistingMusicFile1 );
    engine.addTrack( kDummyExistingMusicFile2 );
    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ) );

    // Print on console on errors
    presenter.signalFailed.connect( boost::bind( &mvpplayer::tests::printError, _1 ) );

    // Simulate play
    viewMoc.signalViewStartPlaylist();
    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ) );

    // Check if the engine is playing the "dummyFile.ogg"
    BOOST_CHECK( player.trackFilename == kDummyExistingMusicFile1 );

    // Check if we are "playing" a file
    BOOST_CHECK( player.position > 0 );

    viewMoc.signalViewHitPlaylistItem( 1 );
    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ) );

    // Check if the engine is playing the right track
    BOOST_CHECK( player.trackFilename == kDummyExistingMusicFile2 );

    // Check if we are "playing" a file
    BOOST_CHECK( player.position > 0 );

    viewMoc.signalViewHitPlaylistItem( 0 );
    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ) );

    // Check if the engine is playing the right track
    BOOST_CHECK( player.trackFilename == kDummyExistingMusicFile1 );

    // Check if we are "playing" a file
    BOOST_CHECK( player.position > 0 );
}

BOOST_AUTO_TEST_SUITE_END()
