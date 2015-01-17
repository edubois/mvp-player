#ifndef _MVPPLAYER_CLIENT_PEER_HPP_
#define	_MVPPLAYER_CLIENT_PEER_HPP_

#include <mvp-player-net/IPeer.hpp>

namespace mvpplayer
{
namespace network
{
namespace client
{

/**
 * @brief mvp_player network peer representing server
 */
class Peer : public IPeer
{
private:
    typedef Peer This;
public:
    Peer( boost::asio::io_service *ioService );
    virtual ~Peer();
};

}
}
}

#endif
