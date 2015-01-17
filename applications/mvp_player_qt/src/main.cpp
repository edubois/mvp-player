#include <mvp-player-core/MVPPlayerEngine.hpp>
#include <mvp-player-core/MVPPlayerLogic.hpp>
#include <mvp-player-core/SoundPlayer.hpp>
#include <mvp-player-gui/playerBehavior.hpp>
#include <mvp-player-qtgui/MVPPlayerDialog.hpp>
#include <mvp-player-qtgui/resources.hpp>
#include <mvp-player-net/server/Server.hpp>

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

    initResources();

    // Core (model): a sound player engine
    mvpplayer::MVPPlayerEngine playerEngine( &mvpplayer::SoundPlayer::getInstance() );
    mvpplayer::network::server::Server mvpPlayerServer;

    // Main dialog (view)
    mvpplayer::gui::qt::MVPPlayerDialog dlg;

    // Presenter (presenter: logic-glu between model and view)
    mvpplayer::logic::MVPPlayerPresenter presenter;
    presenter.startStateMachine<mvpplayer::logic::PlayerStateMachine>();

    // Specific connections (be careful of the order here)

    // Display a message box on errors
    presenter.signalFailed.connect( boost::bind( &mvpplayer::gui::qt::MVPPlayerDialog::displayError, &dlg, _1 ) );
    // When no file is provided and we hit play button, ask for a music file
    presenter.signalAskForFile.connect( boost::bind( &mvpplayer::gui::qt::MVPPlayerDialog::openFile, &dlg, _1, "Musics (*.wav;*.m3u)" ) );

    // Setup Model View Presenter behavior (binds the whole thing)
    mvpplayer::gui::setupMainBehavior( playerEngine, dlg, presenter );

    // Network connexion
    dlg.signalViewStartServer.connect( boost::bind( &mvpplayer::network::server::Server::run, &mvpPlayerServer ) );
    dlg.signalViewStopServer.connect( boost::bind( &mvpplayer::network::server::Server::stop, &mvpPlayerServer ) );

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
