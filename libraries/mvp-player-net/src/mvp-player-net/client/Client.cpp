#include "Client.hpp"

#include <mvp-player-net/PeerInfo.hpp>

#include <boost/foreach.hpp>

namespace mvpplayer
{
namespace network
{
namespace client
{

Client::Client()
: _disconnected( true )
{
}

Client::~Client()
{
    try
    {
        disconnect();
        _serverPeer.reset( nullptr );
        if ( _ioThread )
        {
            _ioThread->interrupt();
            _ioThread->join();
        }
    }
    catch( ... )
    {}
}

boost::system::error_code Client::connect( const std::string & ipAdress, const unsigned short port )
{
    disconnect();
    boost::system::error_code error;
    _serverPeer.reset( new Peer( &_ioService ) );
    // Signal proxy (transfer the signal)
    _serverPeer->signalEvent.connect( [this](IEvent & event){ signalEvent( event ); } );
    if ( _ioThread )
    {
        _ioThread->interrupt();
        _ioThread->join();
    }
    _ioThread.reset( new boost::thread( boost::bind( &boost::asio::io_service::run, &_ioService ) ) );
    _serverPeer->socket().connect( boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string( ipAdress ), port ), error );
    _serverPeer->receivePeerInfo();
    _serverPeer->presentation( peerInfo() );
    _serverPeer->start();
    _disconnected = false;
    return error;
}

void Client::disconnect()
{
    // Disconnect server peer
    if ( _serverPeer )
    {
        _serverPeer->disconnect();
    }

    // Stop service
    _ioService.stop();
    _disconnected = true;
}

PeerInfo Client::peerInfo() const
{
    PeerInfo peerInfo;
    peerInfo.peerName = "MVP-Player client";
    peerInfo.protocolVersionMinor = kProtocolVersionMinor;
    peerInfo.protocolVersionMajor = kProtocolVersionMajor;
    return peerInfo;
}

void Client::sendEvent( const IEvent & event )
{
    if ( _serverPeer )
    {
        if ( event.shallDispatch() )
        {
            _serverPeer->sendEvent( &event );
        }
    }
}

}
}
}
