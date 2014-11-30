#ifndef DLGUTILS_HPP
#define	DLGUTILS_HPP

#include <boost/filesystem/path.hpp>
#include <string>

namespace mvpplayer
{
namespace gui
{

namespace qt
{
boost::filesystem::path openFile( const std::string & title, const std::string & extensions );

void displayError( const std::string & msg );
}

}
}

#endif	/* DLGUTILS_HPP */

