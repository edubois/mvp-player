#define BOOST_TEST_MODULE player_network_server_test
#include <unittest.hpp>

#include <mvp-player-net/server/Server.hpp>
#include <mvp-player-net/client/Client.hpp>
#include <mvp-player-core/stateMachineEvents.hpp>

#include <chrono>
#include <thread>
#include <boost/test/unit_test.hpp>

namespace mvpplayer
{
namespace tests
{

}
}

using namespace mvpplayer::tests;

BOOST_AUTO_TEST_SUITE( server_test_suite )

BOOST_AUTO_TEST_CASE( server_connection_disconnection )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
    mvpplayer::network::server::Server server;
    BOOST_CHECK( server.stopped() == true );
    server.run();
    BOOST_CHECK( server.stopped() == false );
    server.stop();
    BOOST_CHECK( server.stopped() == true );
}

BOOST_AUTO_TEST_CASE( server_client_presentation )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
    mvpplayer::network::server::Server server;
    BOOST_CHECK( server.stopped() == true );
    server.run();
    BOOST_CHECK( server.stopped() == false );

    mvpplayer::network::client::Client client1;
    client1.connect( "127.0.0.1" );
    mvpplayer::network::client::Client client2;
    client2.connect( "127.0.0.1" );
    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
    // A client should be connected to the server
    BOOST_CHECK( server.clients().size() == 2 );
    if ( server.clients().size() )
    {
        const mvpplayer::network::IPeer & serverPeer1 = *server.clients().begin()->second;
        BOOST_CHECK( serverPeer1.peerInfo().protocolVersionMajor == mvpplayer::network::kProtocolVersionMajor );
        BOOST_CHECK( serverPeer1.peerInfo().protocolVersionMinor == mvpplayer::network::kProtocolVersionMinor );
    }
    server.stop();
    BOOST_CHECK( server.stopped() == true );
}

BOOST_AUTO_TEST_CASE( server_client_event_communication )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
    mvpplayer::network::server::Server server;
    BOOST_CHECK( server.stopped() == true );
    server.run();
    BOOST_CHECK( server.stopped() == false );

    mvpplayer::network::client::Client client1;
    client1.connect( "127.0.0.1" );
    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
    // A client should be connected to the server
    BOOST_CHECK( server.clients().size() == 1 );
    if ( server.clients().size() )
    {
        // Server to client
        {
            bool receivedEvent = false;
            mvpplayer::logic::EvPlay eventPlay( "foo.ogg" );
            client1.signalEvent.connect( [&receivedEvent, &eventPlay](mvpplayer::IEvent & event)
                                         {
                                            receivedEvent = true;
                                            BOOST_CHECK( dynamic_cast<const mvpplayer::logic::EvPlay&>( event ).filename() == eventPlay.filename() );
                                         }
                                       );
            server.sendEventMulticast( eventPlay );
            BOOST_CHECK( receivedEvent == true );
        }
        
        // Client to server
        {
            bool receivedEvent = false;
            mvpplayer::logic::EvPlay eventPlay( "foo.ogg" );
            server.signalEventFrom.connect( [&receivedEvent, &eventPlay, &client1](const std::string & clientAddress, mvpplayer::IEvent & event)
                                         {
                                            receivedEvent = true;
                                            BOOST_CHECK( clientAddress == client1.address() );
                                            BOOST_CHECK( dynamic_cast<const mvpplayer::logic::EvPlay&>( event ).filename() == eventPlay.filename() );
                                         }
                                       );
            client1.sendEvent( eventPlay );
            BOOST_CHECK( receivedEvent == true );
        }
    }
    server.stop();
    BOOST_CHECK( server.stopped() == true );
}

BOOST_AUTO_TEST_SUITE_END()
