#ifndef _PLUG_MVPPLAYERRECORDERPLUGIN_HPP_
#define	_PLUG_MVPPLAYERRECORDERPLUGIN_HPP_

#include "MVPPlayerRecorderLogic.hpp"

#include <mvp-player-pluger/IMVPPlugin.hpp>

#include <QtGui/QtGui>
#include <QtCore/QtCore>

#ifndef Q_PLUGIN_METADATA
#define Q_PLUGIN_METADATA(...)
#endif

Q_DECLARE_INTERFACE( mvpplayer::plugins::IMVPPlugin, "org.djarlabs.mvpplayer.plugins.IMVPPlugin/1.0" );

namespace mvpplayer
{
namespace plugins
{
static const std::string kMVPPlayerPluginName( "recorderPlugin" );
static const std::string kRecordAction( "kRecordAction" );

class MVPPlayerRecorderPlugin : public IMVPPlugin
{
    Q_OBJECT
    Q_INTERFACES( mvpplayer::plugins::IMVPPlugin )
    Q_PLUGIN_METADATA( IID "org.djarlabs.mvpplayer.plugins.mvpPlayerRecorderPlugin" FILE "mvpPlayerRecorderPlugin.json" )
public:
    MVPPlayerRecorderPlugin()
    : IMVPPlugin( kMVPPlayerPluginName )
    {}
    
    virtual void setup( MVPPlayerEngine & model, gui::IMVPPlayerDialog & view, logic::MVPPlayerPresenter & presenter );

    /**
     * Triggered when the user click on the record button
     * @param record shall we record or stop recording ?
     */
    void recordClicked( const bool record );
    
    /**
     * @brief Needed to enter into the Recording state
     */
    boost::statechart::detail::reaction_result recordTransition( const std::string & action, logic::Stopped & state );

    /**
     * Triggered when we want to start the recording in a file
     * @param filename output filename
     */
    void record( const boost::filesystem::path & filename );

    /**
     * @brief Triggered when we want to play a track after a volume high triggering
     */
    void playTrack();

private:
    logic::plugin::RecorderPluginPresenter _plugPresenter;
};

}
}

#endif
