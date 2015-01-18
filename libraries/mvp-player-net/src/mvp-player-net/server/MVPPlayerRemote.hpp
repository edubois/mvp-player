#ifndef _MVPPLAYER_NETWORK_REMOTE_HPP_
#define	_MVPPLAYER_NETWORK_REMOTE_HPP_

#include "Server.hpp"
#include <mvp-player-gui/IMVPPlayerDialog.hpp>

namespace mvpplayer
{
namespace network
{
namespace server
{

class MVPPlayerRemote : public gui::IMVPPlayerDialog
{
public:
    MVPPlayerRemote( Server & server );
    virtual ~MVPPlayerRemote();

    void setCurrentTrack( const boost::filesystem::path & filename ) override;

    void setPlaylistItemIndex( const int row ) override;

    void setIconStop() override;

    void setIconPlay() override;

    void openedPlaylist( const std::vector<m3uParser::PlaylistItem> & playlistItems ) override;

    void clearPlaylist() override;

    void addTrack( const boost::filesystem::path & filename ) override;

private:
    Server & _server;       ///< MVP Player server (used to send events)
};

}
}
}

#endif
