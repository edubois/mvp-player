#include "trackTools.hpp"

#include <cmath>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>

namespace mvpplayer
{

/**
 * @brief transform track length from milliseconds to display string
 * @param lengthInMS track length in milliseconds
 * @return a string
 */
std::string trackLengthToString( const std::size_t lengthInMS )
{
    using namespace std::chrono;
    milliseconds d( lengthInMS );
    auto hhh = duration_cast<hours>(d);
    d -= hhh;
    auto mm = duration_cast<minutes>(d);
    d -= mm;
    auto ss = duration_cast<seconds>(d);

    std::ostringstream stream;
    if ( hhh.count() )
    {
        const int sz = std::log( hhh.count() ) / std::log( 10 ) + 1.01;
        stream << std::setfill('0') << std::setw( sz ) << hhh.count() << ':';
    }

    stream << std::setfill('0') << std::setw(2) << mm.count() << ':'
           << std::setfill('0') << std::setw(2) << ss.count();
    return stream.str();
}

}
