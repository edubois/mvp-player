#ifndef _MVPPLAYER_M3U_PARSER_HPP_
#define	_MVPPLAYER_M3U_PARSER_HPP_

#include <boost/filesystem/path.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/serialization/access.hpp>

#define BOOST_SPIRIT_UNICODE // We'll use unicode (UTF8) all throughout
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/repository/include/qi_subrule.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <boost/lexical_cast.hpp>

#include <vector>
#include <string>
#include <cassert>

namespace mvpplayer
{

namespace m3uParser
{

struct PlaylistItem
{
    PlaylistItem()
    : duration( -1 ) {}

    PlaylistItem( const std::string & filename )
    : filename( filename ), duration( -1 ) {}
    
    PlaylistItem( const std::string & filename, const long duration, const std::string & infos )
    : filename( filename ), duration( duration ), infos( infos ) {}

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & filename;
        ar & duration;
        ar & infos;
    }

    boost::filesystem::path filename;
    long duration;
    std::string infos;
};

}

namespace m3uParser
{

namespace details
{
namespace unicode = boost::spirit::unicode;
namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

/**
 *@brief construct a grammar for parsing expressions
 */
template <typename Iterator>
struct Grammar : qi::grammar<Iterator, std::vector<PlaylistItem>()>
{
    Grammar()
    : Grammar::base_type(entry)
    {
        using qi::lit;
        using qi::_val;
        using qi::eps;
        using qi::_1;
        using qi::_a;
        using qi::_b;
        using qi::_c;
        using unicode::char_;
        using qi::int_;
        using qi::lexeme;
        using qi::as_string;
        using phx::construct;
        using phx::push_back;

        extComment = lit( "#EXTREM:" ) >> *(char_ - qi::eol);
        rawPlaylistItem = as_string[ +(char_ - qi::eol) ];
        extPlaylistItem = ( lit( "#EXTINF:" ) >> int_[_a = _1] >> ',' >> as_string[ +(char_ - qi::eol) ][_b = _1] >> +qi::eol >> ( -lit( "file://" ) ) >> as_string[ +(char_ - qi::eol) ][_c = _1]  )[ _val = phx::construct<typename m3uParser::PlaylistItem>( _c, _a, _b ) ];
        entry = ( lit( "#EXTM3U" ) >> +qi::eol >> +( ( ( extPlaylistItem[ phx::push_back( _val, _1 ) ] ) | extComment ) >> *qi::eol ) )
                |
                ( +( rawPlaylistItem[ phx::push_back( _val, _1 ) ] >> *qi::eol ) >> *qi::eol );
    }

    // Create a starting rule with _val as a vector<double>
    qi::rule<Iterator, std::string() > extComment;          ///< For extended m3u: comments
    qi::rule<Iterator, PlaylistItem() > rawPlaylistItem;    ///< For raw m3u
    qi::rule<Iterator, PlaylistItem(), qi::locals<long, std::string, std::string> > extPlaylistItem;    ///< For extended m3u
    qi::rule<Iterator, std::vector<PlaylistItem>()> entry;
};
}

std::vector<PlaylistItem> parse( const boost::filesystem::path & filename );

}

}

#endif
