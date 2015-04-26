#ifndef __MVPPLAYER_MVPPLAYERSETTINGSDIALOG_H_
#define	__MVPPLAYER_MVPPLAYERSETTINGSDIALOG_H_

#include "mvpPlayerSettingsPages.hpp"

#include <mvp-player-core/Settings.hpp>
#include <mvp-player-core/MVPPlayerPresenter.hpp>
#include <mvp-player-core/MVPPlayerEngine.hpp>
#include <mvp-player-gui/IMVPPlayerDialog.hpp>

#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
QT_END_NAMESPACE

namespace mvpplayer
{
namespace gui
{
namespace qt
{

class MVPPlayerSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    MVPPlayerSettingsDialog( mvpplayer::MVPPlayerEngine & model, mvpplayer::gui::IMVPPlayerDialog & view, mvpplayer::logic::MVPPlayerPresenter & presenter, QDialog *parent = NULL );
    virtual ~MVPPlayerSettingsDialog();
    

public Q_SLOTS:
    void accept();
    void changePage( QListWidgetItem *current, QListWidgetItem *previous );

private:
    void createIcons();

private:
    QListWidget *_contentsWidget;
    QStackedWidget *_pagesWidget;
    PlayerConfigurationPage *_playerConfigPage;
    PluginsConfigurationPage *_pluginConfigPage;

private:
    Settings _editedSettings;                               ///< Edited settings
    mvpplayer::MVPPlayerEngine              & _model;       ///< MVP Player model
    mvpplayer::gui::IMVPPlayerDialog        & _view;        ///< MVP Player view
    mvpplayer::logic::MVPPlayerPresenter    & _presenter;   ///< MVP Player presenter
};

}
}
}

#endif
