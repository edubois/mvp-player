#ifndef _IMVPPLAYERDIALOG_HPP
#define	_IMVPPLAYERDIALOG_HPP

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

    virtual void setIconStop() = 0;

    virtual void setIconPlay() = 0;

public:
    boost::signals2::signal<void( const std::string& )> signalViewHitPlay; ///< Signals that user hit play button
    boost::signals2::signal<void()> signalViewHitStop; ///< Signals that user hit stop button
};

}
}

#endif
