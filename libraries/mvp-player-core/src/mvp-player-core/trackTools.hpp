#ifndef _MVPPLAYER_CORE_TRACKTOOLS_HPP_
#define	_MVPPLAYER_CORE_TRACKTOOLS_HPP_

#include <string>

namespace mvpplayer
{

/**
 * @brief transform track length from milliseconds to a display string
 * @param lengthInMS track length in milliseconds
 * @return a string
 */
std::string trackLengthToString( const std::size_t lengthInMS );

}

#endif
