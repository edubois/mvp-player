#include "MVPPlayerEngine.hpp"

#include <iterator>

#include <boost/algorithm/string/predicate.hpp>

namespace mvpplayer
{

MVPPlayerEngine::MVPPlayerEngine( IFilePlayer *filePlayer )
: _filePlayer( filePlayer )
{
    // Subscribe to sound player's end of track notifications
    _filePlayer->signalEndOfTrack.connect( boost::bind( &MVPPlayerEngine::notifyEndOfTrack, this ) );
    _filePlayer->signalTrackLength.connect( boost::bind( &MVPPlayerEngine::notifyTrackLength, this, _1 ) );
    _filePlayer->signalPositionChanged.connect( [this]( const std::size_t p, const std::size_t l ){ signalPositionChanged( p, l ); } );
    _currentPosition = _playlist.begin();
}

MVPPlayerEngine::~MVPPlayerEngine()
{
    try
    {
        stop();
        _filePlayer->terminate();
    }
    catch( ... )
    {}
}

bool MVPPlayerEngine::playFile( const boost::filesystem::path & filename )
{
    stop();
    if ( boost::iends_with( filename.string(), ".m3u" ) )
    {
        openPlaylist( filename );
        playList();
        return true;
    }
    else
    {
        bool ret = false;
        {
            boost::mutex::scoped_lock lock( _mutex );
            _currentPlayedTrack = filename;
            _filePlayer->load( filename );
            ret = _filePlayer->play();
        }
        signalPlayedTrack( filename );
        return ret;
    }
}

void MVPPlayerEngine::addTrackItems( const std::vector<boost::filesystem::path> & filename )
{
    for( const boost::filesystem::path & p: filename )
    {
        if ( boost::iequals( p.extension().string(), ".m3u" ) )
        {
            openPlaylist( p );
        }
        else
        {
            boost::mutex::scoped_lock lock( _mutex );
            _playlist.push_back( p );
            signalTrackAddedToPlaylist( p.filename() );
        }
    }
}

void MVPPlayerEngine::openPlaylist( const boost::filesystem::path & playlistFilename )
{
    // Parse the playlist
    std::vector<m3uParser::PlaylistItem> playlistItems = m3uParser::parse( playlistFilename );
    if ( !playlistItems.size() )
    { return; }

    {
        boost::mutex::scoped_lock lock( _mutex );
        _playlist.clear();
        for( const m3uParser::PlaylistItem playlistItem : playlistItems )
        {
            boost::filesystem::path pathToAdd = playlistItem.filename;
            if ( !boost::filesystem::exists( pathToAdd ) )
            {
                // try absolute path
                if ( boost::filesystem::exists( playlistFilename.parent_path() / pathToAdd ) )
                {
                    pathToAdd = playlistFilename.parent_path() / pathToAdd;
                }
            }
            _playlist.push_back( pathToAdd );
        }
        _currentPosition = _playlist.begin();
    }

    // Signalize that we opened the playlist
    signalOpenedPlaylist( playlistItems );
}

void MVPPlayerEngine::playList()
{
    stop();
    {
        boost::mutex::scoped_lock lock( _mutex );
        _currentPosition = _playlist.begin();
    }
    playCurrent();
}

/**
 * @brief Plays a playlist item
 * @param index playlist index
 */
void MVPPlayerEngine::playPlaylistItem( const int index )
{
    stop();
    {
        boost::mutex::scoped_lock lock( _mutex );
        _currentPosition = _playlist.begin();
        std::advance( _currentPosition, index );
    }
    playCurrent();
}

/**
 * @brief set current track position
 * @param positionInPercent position in percent (0-100)
 * @param seekType seek position in percent or milliseconds
 */
void MVPPlayerEngine::setTrackPosition( const double position, const ESeekPosition seekType )
{
    _filePlayer->setPosition( position, seekType );
}

bool MVPPlayerEngine::restart()
{
    return _filePlayer->restart();
}

void MVPPlayerEngine::playPrevious()
{
    boost::mutex::scoped_lock lock( _mutex );
    if ( --_currentPosition != _playlist.end() )
    {
        lock.unlock();
        stop();
        playCurrent();
    }
    else
    {
        _currentPosition = _playlist.begin();
    }
}

void MVPPlayerEngine::playNext()
{
    boost::mutex::scoped_lock lock( _mutex );
    if ( ++_currentPosition != _playlist.end() )
    {
        lock.unlock();
        stop();
        playCurrent();
    }
}

void MVPPlayerEngine::stop()
{
    boost::mutex::scoped_lock lock( _mutex );
    _currentPlayedTrack = boost::filesystem::path();
    // Stop all
    _filePlayer->stop();
}

bool MVPPlayerEngine::playCurrent()
{
    if ( _currentPosition != _playlist.end() )
    {
        boost::filesystem::path playedTrack;
        int trackIndex = -1;
        {
            boost::mutex::scoped_lock lock( _mutex );
            playedTrack = *_currentPosition;
        }
        if ( playFile( playedTrack ) )
        {
            trackIndex = std::distance( _playlist.cbegin(), _currentPosition );
            signalPlayingItemIndex( playedTrack, trackIndex );
        }
        return true;
    }
    return false;
}

/**
 * @brief clear the playlist
 */
void MVPPlayerEngine::clearPlaylist()
{
    stop();

    boost::mutex::scoped_lock lock( _mutex );
    if ( _playlist.size() )
    {
        _playlist.clear();
        _currentPosition = _playlist.begin();
        lock.unlock();
        signalClearedPlaylist();
    }
}


}
