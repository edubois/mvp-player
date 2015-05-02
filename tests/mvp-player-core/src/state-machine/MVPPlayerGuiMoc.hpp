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

    void setCurrentTrack( const boost::filesystem::path & filename ) override
    { /* No GUI */ }

    void setIconStop() override
    { /* No GUI */ }
    
    void setIconPlay() override
    { /* No GUI */ }

    void openedPlaylist( const std::vector<m3uParser::PlaylistItem> & playlistItems ) override
    { /* No GUI */ }

    void addTrack( const boost::filesystem::path & filename ) override
    { /* No GUI */ }

    void clearedPlaylist() override
    { /* No GUI */ }

    void setTrackLength( const std::size_t trackLengthInMS ) override
    { /* No GUI */ }

    void setButtonChecked( const std::string & buttonName, const bool checked ) override
    { /* No GUI */ }

    void setTrackPosition( const std::size_t positionInMS, const std::size_t trackLength ) override
    { /* No GUI */ }

    void setVolume( const float volume ) override
    { /* No GUI */ }
};

}
}

#endif

