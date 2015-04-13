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
     */
    void recordClicked();
};

}
}

#endif
