#include "winFun.hpp"

namespace mvpplayer
{
namespace gui
{
namespace ncurses
{

WINDOW *createNewWin(int height, int width, int starty, int startx)
{
    WINDOW *localWin;

	localWin = newwin( height, width, starty, startx );
	box( localWin, 0 , 0 );
	wrefresh(localWin); // Show the window's box

	return localWin;
}

void destroyWin( WINDOW * win )
{
    wborder( win, ' ', ' ', ' ',' ',' ',' ',' ',' ' );
	wrefresh( win );
	delwin( win );
}

}
}
}
