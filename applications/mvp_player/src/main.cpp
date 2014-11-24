#include "dlgUtils.hpp"
#include "mvp-player-core/MVPPlayerEngine.hpp"
#include "mvp-player-core/MVPPlayerLogic.hpp"
#include "mvp-player-qtgui/MVPPlayerDialog.hpp"

#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>

/**
 * @note: See how this file is clear allowing an easy setup/fix of the application's behavior
 * @note: You can, by that way, make a console application very quickly.
 */

void setupBehavior( mvpplayer::MVPPlayerEngine & m, mvpplayer::gui::qt::MVPPlayerDialog & v, mvpplayer::logic::PlayerStateMachine & p );

int main( int argc, char **argv )
{
    QApplication app( argc, argv );

    // Core (model)
    mvpplayer::MVPPlayerEngine playerEngine;

    // QT Gui (view)
    mvpplayer::gui::qt::MVPPlayerDialog dlg;

    // Presenter (presenter: logic-glu between model and view)
    mvpplayer::logic::PlayerStateMachine playerLogic;

    // Setup Model View Presenter behavior (binds the whole thing)
    setupBehavior( playerEngine, dlg, playerLogic );

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
 * @brief Setup music player's behavior (connect signals between the model/view/presenter)
 */
void setupBehavior( mvpplayer::MVPPlayerEngine & m, mvpplayer::gui::qt::MVPPlayerDialog & v, mvpplayer::logic::PlayerStateMachine & p )
{
    //@{ Connections (behavior)

    // When we hit play button, we want to react by sending a play event to the state machine
    v.signalViewHitPlay.connect( boost::bind( &mvpplayer::logic::PlayerStateMachine::processPlay, &p, _1 ) );
    // When we hit stop button, we want to react by sending a stop event to the state machine
    v.signalViewHitStop.connect( boost::bind( &mvpplayer::logic::PlayerStateMachine::processStop, &p ) );
    // Connect played event to the engine play file function
    p.signalPlayedTrack.connect( boost::bind( &mvpplayer::MVPPlayerEngine::playFile, &m, _1 ) );
    // Connect stop event to stop the current played track
    p.signalStopTrack.connect( boost::bind( &mvpplayer::MVPPlayerEngine::stop, &m ) );
    
    // Connect played event to display track filename function
    p.signalPlayedTrack.connect( boost::bind( &mvpplayer::gui::qt::MVPPlayerDialog::setCurrentTrack, &v, _1 ) );
    // Connect stop event to change play button to [*]
    p.signalPlayedTrack.connect( boost::bind( &mvpplayer::gui::qt::MVPPlayerDialog::setIconStop, &v ) );
    // Connect stop event to display empty track filename
    p.signalStopTrack.connect( boost::bind( &mvpplayer::gui::qt::MVPPlayerDialog::setCurrentTrack, &v, boost::filesystem::path() ) );
    // Connect stop event to change play button to |>
    p.signalStopTrack.connect( boost::bind( &mvpplayer::gui::qt::MVPPlayerDialog::setIconPlay, &v ) );
    // Display a message box on errors
    p.signalFailed.connect( boost::bind( &mvpplayer::gui::displayError, _1 ) );

    // When no file is provided and we hit play button, ask for a music file
    p.signalAskForFile.connect( boost::bind( &mvpplayer::gui::openFile, _1, "Musics (*.wav)" ) );
    
    //@}
}
