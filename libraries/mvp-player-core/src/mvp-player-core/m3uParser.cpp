#include "m3uParser.hpp"
#include <sstream>
#include <fstream>

namespace
{
    std::string slurp( const boost::filesystem::path & filename )
    {
        std::ifstream filein( filename.string().c_str(), std::ios::in );
        if ( filein.good() )
        {
            return static_cast<std::stringstream const&>(std::stringstream() << filein.rdbuf()).str();
        }
        else
        {
            return std::string();
        }
    }
}

namespace mvpplayer
{

namespace m3uParser
{

std::vector<PlaylistItem> parse( const boost::filesystem::path & filename )
{
    using namespace boost::spirit;
    const std::string content = slurp( filename );
    
    std::vector<PlaylistItem> vec;
    typedef std::string::const_iterator iterator_t;
    details::Grammar<iterator_t> g;
    iterator_t itBegin = content.begin();
    iterator_t itEnd = content.end();
    std::string v;
    phrase_parse( itBegin, itEnd, g, +qi::space, vec );
    return vec;
}

}

}
