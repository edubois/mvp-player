#ifndef _NCURSES_MVPPLAYERDIALOG_HPP_
#define	_NCURSES_MVPPLAYERDIALOG_HPP_

#include <mvp-player-gui/IMVPPlayerDialog.hpp>

#include <ncurses.h>
#include <cdk.h>

#include <boost/signals2.hpp>
#include <boost/filesystem/path.hpp>
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

private:
    void initWin( const std::string & currentTrack, const bool playButton = true );
    void openPlaylist( const boost::filesystem::path & playlistFilename );

private:
    CDKSCREEN* _cdkScreen;
    CDKDIALOG* _childwin;
    CDKSCROLL* _playlist;
    bool _isPlaying;
};

}
}
}

#endif
