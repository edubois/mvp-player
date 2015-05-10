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

    presenter.registerPluginPresenter( kMVPPlayerPluginName, _plugPresenter );
    _plugPresenter.signalRecord.connect( boost::bind( &MVPPlayerRecorderPlugin::record, this, _1 ) );
    _plugPresenter.signalStopRecord.connect( boost::bind( &SoundRecorder::stopRecording, &SoundRecorder::getInstance() ) );
    _plugPresenter.signalStopRecord.connect( boost::bind( &logic::MVPPlayerPresenter::processCommandActive, &presenter, std::string( "Record" ), false ) );
}

/**
 * Triggered when the user click on the record button
 */
void MVPPlayerRecorderPlugin::recordClicked( const bool activated )
{
    if ( activated )
    {
        // Stop current action
        _presenter->processStop();
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
boost::statechart::detail::reaction_result MVPPlayerRecorderPlugin::recordTransition( const std::string & action, logic::Stopped & state )
{
    if ( action == kRecordAction )
    {
        // The following is needed to silent assert in boost
        const auto result = state.transit<logic::plugin::Recording>();
        const auto consume = sc::detail::result_utility::get_result( result );
        return boost::statechart::detail::consumed;
    }
    else
    {
        return boost::statechart::detail::no_reaction;
    }
}

/**
 * Triggered when we want to start the recording in a file
 * @param filename output filename
 */
void MVPPlayerRecorderPlugin::record( const boost::filesystem::path & filename )
{
    // Recording goes here:
    SoundRecorder::getInstance().stopRecording();
    SoundRecorder::getInstance().setFilename( filename );
    SoundRecorder::getInstance().signalVolumeHigh.connect( boost::bind( &MVPPlayerRecorderPlugin::playTrack, this ) );
    SoundRecorder::getInstance().startRecording();
}

void MVPPlayerRecorderPlugin::playTrack()
{
    // Queue stop event
    _presenter->processStop();
    _presenter->processPlay( boost::none );
}


}
}

#if (QT_VERSION < 0x050000)
Q_EXPORT_PLUGIN2( mvpplayer::plugins::MVPPlayerRecorderPlugin, MVPPlayerRecorderPlugin )
#endif // (QT_VERSION >= 0x050000)
