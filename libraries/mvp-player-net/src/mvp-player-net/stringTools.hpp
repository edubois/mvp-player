#ifndef _NET_STRINGTOOLS_HPP_
#define	_NET_STRINGTOOLS_HPP_

#include <string>

namespace mvpplayer
{
namespace network
{

/**
 * @brief remove port from string (ex. 127.0.0.1:1234 -> 127.0.0.1)
 * @param hostname hostname
 * @return hostname without tailing ':port'
 */
std::string removePort( const std::string & hostname );

/**
 * @brief remove hostname from string (ex. 127.0.0.1:1234 -> 1234)
 * @param hostname hostname
 * @return port without heading 'hostname:'
 */
unsigned short removeHostname( const std::string & hostname );

}
}

#endif
