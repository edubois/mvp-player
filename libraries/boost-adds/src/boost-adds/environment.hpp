#ifndef _BOOSTADDS_ENVIRONMENT_HPP_
#define	_BOOSTADDS_ENVIRONMENT_HPP_

#include "shared.hpp"

#include <string>
#include <boost/optional.hpp>
#include <cstdlib>

namespace boost
{

BUILD_DLL boost::optional<std::string> get_env( const std::string & name );

}

#endif

