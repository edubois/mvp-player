#include "Peer.hpp"

namespace mvpplayer
{
namespace network
{
namespace server
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
