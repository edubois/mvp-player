#ifndef _IMVPPLAYERDIALOG_HPP
#define	_IMVPPLAYERDIALOG_HPP

#include "PlayerButtonsBar.hpp"

#include <mvp-player-core/m3uParser.hpp>

#include <boost/signals2.hpp>
#include <boost/filesystem/path.hpp>
#include <string>

namespace mvpplayer
{
namespace gui
{

/**
 * @brief mvp-player dialog
 */
class IMVPPlayerDialog
{
public:
    IMVPPlayerDialog()
    { readDefaultButtonDescription(); }

    virtual ~IMVPPlayerDialog() = 0;

    void readDefaultButtonDescription( const boost::filesystem::path & buttonsDir = "./ui/buttons/" );

    virtual void setCurrentTrack( const boost::filesystem::path & filename ) = 0;

    virtual void setPlaylistItemIndex( const int row ) = 0;

    virtual void setIconStop() = 0;

    virtual void setIconPlay() = 0;

    virtual void openedPlaylist( const std::vector<m3uParser::PlaylistItem> & playlistItems ) = 0;

    virtual void clearPlaylist() = 0;

    virtual void addTrack( const boost::filesystem::path & filename ) = 0;

public:
    boost::signals2::signal<void( const std::function<void()> )> signalSequencial; ///< Signals that we want a sequencial run of the given lambda function
    boost::signals2::signal<void( const std::string & buttonName )> signalViewHitButton; ///< Signals that user hit a button
    boost::signals2::signal<void( const int )> signalViewHitPlaylistItem; ///< Signals that user hit play on a playlist item
    boost::signals2::signal<void()> signalViewClearPlaylist;  ///< Signal clear playlist
    boost::signals2::signal<void()> signalViewStartPlaylist;  ///< Signal start playlist
    boost::signals2::signal<void( const std::string& )> signalViewAddTrack; ///< Signals that user wants to add a track

protected:
    PlayerButtonsBar _buttonsBar;   ///< The player buttons
};

}
}

#endif
