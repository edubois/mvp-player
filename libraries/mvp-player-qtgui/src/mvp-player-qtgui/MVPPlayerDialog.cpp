#include "MVPPlayerDialog.hpp"
#include "mvp-player-core/MVPPlayerPresenter.hpp"

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

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
    QMetaObject::invokeMethod( this, "slotOpenFile", Qt::BlockingQueuedConnection, Q_RETURN_ARG( QString, result ), Q_ARG( QString, QString::fromStdString( title ) ), Q_ARG( QString, QString::fromStdString( extensions ) ) );
    if ( !result.isEmpty() )
    {
        return boost::filesystem::path( result.toStdString() );
    }
    else
    {
        return boost::none;
    }
}

QString MVPPlayerDialog::slotOpenFile( const QString & title, const QString & extensions )
{
    return QFileDialog::getOpenFileName( QApplication::activeWindow(), title, QDir::currentPath(), extensions );
}

void MVPPlayerDialog::slotDisplayError( const QString & msg )
{
    QMessageBox::critical( QApplication::activeWindow(), QObject::tr( "Error!" ), msg, QMessageBox::Ok | QMessageBox::Default);
}

}
}
}
