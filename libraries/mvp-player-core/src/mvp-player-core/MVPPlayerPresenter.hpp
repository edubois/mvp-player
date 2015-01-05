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

/**
 * @brief the presenter is the glue between the model and the view,
 *        it also contains the player's state machine
 */
class MVPPlayerPresenter
{
public:
    MVPPlayerPresenter()
    : _scheduler( true )
    {}

    template<class M>
    void startStateMachine( const bool startScheduler = true )
    {
        // Create an event processor for the state machine M (template parameter)
        _playerProcessor = _scheduler.create_processor< M >( boost::ref( *this ) );
        _scheduler.initiate_processor( _playerProcessor );
        // Start thread
        _schedulerThread.reset( new boost::thread( boost::bind( &sc::fifo_scheduler<>::operator(), &_scheduler, 0 ) ) );
    }

    inline void waitUntilProcessed( const int n ) const
    { _scheduler( n ); }

    /**
     * @brief playing item at a given index (status change)
     * @param ev playing event
     */
    inline void playingItemIndex( const boost::filesystem::path & filename, const int playlistIndex )
    {
        signalPlayedTrack( filename );
        signalPlayingItemIndex( filename, playlistIndex );
    }

    /**
     * @brief played track (status)
     * @param filename track filename
     */
    inline void played( const boost::filesystem::path & filename )
    { signalPlayedTrack( filename ); }

    /**
     * @brief play item at a given index (action)
     * @param ev playing event
     */
    inline void playItemAtIndex( const int playlistIndex )
    { signalPlayItemAtIndex( playlistIndex ); }
    
    inline void stopped()
    { signalStopTrack(); }

    inline void previousTrack()
    { signalPreviousTrack(); }

    inline void restartTrack()
    { signalRestartTrack(); }

    inline void nextTrack()
    { signalNextTrack(); }

    inline void clearPlaylist()
    { signalClearPlaylist(); }

    inline void startPlaylist()
    { signalStartPlaylist(); }

    inline void failed( const std::string & msg )
    { signalFailed( msg ); }

    inline void openedPlaylist( const std::vector<m3uParser::PlaylistItem> & playlistItems )
    { signalOpenedPlaylist( playlistItems ); }

    boost::optional<boost::filesystem::path> askForFile( const std::string & question )
    { return signalAskForFile( question ); }

    /**
     * @brief send 'play item at given index' event
     * @param index playlist index
     */
    inline void processPlayItemAtIndex( const int index )
    { _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EvPlayItemAtIndex >( new EvPlayItemAtIndex( index ) ) ); }

    /**
     * @brief send 'playing item at given index (status)' event
     * @param filename track filename
     * @param index playlist index
     */
    inline void processPlayingItemIndex( const boost::filesystem::path & filename, const int index )
    { _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EvPlayingItemIndex >( new EvPlayingItemIndex( filename, index ) ) ); }

    inline void processPlay( const boost::filesystem::path & filename )
    { _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EvPlay >( new EvPlay( filename ) ) ); }

    inline void processStop()
    { _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EvStop >( new EvStop() ) ); }

    inline void processRestart()
    { _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EvRestartTrack >( new EvRestartTrack() ) ); }

    inline void processPrevious()
    { _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EvPreviousTrack >( new EvPreviousTrack() ) ); }

    inline void processNext()
    { _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EvNextTrack >( new EvNextTrack() ) ); }

    inline void processClearPlaylist()
    { _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EvClearPlaylist >( new EvClearPlaylist() ) ); }

    inline void processStartPlaylist()
    { _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EvStartPlaylist >( new EvStartPlaylist() ) ); }

    inline void processEndOfTrack()
    { _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EvEndOfTrack >( new EvEndOfTrack() ) ); }

    inline void processOpenedPlaylist( const std::vector<m3uParser::PlaylistItem> & playlistItems )
    { _scheduler.queue_event( _playerProcessor, boost::intrusive_ptr< EvOpenedPlaylist >( new EvOpenedPlaylist( playlistItems ) ) ); }
    
    mutable sc::fifo_scheduler<> _scheduler;                    ///< Event asynchronous scheduler (used to queue events)
    sc::fifo_scheduler<>::processor_handle _playerProcessor;    ///< Event processor
    std::unique_ptr<boost::thread> _schedulerThread;            ///< Event scheduler thread

    boost::signals2::signal<void(const boost::filesystem::path&)> signalPlayedTrack;
    boost::signals2::signal<void()> signalStopTrack;
    boost::signals2::signal<void()> signalRestartTrack;
    boost::signals2::signal<void()> signalPreviousTrack;
    boost::signals2::signal<void()> signalNextTrack;
    boost::signals2::signal<void()> signalClearPlaylist;
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

