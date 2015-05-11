#include "PluginLoader.hpp"
#include <mvp-player-core/Settings.hpp>

#include <boost-adds/environment.hpp>

#include <QtCore/QDir>
#include <QtCore/QPluginLoader>

namespace mvpplayer
{
namespace plugins
{

PluginLoader::PluginLoader()
{
}

PluginLoader::~PluginLoader()
{
}

void PluginLoader::unloadPlugins()
{
    _plugins.clear();
}

void PluginLoader::loadPlugins( const boost::filesystem::path & pluginsPath, mvpplayer::MVPPlayerEngine & model, mvpplayer::gui::IMVPPlayerDialog & view, mvpplayer::logic::MVPPlayerPresenter & presenter )
{
    QDir pluginsDir( pluginsPath.string().c_str() );

    std::cout << "Loading plugins from " << pluginsPath << std::endl;
    std::size_t progress = 0;
    Q_FOREACH( const QString & fileName, pluginsDir.entryList( QDir::Files ) )
    {
        std::cout << fileName.toStdString() << std::endl;
        QPluginLoader loader( pluginsDir.absoluteFilePath( fileName ) );
        loader.setLoadHints(QLibrary::ResolveAllSymbolsHint | QLibrary::ExportExternalSymbolsHint);
        QObject *plugin = loader.instance();
        if ( plugin )
        {
            std::cout << "Loaded: " << plugin->metaObject()->className() << std::endl; 
            IMVPPlugin * tgPlug = dynamic_cast<IMVPPlugin*>( plugin );
            if ( tgPlug )
            {
                std::string pluginName = tgPlug->pluginName();
                std::cout << "Plugin is: " << pluginName << std::endl;
                if ( _plugins.find( pluginName ) == _plugins.end() )
                {
                    _plugins.insert( pluginName, tgPlug );
                    tgPlug->setup( model, view, presenter );
                }
            }
            else
            {
                std::cout << "Warning: unable to cast plugin: " << fileName.toStdString() << std::endl;
            }
        }
        else
        {
            std::cerr << loader.errorString().toStdString() << std::endl;
        }
        ++progress;
    }
}

void PluginLoader::loadPlugins( mvpplayer::MVPPlayerEngine & model, mvpplayer::gui::IMVPPlayerDialog & view, mvpplayer::logic::MVPPlayerPresenter & presenter )
{
    using namespace boost::filesystem;
    // Try to read from application path
    path staticPath( current_path() );
#ifdef ANDROID
    staticPath /= "../lib";
#else
    staticPath /= "plugins";
#endif
    // Get plugin path from settings, environment variable or ./plugins
    boost::optional<std::string> envStr = boost::get_env( kMVPPlayerPluginEnvKey );
    std::string chosenPath;
    if ( Settings::getInstance().has( "plugins", "pluginsPath" ) )
    {
        chosenPath = Settings::getInstance().get<std::string>( "plugins", "pluginsPath" );
    }
    else
    {
        chosenPath = envStr.get_value_or( staticPath.string() );
    }
    loadPlugins( chosenPath, model, view, presenter );
}

}
}
