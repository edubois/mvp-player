#include "dlgUtils.hpp"
#include <mvp-player-core/MVPPlayerEngine.hpp>
#include <mvp-player-core/MVPPlayerLogic.hpp>
#include <mvp-player-gui/playerBehavior.hpp>
#include <mvp-player-ncursesgui/MVPPlayerDialog.hpp>
#include <mvp-player-ncursesgui/fileUtils.hpp>
#include <mvp-player-core/SoundPlayer.hpp>

#include <QtCore/QCoreApplication>

#include <curses.h>
#include <cdk.h>

// Change your GUI here (qt or ncurses)
namespace gui = mvpplayer::gui::ncurses;

/**
 * @brief this is used to implement specific gui applications
 */
template<class Dialog>
int instanciateApp( int argc, char **argv )
{}

/**
 * Specialization for ncurses (console) gui
 */
template<>
int instanciateApp<mvpplayer::gui::ncurses::MVPPlayerDialog>( int argc, char **argv )
{
    // Only needed to use QSound
    QCoreApplication app( argc, argv );

    int ret = 0;
    WINDOW* mainwin = initscr();
    CDKSCREEN* cdkscreen = initCDKScreen( mainwin );
    initCDKColor();

    {
        // Core (model)
        mvpplayer::MVPPlayerEngine playerEngine( &mvpplayer::SoundPlayer::getInstance() );

        // Main dialog (view)
        mvpplayer::gui::ncurses::MVPPlayerDialog dlg( cdkscreen, 30, 10, 5, 5 );

        // Presenter (presenter: logic-glu between model and view)
        mvpplayer::logic::MVPPlayerPresenter presenter;
        presenter.startStateMachine<mvpplayer::logic::PlayerStateMachine>();

        // Specific connections (be careful of the order here)

        // Display a message box on errors
        presenter.signalFailed.connect( boost::bind( &mvpplayer::gui::ncurses::displayError, cdkscreen, _1 ) );
        // When no file is provided and we hit play button, ask for a music file
        presenter.signalAskForFile.connect( boost::bind( &mvpplayer::gui::ncurses::openFile, cdkscreen, _1, "Musics (*.wav, *.m3u)" ) );

        // Setup Model View Presenter behavior (binds the whole thing)
        mvpplayer::gui::setupMainBehavior( playerEngine, dlg, presenter );

        if ( !dlg.exec() )
        { ret = -1; }
    }

    destroyCDKScreen( cdkscreen );
    endCDK();
    delwin( mainwin );
    return ret;
}

/**
 * @brief main goes here
 */
int main( int argc, char **argv )
{
    return instanciateApp<gui::MVPPlayerDialog>( argc, argv );
}
