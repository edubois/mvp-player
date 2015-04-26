#ifndef _GUI_MVPPLAYERSETTINGSPAGE_HPP_
#define	_GUI_MVPPLAYERSETTINGSPAGE_HPP_

#include <mvp-player-core/Settings.hpp>
#include <mvp-player-core/MVPPlayerPresenter.hpp>
#include <mvp-player-core/MVPPlayerEngine.hpp>
#include <mvp-player-gui/IMVPPlayerDialog.hpp>

#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>

namespace mvpplayer
{
namespace gui
{
namespace qt
{

class PlayerConfigurationPage : public QWidget
{
public:
    PlayerConfigurationPage( Settings & editedSettings, mvpplayer::MVPPlayerEngine & model, mvpplayer::gui::IMVPPlayerDialog & view, mvpplayer::logic::MVPPlayerPresenter & presenter, QWidget *parent = 0);

    /**
     * @brief copy GUI values into settings structure
     */
    void updateSettings();

private:
    QSpinBox *_startPos;                                ///< Player start position (default = 0)

private:
    Settings & _editedSettings;                         ///< Edited settings
    mvpplayer::MVPPlayerEngine           & _model;      ///< MVP Player model
    mvpplayer::gui::IMVPPlayerDialog     & _view;       ///< MVP Player view
    mvpplayer::logic::MVPPlayerPresenter & _presenter;  ///< MVP Player presenter
};


class PluginsConfigurationPage : public QWidget
{
    Q_OBJECT
public:
    PluginsConfigurationPage( Settings & editedSettings, mvpplayer::MVPPlayerEngine & model, mvpplayer::gui::IMVPPlayerDialog & view, mvpplayer::logic::MVPPlayerPresenter & presenter, QWidget *parent = 0 );
    
    /**
     * @brief copy GUI values into settings structure
     */
    void updateSettings();

protected Q_SLOTS:
    void browsePluginDir();
    void reloadPlugins();

private:
    QWidget *getPluginPathEdit();

private:
    QLineEdit *_pathEdit;

private:
    Settings & _editedSettings;                             ///< Edited settings
    mvpplayer::MVPPlayerEngine              & _model;       ///< MVP Player model
    mvpplayer::gui::IMVPPlayerDialog        & _view;        ///< MVP Player view
    mvpplayer::logic::MVPPlayerPresenter    & _presenter;   ///< MVP Player presenter
};

}
}
}

#endif
