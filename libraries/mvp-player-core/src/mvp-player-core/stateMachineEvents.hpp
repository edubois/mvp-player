#ifndef _STATEMACHINEEVENTS_HPP_
#define	_STATEMACHINEEVENTS_HPP_

#include "m3uParser.hpp"
#include "IEvent.hpp"
#include "boost-filesystem-path-serialization.hpp"

#include <boost/statechart/event.hpp>
#include <boost/filesystem.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <vector>

namespace mvpplayer
{
namespace logic
{

namespace fs = boost::filesystem;
namespace sc = boost::statechart;

/**
 * @brief event stop
 */
struct EvStop : IEvent, sc::event< EvStop >
{
private:
    typedef EvStop This;
public:
    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }

    friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<IEvent>( *this );
    }

    /**
     * @brief process this event (needed to avoid dynamic_casts)
     * @param scheduler event scheduler
     * @param processor event processor
     */
    void processSelf( boost::statechart::fifo_scheduler<> & scheduler, boost::statechart::fifo_scheduler<>::processor_handle & processor )
    {
        scheduler.queue_event( processor, boost::intrusive_ptr< This >( this ) );
    }
};

/**
 * @brief event restart track
 */
struct EvRestartTrack : IEvent, sc::event< EvRestartTrack >
{
private:
    typedef EvRestartTrack This;
public:
    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }

    friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<IEvent>( *this );
    }

    /**
     * @brief process this event (needed to avoid dynamic_casts)
     * @param scheduler event scheduler
     * @param processor event processor
     */
    void processSelf( boost::statechart::fifo_scheduler<> & scheduler, boost::statechart::fifo_scheduler<>::processor_handle & processor )
    {
        scheduler.queue_event( processor, boost::intrusive_ptr< This >( this ) );
    }
};

/**
 * @brief event previous track
 */
struct EvPreviousTrack : IEvent, sc::event< EvPreviousTrack >
{
private:
    typedef EvPreviousTrack This;
public:
    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }

    friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<IEvent>( *this );
    }

    /**
     * @brief process this event (needed to avoid dynamic_casts)
     * @param scheduler event scheduler
     * @param processor event processor
     */
    void processSelf( boost::statechart::fifo_scheduler<> & scheduler, boost::statechart::fifo_scheduler<>::processor_handle & processor )
    {
        scheduler.queue_event( processor, boost::intrusive_ptr< This >( this ) );
    }
};

/**
 * @brief event next track
 */
struct EvNextTrack : IEvent, sc::event< EvNextTrack >
{
private:
    typedef EvNextTrack This;
public:
    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }

    friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<IEvent>( *this );
    }

    /**
     * @brief process this event (needed to avoid dynamic_casts)
     * @param scheduler event scheduler
     * @param processor event processor
     */
    void processSelf( boost::statechart::fifo_scheduler<> & scheduler, boost::statechart::fifo_scheduler<>::processor_handle & processor )
    {
        scheduler.queue_event( processor, boost::intrusive_ptr< This >( this ) );
    }
};

/**
 * @brief event clear playlist
 */
struct EvClearPlaylist : IEvent, sc::event< EvClearPlaylist >
{
private:
    typedef EvClearPlaylist This;
public:
    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }

    friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<IEvent>( *this );
    }

    /**
     * @brief process this event (needed to avoid dynamic_casts)
     * @param scheduler event scheduler
     * @param processor event processor
     */
    void processSelf( boost::statechart::fifo_scheduler<> & scheduler, boost::statechart::fifo_scheduler<>::processor_handle & processor )
    {
        scheduler.queue_event( processor, boost::intrusive_ptr< This >( this ) );
    }
};

/**
 * @brief event model cleared playlist
 */
struct EvModelClearedPlaylist : IEvent, sc::event< EvModelClearedPlaylist >
{
private:
    typedef EvModelClearedPlaylist This;
public:
    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }

    friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<IEvent>( *this );
    }

    /**
     * @brief process this event (needed to avoid dynamic_casts)
     * @param scheduler event scheduler
     * @param processor event processor
     */
    void processSelf( boost::statechart::fifo_scheduler<> & scheduler, boost::statechart::fifo_scheduler<>::processor_handle & processor )
    {
        scheduler.queue_event( processor, boost::intrusive_ptr< This >( this ) );
    }
};

/**
 * @brief event start playlist
 */
struct EvStartPlaylist : IEvent, sc::event< EvStartPlaylist >
{
private:
    typedef EvStartPlaylist This;
public:
    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }

    friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<IEvent>( *this );
    }

    /**
     * @brief process this event (needed to avoid dynamic_casts)
     * @param scheduler event scheduler
     * @param processor event processor
     */
    void processSelf( boost::statechart::fifo_scheduler<> & scheduler, boost::statechart::fifo_scheduler<>::processor_handle & processor )
    {
        scheduler.queue_event( processor, boost::intrusive_ptr< This >( this ) );
    }
};

/**
 * @brief event end of track
 */
struct EvEndOfTrack : IEvent, sc::event< EvEndOfTrack >
{
private:
    typedef EvEndOfTrack This;
public:
    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }

    friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<IEvent>( *this );
    }

    /**
     * @brief process this event (needed to avoid dynamic_casts)
     * @param scheduler event scheduler
     * @param processor event processor
     */
    void processSelf( boost::statechart::fifo_scheduler<> & scheduler, boost::statechart::fifo_scheduler<>::processor_handle & processor )
    {
        scheduler.queue_event( processor, boost::intrusive_ptr< This >( this ) );
    }
};

/**
 * @brief event play
 */
struct EvPlay : IEvent, sc::event< EvPlay >
{
private:
    typedef EvPlay This;
public:
    EvPlay()
    {
    }

    EvPlay( const boost::filesystem::path & filename )
    : _filename( filename )
    {
    }

    inline const boost::filesystem::path & filename() const
    { return _filename; }

    friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<IEvent>( *this );
        ar & _filename;
    }

    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }
    /**
     * @brief process this event (needed to avoid dynamic_casts)
     * @param scheduler event scheduler
     * @param processor event processor
     */
    void processSelf( boost::statechart::fifo_scheduler<> & scheduler, boost::statechart::fifo_scheduler<>::processor_handle & processor )
    {
        scheduler.queue_event( processor, boost::intrusive_ptr< This >( this ) );
    }
private:
    boost::filesystem::path _filename;      ///< Filename we want to play
};

/**
 * @brief event played track
 */
struct EvPlayed : IEvent, sc::event< EvPlayed >
{
private:
    typedef EvPlayed This;
public:
    EvPlayed()
    {}

    EvPlayed( const boost::filesystem::path & filename )
    : _filename( filename )
    {}

    inline const boost::filesystem::path & filename() const
    { return _filename; }

    friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<IEvent>( *this );
        ar & _filename;
    }

    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }
    /**
     * @brief process this event (needed to avoid dynamic_casts)
     * @param scheduler event scheduler
     * @param processor event processor
     */
    void processSelf( boost::statechart::fifo_scheduler<> & scheduler, boost::statechart::fifo_scheduler<>::processor_handle & processor )
    {
        scheduler.queue_event( processor, boost::intrusive_ptr< This >( this ) );
    }
private:
    boost::filesystem::path _filename;      ///< Filename we want to play
};

/**
 * @brief event add track
 */
struct EvAddTrack : IEvent, sc::event< EvAddTrack >
{
private:
    typedef EvAddTrack This;
public:
    EvAddTrack()
    {}

    EvAddTrack( const boost::filesystem::path & filename )
    : _filename( filename )
    {}

    inline const boost::filesystem::path & filename() const
    { return _filename; }

    friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<IEvent>( *this );
        ar & _filename;
    }

    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }
    /**
     * @brief process this event (needed to avoid dynamic_casts)
     * @param scheduler event scheduler
     * @param processor event processor
     */
    void processSelf( boost::statechart::fifo_scheduler<> & scheduler, boost::statechart::fifo_scheduler<>::processor_handle & processor )
    {
        scheduler.queue_event( processor, boost::intrusive_ptr< This >( this ) );
    }
private:
    boost::filesystem::path _filename;      ///< Filename we want to play
};

/**
 * @brief event track added
 */
struct EvAddedTrack : IEvent, sc::event< EvAddedTrack >
{
private:
    typedef EvAddedTrack This;
public:
    EvAddedTrack()
    {}

    EvAddedTrack( const boost::filesystem::path & filename )
    : _filename( filename )
    {}

    inline const boost::filesystem::path & filename() const
    { return _filename; }

    friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<IEvent>( *this );
        ar & _filename;
    }

    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }
    /**
     * @brief process this event (needed to avoid dynamic_casts)
     * @param scheduler event scheduler
     * @param processor event processor
     */
    void processSelf( boost::statechart::fifo_scheduler<> & scheduler, boost::statechart::fifo_scheduler<>::processor_handle & processor )
    {
        scheduler.queue_event( processor, boost::intrusive_ptr< This >( this ) );
    }
private:
    boost::filesystem::path _filename;      ///< Filename we want to play
};

/**
 * @brief event opened playlist
 */
struct EvOpenedPlaylist : IEvent, sc::event< EvOpenedPlaylist >
{
private:
    typedef EvOpenedPlaylist This;
public:
    EvOpenedPlaylist()
    {}

    EvOpenedPlaylist( const std::vector<m3uParser::PlaylistItem>& playlistItems )
    : _playlistItems( playlistItems )
    {}

    inline const std::vector<m3uParser::PlaylistItem>& playlistItems() const
    { return _playlistItems; }

    friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<IEvent>( *this );
        ar & _playlistItems;
    }

    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }
    /**
     * @brief process this event (needed to avoid dynamic_casts)
     * @param scheduler event scheduler
     * @param processor event processor
     */
    void processSelf( boost::statechart::fifo_scheduler<> & scheduler, boost::statechart::fifo_scheduler<>::processor_handle & processor )
    {
        scheduler.queue_event( processor, boost::intrusive_ptr< This >( this ) );
    }
private:
    std::vector<m3uParser::PlaylistItem> _playlistItems; ///< Playlist items
};

/**
 * @brief event triggered when playing an item of the playlist
 */
struct EvPlayingItemIndex : IEvent, sc::event< EvPlayingItemIndex >
{
private:
    typedef EvPlayingItemIndex This;
public:
    EvPlayingItemIndex()
    : _playlistIndex( -1 )
    {}

    EvPlayingItemIndex( const boost::filesystem::path & filename, const int playlistIndex )
    : _filename( filename )
    , _playlistIndex( playlistIndex )
    {}

    inline const boost::filesystem::path & filename() const
    { return _filename; }

    inline const int playlistIndex() const
    { return _playlistIndex; }

    friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<IEvent>( *this );
        ar & _filename;
        ar & _playlistIndex;
    }

    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }
    /**
     * @brief process this event (needed to avoid dynamic_casts)
     * @param scheduler event scheduler
     * @param processor event processor
     */
    void processSelf( boost::statechart::fifo_scheduler<> & scheduler, boost::statechart::fifo_scheduler<>::processor_handle & processor )
    {
        scheduler.queue_event( processor, boost::intrusive_ptr< This >( this ) );
    }
private:
    boost::filesystem::path _filename;      ///< Filename we want to play
    int _playlistIndex;                     ///< Playlist index
};


/**
 * @brief event triggered when playing an item of the playlist
 */
struct EvPlayItemAtIndex : IEvent, sc::event< EvPlayItemAtIndex >
{
private:
    typedef EvPlayItemAtIndex This;
public:
    EvPlayItemAtIndex()
    : _playlistIndex( -1 )
    {}

    EvPlayItemAtIndex( const int index )
    : _playlistIndex( index )
    {}

    inline const int playlistIndex() const
    { return _playlistIndex; }

    friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<IEvent>( *this );
        ar & _playlistIndex;
    }

    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }
    /**
     * @brief process this event (needed to avoid dynamic_casts)
     * @param scheduler event scheduler
     * @param processor event processor
     */
    void processSelf( boost::statechart::fifo_scheduler<> & scheduler, boost::statechart::fifo_scheduler<>::processor_handle & processor )
    {
        scheduler.queue_event( processor, boost::intrusive_ptr< This >( this ) );
    }
private:
    int _playlistIndex;                     ///< Playlist index
};

/**
 * @brief event reset
 */
struct EvReset : IEvent, sc::event< EvReset >
{
private:
    typedef EvReset This;
public:
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<IEvent>( *this );
    }

    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }
    friend class boost::serialization::access;
    /**
     * @brief process this event (needed to avoid dynamic_casts)
     * @param scheduler event scheduler
     * @param processor event processor
     */
    void processSelf( boost::statechart::fifo_scheduler<> & scheduler, boost::statechart::fifo_scheduler<>::processor_handle & processor )
    {
        scheduler.queue_event( processor, boost::intrusive_ptr< This >( this ) );
    }
};

template<class Archive>
void registerClassInArchive( Archive & ar )
{
    ar.template register_type< EvStop >();
    ar.template register_type< EvRestartTrack >();
    ar.template register_type< EvPreviousTrack >();
    ar.template register_type< EvNextTrack >();
    ar.template register_type< EvClearPlaylist >();
    ar.template register_type< EvModelClearedPlaylist >();
    ar.template register_type< EvStartPlaylist >();
    ar.template register_type< EvEndOfTrack >();
    ar.template register_type< EvPlay >();
    ar.template register_type< EvPlayed >();
    ar.template register_type< EvAddTrack >();
    ar.template register_type< EvAddedTrack >();
    ar.template register_type< EvOpenedPlaylist >();
    ar.template register_type< EvPlayingItemIndex >();
    ar.template register_type< EvPlayItemAtIndex >();
    ar.template register_type< EvReset >();
}

}
}

BOOST_CLASS_EXPORT_KEY( mvpplayer::logic::EvStop );
BOOST_CLASS_EXPORT_KEY( mvpplayer::logic::EvRestartTrack );
BOOST_CLASS_EXPORT_KEY( mvpplayer::logic::EvPreviousTrack );
BOOST_CLASS_EXPORT_KEY( mvpplayer::logic::EvNextTrack );
BOOST_CLASS_EXPORT_KEY( mvpplayer::logic::EvClearPlaylist );
BOOST_CLASS_EXPORT_KEY( mvpplayer::logic::EvModelClearedPlaylist );
BOOST_CLASS_EXPORT_KEY( mvpplayer::logic::EvStartPlaylist );
BOOST_CLASS_EXPORT_KEY( mvpplayer::logic::EvEndOfTrack );
BOOST_CLASS_EXPORT_KEY( mvpplayer::logic::EvPlay );
BOOST_CLASS_EXPORT_KEY( mvpplayer::logic::EvPlayed );
BOOST_CLASS_EXPORT_KEY( mvpplayer::logic::EvAddTrack );
BOOST_CLASS_EXPORT_KEY( mvpplayer::logic::EvAddedTrack );
BOOST_CLASS_EXPORT_KEY( mvpplayer::logic::EvOpenedPlaylist );
BOOST_CLASS_EXPORT_KEY( mvpplayer::logic::EvPlayingItemIndex );
BOOST_CLASS_EXPORT_KEY( mvpplayer::logic::EvPlayItemAtIndex );
BOOST_CLASS_EXPORT_KEY( mvpplayer::logic::EvReset );

#endif
