#include "PluginLoader.hpp"

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

void PluginLoader::loadPlugins( const boost::filesystem::path & pluginsPath, mvpplayer::MVPPlayerEngine & model, mvpplayer::gui::IMVPPlayerDialog & view, mvpplayer::logic::MVPPlayerPresenter & presenter )
{
    QDir pluginsDir( pluginsPath.string().c_str() );

    std::cout << "Loading plugins from " << pluginsPath << std::endl;
    std::size_t count = pluginsDir.entryList( QDir::Files ).size();
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
            IMVPPlugin * tgPlug = qobject_cast<IMVPPlugin*>( plugin );
            if ( tgPlug )
            {
                std::cout << "Plugin is: " << tgPlug->pluginName() << std::endl;
                _plugins[ tgPlug->pluginName() ] = tgPlug;
                tgPlug->setup( model, view, presenter );
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
    // Get plugin path from environment variable or ./plugins
    boost::optional<std::string> envStr = boost::get_env( "MVPPLAYER_PLUGIN_PATH" );
    std::string chosenPath = envStr.get_value_or( staticPath.string() );
    loadPlugins( chosenPath, model, view, presenter );
}

}
}
