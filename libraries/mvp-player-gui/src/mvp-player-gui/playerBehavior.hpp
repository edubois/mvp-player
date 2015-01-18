#ifndef _MPV_PLAYER_GUI_PLAYERBEHAVIOR_HPP_
#define	_MPV_PLAYER_GUI_PLAYERBEHAVIOR_HPP_

#include "IMVPPlayerDialog.hpp"
#include <mvp-player-core/MVPPlayerEngine.hpp>
#include <mvp-player-core/MVPPlayerPresenter.hpp>

namespace mvpplayer
{
namespace gui
{

/**
 * @brief Setup music player's behavior (connect signals between the model/view/presenter)
 */
void setupMainBehavior( mvpplayer::MVPPlayerEngine & m, mvpplayer::gui::IMVPPlayerDialog & v, mvpplayer::logic::MVPPlayerPresenter & p );
void connectViewPresenter( mvpplayer::gui::IMVPPlayerDialog & v, mvpplayer::logic::MVPPlayerPresenter & p );
void connectPresenterModel( mvpplayer::logic::MVPPlayerPresenter & p, mvpplayer::MVPPlayerEngine & m );

}
}

#endif
