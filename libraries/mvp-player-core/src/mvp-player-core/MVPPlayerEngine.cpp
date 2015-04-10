#include "MVPPlayerEngine.hpp"

#include <iterator>

#include <boost/algorithm/string/predicate.hpp>

namespace mvpplayer
{

MVPPlayerEngine::MVPPlayerEngine( ISoundPlayer *soundPlayer, ISoundRecorder *soundRecorder )
: _soundPlayer( soundPlayer )
, _soundRecorder( soundRecorder )
{
    // Subscribe to sound player's end of track notifications
    _soundPlayer->signalEndOfTrack.connect( boost::bind( &MVPPlayerEngine::notifyEndOfTrack, this ) );
    _currentPosition = _playlist.begin();
}

MVPPlayerEngine::~MVPPlayerEngine()
{
}

bool MVPPlayerEngine::playFile( const boost::filesystem::path & filename )
{
    stop();
    if ( boost::iends_with( filename.string(), ".m3u" ) )
    {
        openPlaylist( filename );
        playList();
        return false;
    }
    else
    {
        bool ret = true;
        {
            boost::mutex::scoped_lock lock( _mutex );
            _currentPlayedTrack = filename;
            _soundPlayer->load( filename.string() );
            ret = _soundPlayer->play();
        }
        signalPlayedTrack( filename );
        return ret;
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
            _playlist.push_back( playlistItem.filename );
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


bool MVPPlayerEngine::restart()
{
    return _soundPlayer->restart();
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
    _soundPlayer->stop();
}

bool MVPPlayerEngine::playCurrent()
{
    if ( _currentPosition != _playlist.end() )
    {
        boost::filesystem::path playedTrack;
        int trackIndex = -1;
        {
            boost::mutex::scoped_lock lock( _mutex );
            playedTrack = ( _currentPlayedTrack = *_currentPosition );
            trackIndex = std::distance( _playlist.cbegin(), _currentPosition );
            _soundPlayer->load( _currentPlayedTrack.string() );
            _soundPlayer->play();
        }
        signalPlayedTrack( playedTrack );
        signalPlayingItemIndex( playedTrack, trackIndex );
        return false;
    }
    return true;
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
