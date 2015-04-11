#ifndef _MVPPLAYERPRESENTER_HPP_
#define	_MVPPLAYERPRESENTER_HPP_

#include "stateMachineEvents.hpp"

#include <boost/statechart/fifo_scheduler.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/signals2.hpp>
#include <boost/thread.hpp>

namespace mvpplayer
{
namespace logic
{
namespace sc = boost::statechart;

namespace details
{

class SchedulerWorker
{
public:
    SchedulerWorker( sc::fifo_scheduler<> & scheduler )
    : _scheduler( scheduler )
    , _stop( true )
    {
    }

    inline void start()
    {
        _stop = false;
        _thread.reset( new boost::thread( boost::bind( &SchedulerWorker::work, this ) ) );
    }
    
    inline void join()
    {
        _stop = true;
        _mutex.unlock();
        _thread->join();
    }

    inline boost::mutex & mutex() const
    { return _mutex; }

private:    
    void work()
    {
        while( !_stop )
        {
            _scheduler( 1 );
            // Needed to handle pause in event processing
            try { boost::mutex::scoped_lock lock( _mutex ); } catch( boost::lock_error& ) {}
        }
    }

private:
    sc::fifo_scheduler<> & _scheduler;
    bool _stop;
    std::unique_ptr<boost::thread> _thread;
    mutable boost::mutex _mutex;
};

}

/**
 * @brief the presenter is the glue between the model and the view,
 *        it also contains the player's state machine
 */
class MVPPlayerPresenter
{
public:
    MVPPlayerPresenter()
    : _scheduler( true )
    , _schedulerWorker( _scheduler )
    {}

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

    boost::optional<boost::filesystem::path> askForFile( const std::string & question )
    { return signalAskForFile( question ); }

    /**
     * @brief pause the processor, call the lambda function, restart the processor
     * @return true if error, false otherwise
     */
    bool processSequencial( const std::function<void()> lambda );

    /**
     * @brief send event
     */
    void processEvent( IEvent & event );

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
    
    mutable sc::fifo_scheduler<> _scheduler;                    ///< Event asynchronous scheduler (used to queue events)
    sc::fifo_scheduler<>::processor_handle _playerProcessor;    ///< Event processor
    details::SchedulerWorker _schedulerWorker;                  ///< Event scheduler thread

    //- signals
    boost::signals2::signal<void( IEvent& )> signalEvent;
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
    boost::signals2::signal<void(const std::vector<m3uParser::PlaylistItem> &)> signalOpenedPlaylist;
    boost::signals2::signal<void(const boost::filesystem::path&, const int)> signalPlayingItemIndex;
    boost::signals2::signal<void(const std::string&)> signalFailed;
    boost::signals2::signal<boost::filesystem::path(const std::string&)> signalAskForFile;
};

}
}

#endif	/* MVPPLAYERPRESENTER_HPP */

