#ifndef _NCURSES_MVPPLAYERDIALOG_HPP_
#define	_NCURSES_MVPPLAYERDIALOG_HPP_

#include <mvp-player-gui/IMVPPlayerDialog.hpp>

#include <ncurses.h>
#include <cdk.h>

#include <boost/signals2.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/thread.hpp>
#include <string>

namespace mvpplayer
{
namespace gui
{
namespace ncurses
{

static const int kColorMessage = 1;

/**
 * @brief mvp-player ncurses dialog
 */
class MVPPlayerDialog : public IMVPPlayerDialog
{
public:
    MVPPlayerDialog( CDKSCREEN *cdkScreen, const int width, const int height, const int x, const int y );
    virtual ~MVPPlayerDialog();

    int exec();

    void setCurrentTrack( const boost::filesystem::path & filename ) override;

    void setPlaylistItemIndex( const int row ) override;

    void setIconStop() override;

    void setIconPlay() override;

    void openedPlaylist( const std::vector<m3uParser::PlaylistItem> & playlistItems ) override;

    void clearedPlaylist() override;

    void addTrack( const boost::filesystem::path & filename ) override;

    void setTrackLength( const std::size_t trackLengthInMS ) override;

    void setButtonChecked( const std::string & buttonName, const bool checked ) override;

    void setTrackPosition( const std::size_t positionInMS, const std::size_t trackLength ) override;

    void setVolume( const float volume ) override;
private:
    void initWin( const std::string & currentTrack, const bool playButton = true );
    void initPlaylist( const std::vector<std::string> & playlistItemsStr );

private:
    CDKSCREEN* _cdkScreen;
    CDKDIALOG* _childwin;
    CDKSCROLL* _playlist;
    bool _isPlaying;

    std::vector<std::string> _playlistItemsStr;     ///< Playlist items
    mutable boost::mutex _mutexGui;                 ///< For thread safetyness
};

}
}
}

#endif
