#define BOOST_TEST_MODULE player_network_remote_test
#include <unittest.hpp>

#include <mvp-player-net/server/Server.hpp>
#include <mvp-player-net/client/Client.hpp>
#include <mvp-player-core/stateMachineEvents.hpp>

#include <chrono>
#include <thread>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( network_remote_test_suite )

BOOST_AUTO_TEST_CASE( mvpplayer_remote )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
    mvpplayer::network::server::Server server;
    server.run();
    BOOST_CHECK( server.stopped() == false );
}

BOOST_AUTO_TEST_SUITE_END()
