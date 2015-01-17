#ifndef _MVPPLAYER_NETWORK_DATA_HPP_
#define	_MVPPLAYER_NETWORK_DATA_HPP_

#include <boost/shared_array.hpp>
#include <boost/cstdint.hpp>

namespace mvpplayer
{
namespace network
{

struct Data
{
    Data()
    {}

    Data( const boost::uint8_t* buffer_, const boost::uint32_t length_ )
    : length( length_ )
    , buffer( new boost::uint8_t[ length_ ] )
    { memcpy( buffer.get(), buffer_, length_ ); }

    boost::uint32_t length;
    boost::shared_array<boost::uint8_t> buffer;
};

}
}

#endif
