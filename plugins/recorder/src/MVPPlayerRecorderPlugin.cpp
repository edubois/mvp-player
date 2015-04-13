#include "MVPPlayerRecorderPlugin.hpp"

namespace mvpplayer
{
namespace plugins
{

void MVPPlayerRecorderPlugin::setup( MVPPlayerEngine & model, gui::IMVPPlayerDialog & view, logic::MVPPlayerPresenter & presenter )
{
    // Call base class' setup
    IMVPPlugin::setup( model, view, presenter );
    // Intercept record button click
    view.signalViewHitButton.connect( [this, &presenter]( const std::string & commandName ) { if ( commandName == "Record" ) this->recordClicked(); } );
}

/**
 * Triggered when the user click on the record button
 */
void MVPPlayerRecorderPlugin::recordClicked()
{
    std::cout << "Record!" << std::endl;
}

}
}

#if (QT_VERSION < 0x050000)
Q_EXPORT_PLUGIN2( mvpplayer::plugins::MVPPlayerRecorderPlugin, MVPPlayerRecorderPlugin )
#endif // (QT_VERSION >= 0x050000)
