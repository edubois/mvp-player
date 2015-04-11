#include <mvp-player-core/MVPPlayerEngine.hpp>
#include <mvp-player-core/MVPPlayerLogic.hpp>
#include <mvp-player-core/SoundPlayer.hpp>
#include <mvp-player-gui/playerBehavior.hpp>
#include <mvp-player-qtgui/MVPPlayerLocalDialog.hpp>
#include <mvp-player-qtgui/MVPPlayerRemoteDialog.hpp>
#include <mvp-player-qtgui/resources.hpp>
#include <mvp-player-net/client/Client.hpp>
#include <mvp-player-net/server/Server.hpp>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSystemTrayIcon>
#include <QtCore/QCoreApplication>

// Change your GUI here (qt)
namespace gui = mvpplayer::gui::qt;

/**
 * @brief this is used to implement specific gui applications
 */
template<class Dialog>
int instanciateApp( int argc, char **argv )
{
    std::cerr << "Unimplented GUI" << std::endl;
}

/**
 * Specialization for QT remote gui (client)
 */
template<>
int instanciateApp<gui::MVPPlayerRemoteDialog>( int argc, char **argv )
{
    using Dialog = gui::MVPPlayerRemoteDialog;

    QApplication app( argc, argv );

    initResources();

    // Core (model): a sound player engine
    mvpplayer::MVPPlayerEngine playerEngine( &mvpplayer::SoundPlayer::getInstance() );
    mvpplayer::SoundPlayer::getInstance().setVolume( 0.0f );

    // Network remote
    mvpplayer::network::client::Client mvpPlayerClient;

    // Main dialog (view)
    Dialog dlg;

    // Presenter (presenter: logic-glu between model and view)
    mvpplayer::logic::MVPPlayerPresenter presenter;
    presenter.startStateMachine<mvpplayer::logic::PlayerStateMachine>();

    // Specific connections (be careful of the order here)

    // Display a message box on errors
    presenter.signalFailed.connect( boost::bind( &Dialog::displayError, &dlg, _1 ) );
    // When no file is provided and we hit play button, ask for a music file
    presenter.signalAskForFile.connect( boost::bind( &Dialog::openFile, &dlg, _1, "Musics (*.wav;*.flac;*.mp3;*.m3u);; All files (*.*)" ) );

    // Setup Model View Presenter behavior (binds the whole thing)
    mvpplayer::gui::setupMainBehavior( playerEngine, dlg, presenter );

    // React on mute event
    // We don't want to share this event
    dlg.signalViewMute.connect( [](const bool mute) { mvpplayer::SoundPlayer::getInstance().setVolume( mute == false ? 1.0f : 0.0f ); } );

    // Transfer events received from the network to the presenter's state machine
    mvpPlayerClient.signalEvent.connect( boost::bind( &mvpplayer::logic::MVPPlayerPresenter::processEvent, &presenter, _1 ) );
    // Spy presenter's events, and transfer them trhu the network
    presenter.signalEvent.connect( boost::bind( &mvpplayer::network::client::Client::sendEvent, &mvpPlayerClient, _1 ) );

    // Network setup
    dlg.signalViewConnect.connect(
        [&mvpPlayerClient, &dlg]()
        {
            bool ok = false;
            const QString serverIP = QInputDialog::getText( &dlg, QObject::tr("Connection"), QObject::tr("Server IP:"), QLineEdit::Normal, "127.0.0.1", &ok);
            if ( ok )
            {
                mvpPlayerClient.connect( serverIP.toStdString() );
            }
        }
    );
    dlg.signalViewDisconnect.connect( boost::bind( &mvpplayer::network::client::Client::disconnect, &mvpPlayerClient ) );

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
 * Specialization for QT gui (server)
 */
template<>
int instanciateApp<mvpplayer::gui::qt::MVPPlayerLocalDialog>( int argc, char **argv )
{
    using Dialog = mvpplayer::gui::qt::MVPPlayerLocalDialog;

    QApplication app( argc, argv );

    initResources();

    // Core (model): a sound player engine
    mvpplayer::MVPPlayerEngine playerEngine( &mvpplayer::SoundPlayer::getInstance() );
    mvpplayer::network::server::Server mvpPlayerServer;

    // Main dialog (view)
    QSystemTrayIcon trayIcon( QIcon( ":/mvpplayer/action/play.png" ) );
    trayIcon.setVisible( true );

    Dialog dlg;

    // Presenter (presenter: logic-glu between model and view)
    mvpplayer::logic::MVPPlayerPresenter presenter;
    presenter.startStateMachine<mvpplayer::logic::PlayerStateMachine>();

    // Specific connections (be careful of the order here)

    // Display a message box on errors
    presenter.signalFailed.connect( boost::bind( &Dialog::displayError, &dlg, _1 ) );
    // When no file is provided and we hit play button, ask for a music file
    presenter.signalAskForFile.connect( boost::bind( &Dialog::openFile, &dlg, _1, "Musics (*.wav;*.flac;*.mp3;*.m3u);; All files (*.*)" ) );

    // Setup Model View Presenter behavior (binds the whole thing)
    mvpplayer::gui::setupMainBehavior( playerEngine, dlg, presenter );

    // Transfer events received from the network to the presenter's state machine
    mvpPlayerServer.signalEventFrom.connect( boost::bind( &mvpplayer::logic::MVPPlayerPresenter::processEvent, &presenter, _2 ) );
    // Spy presenter's events, and transfer them trhu the network
    presenter.signalEvent.connect( boost::bind( &mvpplayer::network::server::Server::sendEventMulticast, &mvpPlayerServer, _1 ) );

    mvpPlayerServer.signalNewClient.connect(
        [&trayIcon](const std::string &clientAddress)
        {
            trayIcon.showMessage( QObject::tr("MVPPlayer"), QObject::tr( "New client: " ) + QString::fromStdString( clientAddress ), QSystemTrayIcon::Information, 5000 );
        }
    );
    // Network setup
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
#ifdef FORCE_REMOTE_BY_DEFAULT
        return instanciateApp<gui::MVPPlayerRemoteDialog>( argc, argv );
#else
    if ( argc > 1 && ( std::string( argv[1] ) == "--remote" || std::string( argv[1] ) == "-r" ) )
    {
        return instanciateApp<gui::MVPPlayerRemoteDialog>( argc, argv );
    }
    else
    {
        return instanciateApp<gui::MVPPlayerLocalDialog>( argc, argv );
    }
#endif
}
