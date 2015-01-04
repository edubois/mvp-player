#ifndef _NCURSES_DLGUTILS_HPP_
#define	_NCURSES_DLGUTILS_HPP_

#include <string>

#include <cdk.h>

namespace mvpplayer
{
namespace gui
{

namespace ncurses
{

void displayError( CDKSCREEN* cdkscreen, const std::string & msg );

}

}
}

#endif
