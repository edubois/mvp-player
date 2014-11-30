#ifndef _NCURSES_DLGUTILS_HPP_
#define	_NCURSES_DLGUTILS_HPP_

#include <boost/filesystem/path.hpp>
#include <string>

#include <cdk.h>

namespace mvpplayer
{
namespace gui
{

namespace ncurses
{
    
boost::filesystem::path openFile( CDKSCREEN* cdkscreen, const std::string & title, const std::string & extensions );
void displayError( CDKSCREEN* cdkscreen, const std::string & msg );

}

}
}

#endif
