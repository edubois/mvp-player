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

    void setCurrentTrack( const boost::filesystem::path & filename );

    void setPlaylistItemIndex( const int row );

    void setIconStop();

    void setIconPlay();

    int exec();

    void openedPlaylist( const std::vector<m3uParser::PlaylistItem> & playlistItems );

    void clearPlaylist();

    void addTrack( const boost::filesystem::path & filename );

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
