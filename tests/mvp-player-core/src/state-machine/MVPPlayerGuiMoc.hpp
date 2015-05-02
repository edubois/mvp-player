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

    void setPlaylistItemIndex( const int row ) override
    { /* No GUI */ }

    virtual void setCurrentTrack( const boost::filesystem::path & filename ) override
    { /* No GUI */ }

    virtual void setIconStop() override
    { /* No GUI */ }
    
    virtual void setIconPlay() override
    { /* No GUI */ }

    virtual void openedPlaylist( const std::vector<m3uParser::PlaylistItem> & playlistItems ) override
    { /* No GUI */ }

    virtual void addTrack( const boost::filesystem::path & filename ) override
    { /* No GUI */ }

    virtual void clearedPlaylist() override
    { /* No GUI */ }
};

}
}

#endif

