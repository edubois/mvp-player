#ifndef _PLUGER_PLUGINLOADER_HPP_
#define	_PLUGER_PLUGINLOADER_HPP_

#include <mvp-player-core/Singleton.hpp>
#include <mvp-player-core/MVPPlayerPresenter.hpp>
#include <mvp-player-core/MVPPlayerEngine.hpp>
#include <mvp-player-gui/IMVPPlayerDialog.hpp>

#include "IMVPPlugin.hpp"

#include <boost/filesystem/path.hpp>
#include <map>

namespace mvpplayer
{
namespace plugins
{

class PluginLoader : public Singleton<PluginLoader>
{
public:
    PluginLoader();
    virtual ~PluginLoader();

    void loadPlugins( const boost::filesystem::path & pluginsPath, mvpplayer::MVPPlayerEngine & model, mvpplayer::gui::IMVPPlayerDialog & view, mvpplayer::logic::MVPPlayerPresenter & presenter );
    void loadPlugins( mvpplayer::MVPPlayerEngine & model, mvpplayer::gui::IMVPPlayerDialog & view, mvpplayer::logic::MVPPlayerPresenter & presenter );

private:
    std::map<std::string, IMVPPlugin*> _plugins;    ///< Plugins loaded
};

}
}

#endif
