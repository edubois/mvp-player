#ifndef _WINFUN_HPP_
#define	_WINFUN_HPP_

#include <ncurses.h>

namespace mvpplayer
{
namespace gui
{
namespace ncurses
{

WINDOW *createNewWin(int height, int width, int starty, int startx);
void destroyWin( WINDOW * win );

}
}
}

#endif
