#include "dlgUtils.hpp"

#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>

namespace mvpplayer
{
namespace gui
{
namespace qt
{

boost::filesystem::path openFile( const std::string & title, const std::string & extensions )
{
    return QFileDialog::getOpenFileName( QApplication::activeWindow(), QString::fromStdString( title ),
                                         "/Users",
                                         QString::fromStdString( extensions ) ).toStdString();
}

void displayError( const std::string & msg )
{
    QMessageBox::critical( QApplication::activeWindow(), QObject::tr( "Error!" ), QString::fromStdString( msg ), QMessageBox::Ok | QMessageBox::Default);
}

}
}
}

