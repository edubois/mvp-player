#include "MVPPlayerRecorderLogic.hpp"

namespace mvpplayer
{
namespace logic
{
namespace plugin
{

/**
 * @brief reaction on record event
 */
sc::result Recording::react( const EvRecord & ev )
{
    boost::optional<boost::filesystem::path> answer = context< PlayerStateMachine >().presenter.askForFile( _tr( "Save record as..." ), eFileDialogModeSave );
    if ( answer && !answer.get().empty() )
    {
        // Trigger recording into provided filename
        RecorderPluginPresenter & plugPresenter = context< PlayerStateMachine >().presenter.presenterOfPlugin<RecorderPluginPresenter>( "recorderPlugin" );
        plugPresenter.signalRecord( *answer );
        return transit< Recording >();
    }
    return discard_event();
}

}
}
}
