#ifndef _IMVPPLAYERDIALOG_HPP
#define	_IMVPPLAYERDIALOG_HPP

#include <mvp-player-core/m3uParser.hpp>

#include <boost/signals2.hpp>
#include <boost/filesystem/path.hpp>
#include <string>

namespace mvpplayer
{
namespace gui
{

static const std::string kStopCaption( "[*]" );
static const std::string kPlayCaption( "|>" );

/**
 * @brief mvp-player dialog
 */
class IMVPPlayerDialog
{
public:
    IMVPPlayerDialog() {}
    virtual ~IMVPPlayerDialog() = 0;

    virtual void setCurrentTrack( const boost::filesystem::path & filename ) = 0;

    virtual void setPlaylistItemIndex( const int row ) = 0;

    virtual void setIconStop() = 0;

    virtual void setIconPlay() = 0;

    virtual void openedPlaylist( const std::vector<m3uParser::PlaylistItem> & playlistItems ) = 0;

    virtual void clearPlaylist() = 0;

    virtual void addTrack( const boost::filesystem::path & filename ) = 0;

public:
    boost::signals2::signal<void( const std::function<void()> )> signalSequencial; ///< Signals that we want a sequencial run of the given lambda function
    boost::signals2::signal<void( const std::string& )> signalViewHitPlay; ///< Signals that user hit play button
    boost::signals2::signal<void( const int )> signalViewHitPlaylistItem; ///< Signals that user hit play on a playlist item
    boost::signals2::signal<void()> signalViewHitStop; ///< Signals that user hit stop button
    boost::signals2::signal<void()> signalViewHitPrevious;  ///< Signal hit previous track
    boost::signals2::signal<void()> signalViewHitNext;  ///< Signal hit next track
    boost::signals2::signal<void()> signalViewClearPlaylist;  ///< Signal clear playlist
    boost::signals2::signal<void()> signalViewStartPlaylist;  ///< Signal start playlist
    boost::signals2::signal<void( const std::string& )> signalViewAddTrack; ///< Signals that user wants to add a track
};

}
}

#endif
