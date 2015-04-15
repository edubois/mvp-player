#include "MVPPlayerRecorderPlugin.hpp"
#include "SoundRecorder.hpp"

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QApplication>
#include <boost/filesystem/path.hpp>

namespace mvpplayer
{
namespace plugins
{

void MVPPlayerRecorderPlugin::setup( MVPPlayerEngine & model, gui::IMVPPlayerDialog & view, logic::MVPPlayerPresenter & presenter )
{
    // Call base class' setup
    IMVPPlugin::setup( model, view, presenter );
    // Intercept record button click
    view.signalViewHitButton.connect( [this, &presenter]( const std::string & commandName, const bool record ) { if ( commandName == "Record" ) this->recordClicked( record ); } );
    SoundRecorder::getInstance().setSampleRate( 44100 );
    SoundRecorder::getInstance().setBitDepth( 16 );
    SoundRecorder::getInstance().setChannels( 1 );
    presenter.askStoppedStateExternalTransition.connect( boost::bind( &MVPPlayerRecorderPlugin::recordTransition, this, _1, _2 ) );
}

/**
 * Triggered when the user click on the record button
 */
void MVPPlayerRecorderPlugin::recordClicked( const bool activated )
{
    if ( activated )
    {
        // Queue custom event to enter the right plugin recording state
        {
            using EventT = logic::EvCustomState;
            EventT *event = new EventT( kRecordAction );
            _presenter->signalEvent( *event );
            _presenter->processEvent( *event );
        }
        // Queue record event
        {
            using EventT = logic::plugin::EvRecord;
            EventT *event = new EventT();
            _presenter->signalEvent( *event );
            _presenter->processEvent( *event );
        }
    }
    else
    {
        // Queue stop event
        _presenter->processStop();
    }
}

/**
 * @brief Needed to enter into the Recording state
 */
boost::statechart::result MVPPlayerRecorderPlugin::recordTransition( const std::string & action, logic::Stopped & state )
{
    if ( action == kRecordAction )
    {
        return state.transit<logic::plugin::Recording>();
    }
    else
    {
        return boost::statechart::result( boost::statechart::detail::no_reaction );
    }
}

}
}

#if (QT_VERSION < 0x050000)
Q_EXPORT_PLUGIN2( mvpplayer::plugins::MVPPlayerRecorderPlugin, MVPPlayerRecorderPlugin )
#endif // (QT_VERSION >= 0x050000)
