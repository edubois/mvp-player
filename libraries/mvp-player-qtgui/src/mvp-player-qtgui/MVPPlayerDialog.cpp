#include "MVPPlayerDialog.hpp"
#include "mvp-player-core/MVPPlayerPresenter.hpp"

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtGui/QKeyEvent>

namespace mvpplayer
{
namespace gui
{
namespace qt
{

MVPPlayerDialog::MVPPlayerDialog( QWidget *parent )
: QDialog( parent )
, _btnPlayPause( nullptr )
, _btnPrevious( nullptr )
, _btnNext( nullptr )
{
}

MVPPlayerDialog::~MVPPlayerDialog()
{
}

boost::optional<boost::filesystem::path> MVPPlayerDialog::openFile( const std::string & title, const logic::EFileDialogMode mode, const std::string & extensions )
{
    QString result;
    QMetaObject::invokeMethod( this, "slotOpenFile", Qt::BlockingQueuedConnection, Q_RETURN_ARG( QString, result ), Q_ARG( QString, QString::fromStdString( title ) ), Q_ARG( QString, QString::fromStdString( extensions ) ), Q_ARG( logic::EFileDialogMode, mode ) );
    if ( !result.isEmpty() )
    {
        return boost::filesystem::path( result.toStdString() );
    }
    else
    {
        return boost::none;
    }
}

QString MVPPlayerDialog::slotOpenFile( const QString & title, const QString & extensions, const logic::EFileDialogMode mode )
{
    if ( mode == logic::eFileDialogModeOpen )
    {
        return QFileDialog::getOpenFileName( QApplication::activeWindow(), title, QDir::currentPath(), extensions );
    }
    else
    {
        return QFileDialog::getSaveFileName( QApplication::activeWindow(), title, QDir::currentPath(), extensions );
    }
}

void MVPPlayerDialog::slotDisplayError( const QString & msg )
{
    QMessageBox::critical( QApplication::activeWindow(), QObject::tr( "Error!" ), msg, QMessageBox::Ok | QMessageBox::Default);
}

void MVPPlayerDialog::setButtonChecked( const std::string & buttonName, const bool checked )
{
    auto it = _playerButtonsWidgets.find( buttonName );
    if ( it != _playerButtonsWidgets.end() )
    {
        it->second->setChecked( false );
    }
}

void MVPPlayerDialog::keyPressEvent( QKeyEvent* event )
{
    QMessageBox::information( QApplication::activeWindow(), "test", QString::number( event->key() ) );
}

void MVPPlayerDialog::slotViewHitButton()
{
    QToolButton *button = qobject_cast<QToolButton*>( sender() );
    assert( button );
    if ( button->isCheckable() )
    {
        signalViewHitButton( button->objectName().toStdString(), button->isChecked() );
    }
    else
    {
        signalViewHitButton( button->objectName().toStdString(), true );
    }
}

void MVPPlayerDialog::changeTrackPosition( const int positionInPercent )
{
    signalViewHitTrackPosition( positionInPercent );
}

}
}
}
