#ifndef _MVP_PLAYER_NCURSES_GUI_FILEUTILS_HPP_
#define	_MVP_PLAYER_NCURSES_GUI_FILEUTILS_HPP_

#include <ncurses.h>
#include <cdk.h>

#include <boost/filesystem/path.hpp>
#include <string>

namespace mvpplayer
{
namespace gui
{
namespace ncurses
{

boost::filesystem::path openFile( CDKSCREEN* cdkscreen, const std::string & title, const std::string & extensions );

}
}
}

#endif
