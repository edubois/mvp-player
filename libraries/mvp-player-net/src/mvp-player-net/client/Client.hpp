#ifndef _MVPPLAYER_CLIENT_HPP_
#define	_MVPPLAYER_CLIENT_HPP_

#include "peer/Peer.hpp"

#include <boost/ptr_container/ptr_map.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>

namespace mvpplayer
{
namespace network
{
namespace client
{

static const unsigned short kDefaultServerPort = 11999;

/**
 * @brief mvp_player network client
 */
class Client : public boost::signals2::trackable
{
public:
    Client();
    virtual ~Client();

    boost::system::error_code connect( const std::string & adress, const unsigned short port = kDefaultServerPort );
    void disconnect();

    inline bool disconnected() const
    { return _disconnected; }

    PeerInfo peerInfo() const;
    
    /**
     * @brief return client address
     */
    inline std::string address() const
    { return _serverPeer->address(); }

    void sendEvent( const IEvent & event );

public:
//- signals
    boost::signals2::signal<void( IEvent& )> signalEvent;

private:
    bool _disconnected;                                                         ///< Disconnected flag
    std::unique_ptr<Peer> _serverPeer;                                          ///< Server peer instance
    boost::asio::io_service _ioService;                                         ///< IO Service
    boost::scoped_ptr<boost::asio::io_service::work> _workIO;                   ///< Work thread
    std::unique_ptr<boost::thread> _ioThread;                                   ///< Service IO thread
};

}
}
}

#endif
