#ifndef _TESTS_MVPPLAYERGUIMOC_HPP_
#define	_TESTS_MVPPLAYERGUIMOC_HPP_

#include <mvp-player-gui/IMVPPlayerDialog.hpp>

namespace mvpplayer
{
namespace tests
{

/**
 * @brief MOC GUI for music player tests
 */
class MVPPlayerGuiMoc : public gui::IMVPPlayerDialog
{
public:
    MVPPlayerGuiMoc() {}
    virtual ~MVPPlayerGuiMoc() {}

    void setPlaylistItemIndex( const int row )
    { /* No GUI */ }

    virtual void setCurrentTrack( const boost::filesystem::path & filename )
    { /* No GUI */ }

    virtual void setIconStop()
    { /* No GUI */ }
    
    virtual void setIconPlay()
    { /* No GUI */ }

    virtual void openedPlaylist( const std::vector<m3uParser::PlaylistItem> & playlistItems )
    { /* No GUI */ }
};

}
}

#endif

