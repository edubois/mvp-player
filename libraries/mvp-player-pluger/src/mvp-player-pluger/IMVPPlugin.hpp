#ifndef _MVP_PLAYER_PLUGER_IMVPPLUGIN_HPP_
#define	_MVP_PLAYER_PLUGER_IMVPPLUGIN_HPP_

#include <mvp-player-core/MVPPlayerPresenter.hpp>
#include <mvp-player-core/MVPPlayerEngine.hpp>
#include <mvp-player-gui/IMVPPlayerDialog.hpp>

namespace mvpplayer
{
namespace plugins
{

/**
 * Interface for MVP Player plugins
 */
class IMVPPlugin
{
public:
    IMVPPlugin();
    virtual ~IMVPPlugin();

    /**
     * @brief must be called to setup the plugin
     * @param model the MVP Player model
     * @param view the MVP Player view
     * @param presenter the MVP Player presenter
     */
    virtual void setup( MVPPlayerEngine & model, gui::IMVPPlayerDialog & view, logic::MVPPlayerPresenter & presenter )
    {
        _model = &model;
        _view = &view;
        _presenter = &presenter;
    }

private:
    MVPPlayerEngine *_model;                        ///< MVP Player model
    gui::IMVPPlayerDialog     *_view;               ///< MVP Player view
    logic::MVPPlayerPresenter *_presenter;          ///< MVP Player presenter
};

}
}

#endif	/* IMVPPLUGIN_HPP */

