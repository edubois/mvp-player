#ifndef _MPV_PLAYER_GUI_PLAYERBEHAVIOR_HPP_
#define	_MPV_PLAYER_GUI_PLAYERBEHAVIOR_HPP_

#include "IMVPPlayerDialog.hpp"
#include <mvp-player-core/IMVPPlayerEngine.hpp>
#include <mvp-player-core/MVPPlayerLogic.hpp>

namespace mvpplayer
{
namespace gui
{

/**
 * @brief Setup music player's behavior (connect signals between the model/view/presenter)
 */
void setupMainBehavior( mvpplayer::IMVPPlayerEngine & m, mvpplayer::gui::IMVPPlayerDialog & v, mvpplayer::logic::PlayerStateMachine & p );

}
}

#endif
