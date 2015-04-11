#include "MVPPlayerRecorderPlugin.hpp"

namespace mvpplayer
{
namespace plugins
{

void MVPPlayerRecorderPlugin::setup( MVPPlayerEngine & model, gui::IMVPPlayerDialog & view, logic::MVPPlayerPresenter & presenter )
{
    
}

}
}

#if (QT_VERSION < 0x050000)
Q_EXPORT_PLUGIN2( mvpplayer::plugins::MVPPlayerRecorderPlugin, MVPPlayerRecorderPlugin )
#endif // (QT_VERSION >= 0x050000)
