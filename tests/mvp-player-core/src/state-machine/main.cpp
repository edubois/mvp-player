#define BOOST_TEST_MODULE player_state_machine_test
#include <unittest.hpp>

#include "MVPPlayerGuiMoc.hpp"
#include "SoundPlayerMOC.hpp"

#include <mvp-player-core/MVPPlayerEngine.hpp>
#include <mvp-player-gui/playerBehavior.hpp>

using namespace mvpplayer::tests;

namespace mvpplayer
{
namespace tests
{

static const std::string kDummyExistingMusicFile( "tests/mvp-player-core/src/state-machine/dummyExistingFile.ogg" );

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
    mvpplayer::logic::PlayerStateMachine playerLogic;     // logic (presenter)
    
    // Bind the whole thing
    mvpplayer::gui::setupMainBehavior( engine, viewMoc, playerLogic );
    
    // Print on console on errors
    playerLogic.signalFailed.connect( boost::bind( &mvpplayer::tests::printError, _1 ) );

    // Simulate play
    viewMoc.signalViewHitPlay( kDummyExistingMusicFile );

    // Check if the engine is playing the "dummyFile.ogg"
    BOOST_CHECK( player.trackFilename == kDummyExistingMusicFile );

    // Simulate stop
    viewMoc.signalViewHitStop();

    // Check if the engine is stopped
    BOOST_CHECK( player.trackFilename == std::string() );
}

BOOST_AUTO_TEST_CASE( play_restart_previous_music )
{
    // @todo
}

BOOST_AUTO_TEST_SUITE_END()