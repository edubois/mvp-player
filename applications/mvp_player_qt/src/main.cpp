#include "dlgUtils.hpp"
#include <mvp-player-gui/playerBehavior.hpp>
#include <mvp-player-qtgui/MVPPlayerDialog.hpp>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QtCore/QCoreApplication>

// Change your GUI here (qt)
namespace gui = mvpplayer::gui::qt;

/**
 * @brief this is used to implement specific gui applications
 */
template<class Dialog>
int instanciateApp( int argc, char **argv )
{}

/**
 * Specialization for QT gui
 */
template<>
int instanciateApp<mvpplayer::gui::qt::MVPPlayerDialog>( int argc, char **argv )
{
    QApplication app( argc, argv );

    // Core (model)
    mvpplayer::MVPPlayerEngine playerEngine;

    // Main dialog (view)
    mvpplayer::gui::qt::MVPPlayerDialog::MVPPlayerDialog dlg;

    // Presenter (presenter: logic-glu between model and view)
    mvpplayer::logic::PlayerStateMachine playerLogic;

    // Additionnal specific connections

    // Display a message box on errors
    playerLogic.signalFailed.connect( boost::bind( &mvpplayer::gui::qt::displayError, _1 ) );
    // When no file is provided and we hit play button, ask for a music file
    playerLogic.signalAskForFile.connect( boost::bind( &mvpplayer::gui::qt::openFile, _1, "Musics (*.wav)" ) );

    // Setup Model View Presenter behavior (binds the whole thing)
    mvpplayer::gui::setupMainBehavior( playerEngine, dlg, playerLogic );

    if ( !dlg.exec() )
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief main goes here
 */
int main( int argc, char **argv )
{
    return instanciateApp<gui::MVPPlayerDialog>( argc, argv );
}
