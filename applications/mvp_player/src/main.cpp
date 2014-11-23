#include "mvp-player-qtgui/MVPPlayerDialog.hpp"

#include <QtWidgets/QApplication>

int main( int argc, char **argv )
{
    QApplication app( argc, argv );

    mvpplayer::gui::qt::MVPPlayerDialog dlg;
    if ( !dlg.exec() )
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
