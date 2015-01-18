#include "Server.hpp"

#include <boost/foreach.hpp>

namespace mvpplayer
{
namespace network
{
namespace server
{

Server::Server( const unsigned short port )
: _port( port )
, _stopped( true )
{
}

Server::~Server()
{
    try
    {
        stop();
        if ( _ioThread )
        {
            _ioThread.reset( nullptr );
        }
    }
    catch( ... )
    {}
}

void Server::handleConnection()
{
    // Setup a new connection
    Peer *serverPeer = new Peer();
	_acceptor->async_accept( serverPeer->socket(),
                             boost::bind( &Server::handleNewConnection, this,
                             serverPeer, boost::asio::placeholders::error ) );
}

void Server::handleNewConnection( Peer * peerPtr, const boost::system::error_code& error )
{
    std::auto_ptr<Peer> serverPeer( peerPtr );
	if ( !error )
	{
        // The order is important here
        // Start by presenting ourself
        serverPeer->presentation( peerInfo() );
        // Receive peer information
        serverPeer->receivePeerInfo();
        // Start peer thread
        serverPeer->start();
        // Subscribe to events received from server peer
        const std::string clientAddress = serverPeer->address();
        serverPeer->signalEvent.connect( [this,clientAddress]( IEvent& event ){ signalEventFrom( clientAddress, event ); } );

        std::string peerAddress = serverPeer->address();
        _clients.insert( peerAddress, serverPeer.release() );
        signalNewClient( peerAddress );
        // Go back to new connection handling
		handleConnection();
	}
}

void Server::run()
{
    stop();
    _acceptor.reset( new boost::asio::ip::tcp::acceptor( _ioService, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), _port ) ) );
    handleConnection();

    _ioThread.reset( new boost::thread( boost::bind( &boost::asio::io_service::run, &_ioService ) ) );
    _stopped = false;
}

void Server::stop()
{
    // Disconnect peers
    BOOST_FOREACH( const MapClientT::iterator::value_type & v, _clients )
    {
        v.second->disconnect();
    }

    try
    {
        if ( _acceptor )
        {
            _acceptor->cancel();
            _acceptor->close();
        }
    }
    catch( ... )
    {}

    _stopped = true;
}

PeerInfo Server::peerInfo() const
{
    PeerInfo peerInfo;
    peerInfo.peerName = std::string( "MVP-Player server (" ) + boost::asio::ip::host_name() + ")";
    peerInfo.protocolVersionMinor = kProtocolVersionMinor;
    peerInfo.protocolVersionMajor = kProtocolVersionMajor;
    return peerInfo;
}

void Server::sendEventMulticast( const IEvent & event )
{
    BOOST_FOREACH( const MapClientT::iterator::value_type & v, _clients )
    {
        v.second->sendEvent( &event );
    }
}


}
}
}
