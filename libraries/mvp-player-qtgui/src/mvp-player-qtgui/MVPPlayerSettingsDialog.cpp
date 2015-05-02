#include "MVPPlayerSettingsDialog.hpp"

#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

namespace mvpplayer
{
namespace gui
{
namespace qt
{

MVPPlayerSettingsDialog::MVPPlayerSettingsDialog( mvpplayer::MVPPlayerEngine & model, mvpplayer::gui::IMVPPlayerDialog & view, mvpplayer::logic::MVPPlayerPresenter & presenter, QWidget *parent )
: QDialog( parent )
, _editedSettings( Settings::getInstance() )
, _model( model )
, _view( view )
, _presenter( presenter )
{
#ifndef ANDROID
    setMinimumWidth( 540 );
#endif
    
    _contentsWidget = new QListWidget();
    _contentsWidget->setViewMode( QListView::IconMode );
    _contentsWidget->setIconSize( QSize( 64, 64 ) );
    _contentsWidget->setMovement( QListView::Static );
    _contentsWidget->setMinimumHeight( 2 * ( 96 + 12 ) + 12 );
    _contentsWidget->setMinimumWidth( 100 );
    _contentsWidget->setMaximumWidth( 100 );
    _contentsWidget->setSpacing( 12 );

    _pagesWidget = new QStackedWidget();
    _playerConfigPage = new PlayerConfigurationPage( _editedSettings, _model, _view, _presenter );
    _pagesWidget->addWidget( _playerConfigPage );
    _pluginConfigPage = new PluginsConfigurationPage( _editedSettings, _model, _view, _presenter );
    _pagesWidget->addWidget( _pluginConfigPage );

    QPushButton *saveSettingsButton = new QPushButton( tr("&Save") );
    connect( saveSettingsButton, SIGNAL( clicked() ), this, SLOT( accept() ) );

    QPushButton *closeButton = new QPushButton( tr("&Close") );
    connect( closeButton, SIGNAL( clicked() ), this, SLOT( reject() ) );

    createIcons();
    _contentsWidget->setCurrentRow(0);

    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->addWidget( _contentsWidget );
    horizontalLayout->addWidget( _pagesWidget, 1 );

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addStretch( 1 );
    buttonsLayout->addWidget( saveSettingsButton );
    buttonsLayout->addWidget( closeButton );

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout( horizontalLayout );
    mainLayout->addStretch( 1 );
    mainLayout->addSpacing( 12 );
    mainLayout->addLayout( buttonsLayout );
    setLayout( mainLayout );

    setWindowTitle( tr("MVP-Player Settings") );
}

MVPPlayerSettingsDialog::~MVPPlayerSettingsDialog()
{
}

void MVPPlayerSettingsDialog::accept()
{
    _playerConfigPage->updateSettings();
    _pluginConfigPage->updateSettings();
    Settings::getInstance().merge( _editedSettings );
    close();
}

void MVPPlayerSettingsDialog::createIcons()
{
    QListWidgetItem *configButton = new QListWidgetItem( _contentsWidget );
    configButton->setIcon( QIcon( ":/mvpplayer/toolbar/player-settings.png" ) );
    configButton->setText( tr( "Player" ) );
    configButton->setTextAlignment( Qt::AlignHCenter );
    configButton->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

    QListWidgetItem *pluginConfigButton = new QListWidgetItem( _contentsWidget );
    pluginConfigButton->setIcon( QIcon( ":/mvpplayer/toolbar/plugins-settings.png" ) );
    pluginConfigButton->setText( tr( "Plugins" ) );
    pluginConfigButton->setTextAlignment( Qt::AlignHCenter );
    pluginConfigButton->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

    connect( _contentsWidget,
             SIGNAL( currentItemChanged( QListWidgetItem*, QListWidgetItem* ) ),
             this, SLOT( changePage( QListWidgetItem*, QListWidgetItem* ) ) );
}

void MVPPlayerSettingsDialog::changePage( QListWidgetItem *current, QListWidgetItem *previous )
{
    if ( !current )
        current = previous;

    _pagesWidget->setCurrentIndex( _contentsWidget->row( current ) );
}

}
}
}
