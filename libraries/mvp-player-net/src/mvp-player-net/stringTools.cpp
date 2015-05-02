#include "stringTools.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>

namespace mvpplayer
{
namespace network
{

/**
 * @brief remove port from string (ex. 127.0.0.1:1234 -> 127.0.0.1)
 * @param hostname hostname
 * @return hostname without tailing ':port'
 */
std::string removePort( const std::string & hostname )
{
    std::vector<std::string> items;
    boost::split( items, hostname, boost::is_any_of( ":" ) );
    if ( items.size() )
    {
        return items[0];
    }
    else
    {
        return hostname;
    }
}

/**
 * @brief remove hostname from string (ex. 127.0.0.1:1234 -> 1234)
 * @param hostname hostname
 * @return port without heading 'hostname:'
 */
unsigned short removeHostname( const std::string & hostname )
{
    std::string port = hostname;
    std::vector<std::string> items;
    boost::split( items, hostname, boost::is_any_of( ":" ) );
    if ( items.size() )
    {
        port = items[1];
    }

    try
    {
        return boost::lexical_cast<unsigned short>( port );
    }
    catch( boost::bad_lexical_cast& )
    {
        return 0;
    }
}

}
}
