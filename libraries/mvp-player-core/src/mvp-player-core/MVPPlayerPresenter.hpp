#ifndef _CORE_MVPPLAYERPRESENTER_HPP_
#define	_CORE_MVPPLAYERPRESENTER_HPP_

#include "stateMachineEvents.hpp"

#include <boost/statechart/fifo_scheduler.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/signals2.hpp>
#include <boost/thread.hpp>
#include <map>

namespace mvpplayer
{
namespace logic
{
struct Stopped;
struct Playing;

namespace sc = boost::statechart;

enum EFileDialogMode { eFileDialogModeOpen, eFileDialogModeSave };

namespace details
{

class SchedulerWorker
{
public:
    SchedulerWorker( sc::fifo_scheduler<> & scheduler )
    : _scheduler( scheduler )
    , _stopped( true )
    {
    }
    
    ~SchedulerWorker()
    {
        join();
    }

    inline void start()
    {
        _thread.reset( new boost::thread( boost::bind( &SchedulerWorker::work, this ) ) );
    }
    
    inline void join()
    {
        _thread->interrupt();
        _scheduler.terminate();
        _thread->join();
    }
    
    inline boost::mutex & mutex() const
    { return _mutex; }
    
    inline bool stopped() const
    { return _stopped; }

private:    
    void work()
    {
        _stopped = false;
        try
        {
            while( 1 )
            {
                _scheduler( 1 );
                boost::this_thread::interruption_point();
                // Needed to handle pause in event processing
                boost::mutex::scoped_lock lock( _mutex );
            }
        }
        catch( boost::thread_interrupted& )
        {
        }
        
        _stopped = true;
    }

private:
    sc::fifo_scheduler<> & _scheduler;
    bool _stopped;
    std::unique_ptr<boost::thread> _thread;
    mutable boost::mutex _mutex;
};

}

/**
 * @brief For plugins
 * Put your custom plugin signals in a class inheriting from this class
 */
struct IPluginPresenter : public boost::signals2::trackable
{
    virtual ~IPluginPresenter() {}
};

/**
 * @brief the presenter is the glue between the model and the view,
 *        it also contains the player's state machine
 */
class MVPPlayerPresenter : public boost::signals2::trackable
{
public:
    MVPPlayerPresenter()
    : _scheduler( true )
    , _schedulerWorker( _scheduler )
    {}
    
    ~MVPPlayerPresenter()
    {
    }

    template<class M>
    void startStateMachine( const bool startScheduler = true )
    {
        // Create an event processor for the state machine M (template parameter)
        _playerProcessor = _scheduler.create_processor< M >( boost::ref( *this ) );
        _scheduler.initiate_processor( _playerProcessor );
        // Start thread
        _schedulerWorker.start();
    }

    inline void waitUntilProcessed( const int n ) const
    { _scheduler( n ); }

    inline void commandActive( const std::string & commandName, const bool active )
    { signalCommandActive( commandName, active ); }
    
    /**
     * @brief play track
     * @param filename track filename
     */
    inline void playTrack( const boost::filesystem::path & filename )
    { signalPlayTrack( filename ); }

    /**
     * @brief played track (status)
     * @param filename track filename
     */
    inline void played( const boost::filesystem::path & filename )
    { signalPlayedTrack( filename ); }

    /**
     * @brief playing item at a given index (status change)
     * @param ev playing event
     */
    inline void playingItemIndex( const boost::filesystem::path & filename, const int playlistIndex )
    { signalPlayingItemIndex( filename, playlistIndex ); }

    /**
     * @brief play item at a given index (action)
     * @param ev playing event
     */
    inline void playItemAtIndex( const int playlistIndex )
    { signalPlayItemAtIndex( playlistIndex ); }
    

    /**
     * @brief append playlist tracks
     * @param filename playlist filename (.m3u)
     */
    inline void appendPlaylistTracks( const boost::filesystem::path & filename )
    { signalAppendPlaylistTracks( filename ); }

    inline void stopped()
    { signalStopTrack(); }

    inline void addedTrack( const boost::filesystem::path & filename )
    { signalAddedTrack( filename ); }

    inline void addTrack( const boost::filesystem::path & filename )
    { signalAddTrack( filename ); }

    inline void previousTrack()
    { signalPreviousTrack(); }

    inline void restartTrack()
    { signalRestartTrack(); }

    inline void nextTrack()
    { signalNextTrack(); }

    inline void clearPlaylist()
    { signalClearPlaylist(); }

    inline void modelClearedPlaylist()
    { signalModelClearedPlaylist(); }

    inline void startPlaylist()
    { signalStartPlaylist(); }

    inline void failed( const std::string & msg )
    { signalFailed( msg ); }

    inline void openedPlaylist( const std::vector<m3uParser::PlaylistItem> & playlistItems )
    { signalOpenedPlaylist( playlistItems ); }

    inline void setTrackPosition( const std::size_t positionInPercent )
    { signalSetTrackPosition( positionInPercent ); }

    inline void trackPositionChanged( const std::size_t positionInMS, const std::size_t trackLength )
    { signalTrackPositionChanged( positionInMS, trackLength ); }

    inline void trackLengthChanged( const std::size_t lengthInMS )
    { signalTrackLengthChanged( lengthInMS ); }

    boost::optional<boost::filesystem::path> askForFile( const std::string & question, const EFileDialogMode & mode )
    {
        auto sigAnswer = signalAskForFile( question, mode );
        if ( sigAnswer != boost::none )
        {
            return *sigAnswer;
        }
        else
        {
            return boost::none;
        }
    }

    /**
     * @brief send event
     */
    void processEvent( IEvent & event );
    
    /**
     * @brief process play, stop, next, previous commands
     * @param commandName command name
     */
    void processCommand( const std::string & commandName );

    /**
     * @brief send 'play item at given index' event
     * @param index playlist index
     */
    inline void processPlayItemAtIndex( const int index )
    {
        using EventT = EvPlayItemAtIndex;
        EventT *event = new EventT( index );
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    /**
     * @brief send 'playing item at given index (status)' event
     * @param filename track filename
     * @param index playlist index
     */
    inline void processPlayingItemIndex( const boost::filesystem::path & filename, const int index )
    {
        using EventT = EvPlayingItemIndex;
        EvPlayingItemIndex *event = new EventT( filename, index );
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    inline void processPlay( const boost::optional<boost::filesystem::path> & filename )
    {
        using EventT = EvPlay;
        EventT *event = new EventT( filename );
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    inline void processAppendPlaylistTrack( const boost::filesystem::path & filename )
    {
        using EventT = EvAppendPlaylistTrack;
        EventT *event = new EventT( filename );
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    inline void processPlayed( const boost::filesystem::path & filename )
    {
        using EventT = EvPlayed;
        EventT *event = new EventT( filename );
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    inline void processStop()
    {
        using EventT = EvStop;
        EventT *event = new EventT();
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    inline void processRestart()
    {
        using EventT = EvRestartTrack;
        EventT *event = new EventT();
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    inline void processPrevious()
    {
        using EventT = EvPreviousTrack;
        EventT *event = new EventT();
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    inline void processNext()
    {
        using EventT = EvNextTrack;
        EventT *event = new EventT();
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    inline void processClearPlaylist()
    {
        using EventT = EvClearPlaylist;
        EventT *event = new EvClearPlaylist();
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    inline void processModelClearedPlaylist()
    {
        using EventT = EvModelClearedPlaylist;
        EventT *event = new EventT();
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    inline void processAddTrack( const boost::filesystem::path& filename )
    {
        using EventT = EvAddTrack;
        EventT *event = new EventT( filename );
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    inline void processAddedTrack( const boost::filesystem::path& filename )
    {
        using EventT = EvAddedTrack;
        EventT *event = new EventT( filename );
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    inline void processStartPlaylist()
    {
        using EventT = EvStartPlaylist;
        EventT *event = new EventT();
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    inline void processEndOfTrack()
    {
        using EventT = EvEndOfTrack;
        EventT *event = new EventT();
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    inline void processOpenedPlaylist( const std::vector<m3uParser::PlaylistItem> & playlistItems )
    {
        using EventT = EvOpenedPlaylist;
        EventT *event = new EventT( playlistItems );
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    inline void processCommandActive( const std::string & commandName, const bool active )
    {
        using EventT = EvCommandActive;
        EventT *event = new EventT( commandName, active );
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    inline void processSetTrackPosition( const int positionInPercent )
    {
        using EventT = EvSetTrackPosition;
        EventT *event = new EventT( positionInPercent );
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    inline void processTrackLengthChanged( const std::size_t lengthInMS )
    {
        using EventT = EvTrackLengthChanged;
        EventT *event = new EventT( lengthInMS );
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }


    inline void processTrackPositionChanged( const std::size_t positionInMS, const std::size_t lengthInMS )
    {
        using EventT = EvTrackPositionChanged;
        EventT *event = new EventT( positionInMS, lengthInMS );
        signalEvent( *event );
        _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EventT >( event ) );
    }

    inline void registerPluginPresenter( const std::string & pluginName, IPluginPresenter & pres )
    {
        _pluginPresenter.insert( std::make_pair( pluginName, &pres ) );
    }
    
    template<class P>
    P & presenterOfPlugin( const std::string & pluginName )
    {
        auto it = _pluginPresenter.find( pluginName );
        assert( it != _pluginPresenter.end() );
        return dynamic_cast<P&>( *it->second );
    }

private:
    sc::fifo_scheduler<>::processor_handle _playerProcessor;    ///< Event processor
    mutable sc::fifo_scheduler<> _scheduler;                    ///< Event asynchronous scheduler (used to queue events)
    details::SchedulerWorker _schedulerWorker;                  ///< Event scheduler thread

public:
    //- signals
    boost::signals2::signal<void( IEvent& )> signalEvent;
    boost::signals2::signal<sc::detail::reaction_result(const std::string&, Playing &)> askPlayingStateExternalTransition;   ///< Bind this to a transition function to extend the state machine states (context is Playing state)
    boost::signals2::signal<sc::detail::reaction_result(const std::string&, Stopped &)> askStoppedStateExternalTransition;   ///< Bind this to a transition function to extend the state machine states (context is Stopped state)
    boost::signals2::signal<void(const boost::filesystem::path&)> signalAppendPlaylistTracks;
    boost::signals2::signal<void(const boost::filesystem::path&)> signalPlayedTrack;
    boost::signals2::signal<void(const boost::filesystem::path&)> signalPlayTrack;
    boost::signals2::signal<void(const boost::filesystem::path&)> signalAddTrack;
    boost::signals2::signal<void(const boost::filesystem::path&)> signalAddedTrack;
    boost::signals2::signal<void()> signalStopTrack;
    boost::signals2::signal<void()> signalRestartTrack;
    boost::signals2::signal<void()> signalPreviousTrack;
    boost::signals2::signal<void()> signalNextTrack;
    boost::signals2::signal<void()> signalClearPlaylist;
    boost::signals2::signal<void()> signalModelClearedPlaylist;
    boost::signals2::signal<void()> signalStartPlaylist;
    boost::signals2::signal<void(const int)> signalPlayItemAtIndex;
    boost::signals2::signal<void(const std::size_t lengthInMS)> signalTrackLengthChanged;
    boost::signals2::signal<void(const std::size_t posInPercent)> signalSetTrackPosition;
    boost::signals2::signal<void(const std::size_t posInMS, const std::size_t trackLength)> signalTrackPositionChanged;
    boost::signals2::signal<void(const std::vector<m3uParser::PlaylistItem> &)> signalOpenedPlaylist;
    boost::signals2::signal<void(const boost::filesystem::path&, const int)> signalPlayingItemIndex;
    boost::signals2::signal<void(const std::string&)> signalFailed;
    boost::signals2::signal<boost::optional<boost::filesystem::path> (const std::string&, const EFileDialogMode)> signalAskForFile;
    boost::signals2::signal<void( const std::string & commandName, const bool active )> signalCommandActive; ///< Signals that a command has been activated or desactivated

private:
    std::map<std::string, IPluginPresenter*> _pluginPresenter;
};

}
}

#endif	/* MVPPLAYERPRESENTER_HPP */

