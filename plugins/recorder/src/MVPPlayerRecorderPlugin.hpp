#ifndef _MVPPLAYERRECORDERPLUGIN_HPP_
#define	_MVPPLAYERRECORDERPLUGIN_HPP_

#include <mvp-player-pluger/IMVPPlugin.hpp>

#include <QtGui/QtGui>
#include <QtCore/QtCore>

#ifndef Q_PLUGIN_METADATA
#define Q_PLUGIN_METADATA(...)
#endif

Q_DECLARE_INTERFACE( mvpplayer::plugins::IMVPPlugin, "org.djarlabs.mvpplayer.example.recorder.IMVPPlugin" );

namespace mvpplayer
{
namespace plugins
{

class MVPPlayerRecorderPlugin : public QObject, public IMVPPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA( IID "org.djarlabs.mvpplayer.example.recorder.IMVPPlugin" )
    Q_INTERFACES( mvpplayer::plugins::IMVPPlugin )

public:
    virtual void setup( MVPPlayerEngine & model, gui::IMVPPlayerDialog & view, logic::MVPPlayerPresenter & presenter );
};

}
}

#endif
