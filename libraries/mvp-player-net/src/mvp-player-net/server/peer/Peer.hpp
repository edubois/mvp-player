#ifndef _MVPPLAYER_SERVER_PEER_HPP_
#define	_MVPPLAYER_SERVER_PEER_HPP_

#include <mvp-player-net/IPeer.hpp>

namespace mvpplayer
{
namespace network
{
namespace server
{

/**
 * @brief mvp_player network client instance on server side
 */
class Peer : public IPeer
{
private:
    typedef Peer This;
public:
    Peer( boost::asio::io_service *ioService = nullptr );
    virtual ~Peer();
};

}
}
}

#endif
