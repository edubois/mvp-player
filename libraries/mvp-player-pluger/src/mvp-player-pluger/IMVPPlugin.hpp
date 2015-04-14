#ifndef _MVP_PLAYER_PLUGER_IMVPPLUGIN_HPP_
#define	_MVP_PLAYER_PLUGER_IMVPPLUGIN_HPP_

#include <mvp-player-core/MVPPlayerPresenter.hpp>
#include <mvp-player-core/MVPPlayerEngine.hpp>
#include <mvp-player-gui/IMVPPlayerDialog.hpp>

#include <QtCore/QtCore>

namespace mvpplayer
{
namespace plugins
{

/**
 * Interface for MVP Player plugins
 */
class IMVPPlugin : public QObject
{
    Q_OBJECT
public:
    IMVPPlugin( QObject *parent = NULL )
    : QObject( parent )
    {}

    IMVPPlugin( const std::string & name, QObject *parent = NULL )
    : QObject( parent )
    , _pluginName( name )
    {}

    virtual ~IMVPPlugin()
    {}

    inline const std::string & pluginName() const
    { return _pluginName; }

    /**
     * @brief must be called to setup the plugin
     * @param model the MVP Player model
     * @param view the MVP Player view
     * @param presenter the MVP Player presenter
     */
    virtual void setup( mvpplayer::MVPPlayerEngine & model, mvpplayer::gui::IMVPPlayerDialog & view, mvpplayer::logic::MVPPlayerPresenter & presenter )
    {
        _model = &model;
        _view = &view;
        _presenter = &presenter;
    }
protected:
    std::string _pluginName;                        ///< The plugin's name
    mvpplayer::MVPPlayerEngine *_model;                        ///< MVP Player model
    mvpplayer::gui::IMVPPlayerDialog     *_view;               ///< MVP Player view
    mvpplayer::logic::MVPPlayerPresenter *_presenter;          ///< MVP Player presenter
};

}
}

#endif	/* IMVPPLUGIN_HPP */

