#include "Peer.hpp"

namespace mvpplayer
{
namespace network
{
namespace client
{

Peer::Peer( boost::asio::io_service *ioService )
: IPeer( ioService )
{
}

Peer::~Peer()
{
}

}
}
}
