#include "environment.hpp"

namespace boost
{

boost::optional<std::string> get_env( const std::string & name )
{
    char *var = getenv(name.c_str());
    if( var )
    {
        return std::string( var );
    }
    else
    {
        return boost::none_t();
    }
}

}
