#include "mvpPlayerSettingsPages.hpp"

#include <mvp-player-pluger/PluginLoader.hpp>

#include <boost-adds/environment.hpp>

#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QFileDialog>

#include <limits>

namespace mvpplayer
{
namespace gui
{
namespace qt
{

PlayerConfigurationPage::PlayerConfigurationPage( Settings & editedSettings, mvpplayer::MVPPlayerEngine & model, mvpplayer::gui::IMVPPlayerDialog & view, mvpplayer::logic::MVPPlayerPresenter & presenter, QWidget *parent )
: QWidget( parent )
, _editedSettings( editedSettings )
, _model( model )
, _view( view )
, _presenter( presenter )
{
    QGroupBox *configGroup = new QGroupBox( tr( "Player configuration" ) );

    QLabel *startPosLabel = new QLabel( tr( "Start position (ms)" ) );
    _startPos = new QSpinBox();
    try { _startPos->setValue( _editedSettings.get<int>( "player", "startPosition" ) ); } catch ( ... ) {}
    _startPos->setRange( 0, std::numeric_limits<int>::max()-1 );

    QFormLayout *playerConfLayout = new QFormLayout();
    playerConfLayout->addRow( startPosLabel, _startPos );
    playerConfLayout->setFieldGrowthPolicy( QFormLayout::ExpandingFieldsGrow );

    QVBoxLayout *pageLayout = new QVBoxLayout();
    pageLayout->addLayout( playerConfLayout );
    configGroup->setLayout( pageLayout );

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget( configGroup );
    mainLayout->addStretch( 1 );
    setLayout( mainLayout );
}

void PlayerConfigurationPage::updateSettings()
{
    _editedSettings.set( "player", "startPosition", _startPos->value() );
}

PluginsConfigurationPage::PluginsConfigurationPage( Settings & editedSettings, mvpplayer::MVPPlayerEngine & model, mvpplayer::gui::IMVPPlayerDialog & view, mvpplayer::logic::MVPPlayerPresenter & presenter, QWidget *parent )
: QWidget( parent )
, _editedSettings( editedSettings )
, _model( model )
, _view( view )
, _presenter( presenter )
{
    QGroupBox *configGroup = new QGroupBox( tr( "Plugins configuration" ) );

    QLabel *pluginPathLabel = new QLabel( tr( "Plugin path" ) );
    QWidget *pathEdit = getPluginPathEdit();

    QFormLayout *pluginsConfLayout = new QFormLayout();
    pluginsConfLayout->addRow( pluginPathLabel, pathEdit );
    pluginsConfLayout->setFieldGrowthPolicy( QFormLayout::ExpandingFieldsGrow );

    QVBoxLayout *pageLayout = new QVBoxLayout();
    pageLayout->addLayout( pluginsConfLayout );
    configGroup->setLayout( pageLayout );

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget( configGroup );
    mainLayout->addStretch( 1 );
    setLayout( mainLayout );
}

QWidget *PluginsConfigurationPage::getPluginPathEdit()
{
    QWidget *parent = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins( 0, 0, 0, 0 );
    _pathEdit = new QLineEdit();
    boost::optional<std::string> envStr = boost::get_env( plugins::kMVPPlayerPluginEnvKey );
    _pathEdit->setPlaceholderText( QString::fromStdString( std::string("$") + plugins::kMVPPlayerPluginEnvKey ) );
    try { _pathEdit->setText( _editedSettings.get<std::string>( "plugins", "pluginsPath" ).c_str() ); } catch ( ... ) {}
    layout->addWidget( _pathEdit );

    QToolButton *btnBrowse = new QToolButton();
    btnBrowse->setIcon( QIcon( ":/mvpplayer/action/fileopen.png" ) );
    connect( btnBrowse, SIGNAL( released() ), this, SLOT( browsePluginDir() ) );
    btnBrowse->setToolTip( tr( "Browse plugin directory" ) );
    layout->addWidget( btnBrowse );

    QToolButton *btnReload = new QToolButton();
    btnReload->setIcon( QIcon( ":/mvpplayer/action/reload-plugins.png" ) );
    btnReload->setToolTip( tr( "Reload plugins" ) );
    connect( btnReload, SIGNAL( released() ), this, SLOT( reloadPlugins() ) );
    layout->addWidget( btnReload );

    parent->setLayout( layout );
    return parent;
}

void PluginsConfigurationPage::updateSettings()
{
    _editedSettings.set( "plugins", "pluginsPath", _pathEdit->text().toStdString() );
}

void PluginsConfigurationPage::reloadPlugins()
{
    // Reload plugins
    plugins::PluginLoader::getInstance().loadPlugins( _pathEdit->text().toStdString(), _model, _view, _presenter );
}

void PluginsConfigurationPage::browsePluginDir()
{
    QString defaultDir;
    if ( _pathEdit->text().size() == 0 )
    {
        boost::optional<std::string> envStr = boost::get_env( plugins::kMVPPlayerPluginEnvKey );
        std::string pluginPath = envStr.get_value_or( std::string() );
        defaultDir = QString::fromStdString( pluginPath );
    }
    else
    {
        defaultDir = _pathEdit->text();
    }

    const QString chosenDir = QFileDialog::getExistingDirectory( this, "Select mvp-player plugins directory", defaultDir );
    if ( chosenDir.size() )
    {
        _pathEdit->setText( chosenDir );
    }
}

}
}
}
