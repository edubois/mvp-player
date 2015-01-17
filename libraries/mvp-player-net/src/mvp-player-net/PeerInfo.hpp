#ifndef _MVPPLAYER_NETWORK_PEERINFO_HPP_
#define	_MVPPLAYER_NETWORK_PEERINFO_HPP_

#include <boost/serialization/access.hpp>
#include <boost/serialization/serialization.hpp>

#include <string>
#include <cstddef>

namespace mvpplayer
{
namespace network
{
static const unsigned short kProtocolVersionMinor = 0;
static const unsigned short kProtocolVersionMajor = 1;

/**
 * @brief peer information
 */
struct PeerInfo
{
    friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & peerName;
		ar & protocolVersionMajor;
		ar & protocolVersionMinor;
	}

    std::string peerName;
    unsigned short protocolVersionMajor;
    unsigned short protocolVersionMinor;
};

}
}

#endif
