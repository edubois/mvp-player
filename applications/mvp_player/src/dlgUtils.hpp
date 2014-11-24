/* 
 * File:   dlgUtils.hpp
 * Author: admin
 *
 * Created on 24 novembre 2014, 03:02
 */

#ifndef DLGUTILS_HPP
#define	DLGUTILS_HPP

#include <boost/filesystem/path.hpp>
#include <string>

namespace mvpplayer
{
namespace gui
{

boost::filesystem::path openFile( const std::string & title, const std::string & extensions );

void displayError( const std::string & msg );

}
}

#endif	/* DLGUTILS_HPP */

