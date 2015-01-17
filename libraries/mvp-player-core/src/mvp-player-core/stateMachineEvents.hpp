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
    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }
};

/**
 * @brief event restart track
 */
struct EvRestartTrack : IEvent, sc::event< EvRestartTrack >
{
    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }
};

/**
 * @brief event previous track
 */
struct EvPreviousTrack : IEvent, sc::event< EvPreviousTrack >
{
    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }
};

/**
 * @brief event next track
 */
struct EvNextTrack : IEvent, sc::event< EvNextTrack >
{
    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }
};

/**
 * @brief event clear playlist
 */
struct EvClearPlaylist : IEvent, sc::event< EvClearPlaylist >
{
    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }
};

/**
 * @brief event model cleared playlist
 */
struct EvModelClearedPlaylist : IEvent, sc::event< EvModelClearedPlaylist >
{
    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }
};

/**
 * @brief event start playlist
 */
struct EvStartPlaylist : IEvent, sc::event< EvStartPlaylist >
{
    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }
};

/**
 * @brief event end of track
 */
struct EvEndOfTrack : IEvent, sc::event< EvEndOfTrack >
{
    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }
};

/**
 * @brief event play
 */
struct EvPlay : IEvent, sc::event< EvPlay >
{
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
private:
    boost::filesystem::path _filename;      ///< Filename we want to play
};

/**
 * @brief event played track
 */
struct EvPlayed : IEvent, sc::event< EvPlayed >
{
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
private:
    boost::filesystem::path _filename;      ///< Filename we want to play
};

/**
 * @brief event add track
 */
struct EvAddTrack : IEvent, sc::event< EvAddTrack >
{
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
private:
    boost::filesystem::path _filename;      ///< Filename we want to play
};

/**
 * @brief event track added
 */
struct EvAddedTrack : IEvent, sc::event< EvAddedTrack >
{
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
private:
    boost::filesystem::path _filename;      ///< Filename we want to play
};

/**
 * @brief event opened playlist
 */
struct EvOpenedPlaylist : IEvent, sc::event< EvOpenedPlaylist >
{
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
private:
    std::vector<m3uParser::PlaylistItem> _playlistItems; ///< Playlist items
};

/**
 * @brief event triggered when playing an item of the playlist
 */
struct EvPlayingItemIndex : IEvent, sc::event< EvPlayingItemIndex >
{
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
private:
    boost::filesystem::path _filename;      ///< Filename we want to play
    int _playlistIndex;                     ///< Playlist index
};


/**
 * @brief event triggered when playing an item of the playlist
 */
struct EvPlayItemAtIndex : IEvent, sc::event< EvPlayItemAtIndex >
{
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
private:
    int _playlistIndex;                     ///< Playlist index
};

/**
 * @brief event reset
 */
struct EvReset : IEvent, sc::event< EvReset >
{
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<IEvent>( *this );
    }

    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }
    friend class boost::serialization::access;
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
