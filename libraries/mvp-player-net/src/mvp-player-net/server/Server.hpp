#ifndef _MVPPLAYER_SERVER_HPP_
#define	_MVPPLAYER_SERVER_HPP_

#include "peer/Peer.hpp"

#include <boost/ptr_container/ptr_map.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>

namespace mvpplayer
{
namespace network
{
namespace server
{

static const unsigned short kDefaultServerPort = 11999;

/**
 * @brief mvp_player network server
 */
class Server
{
private:
    typedef boost::ptr_multimap<std::string, Peer> MapClientT;

public:
    Server( const unsigned short port = kDefaultServerPort );
    virtual ~Server();

    void run();
    void stop();
    void handleConnection();
    inline bool stopped() const
    { return _stopped; }

    const MapClientT & clients() const
    { return _clients; }

    PeerInfo peerInfo() const;

    void sendEventMulticast( const IEvent & event );

public:
    boost::signals2::signal<void(const std::string&, IEvent&)> signalEventFrom; ///< Signals that a client sent an event
    boost::signals2::signal<void(const std::string&)> signalNewClient;          ///< Signals new client connection

private:
    void handleNewConnection( Peer * serverPeer, const boost::system::error_code& error );

private:
    MapClientT _clients;                                                        ///< Clients
    unsigned short _port;                                                       ///< Server port
    bool _stopped;                                                              ///< Is the server stopped
    boost::asio::io_service _ioService;                                         ///< IO Service
    std::unique_ptr<boost::thread> _ioThread;                                   ///< Service IO thread
    std::unique_ptr<boost::asio::ip::tcp::acceptor> _acceptor;                  ///< Connection acceptor
};

}
}
}

#endif
