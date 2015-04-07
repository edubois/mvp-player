#include "MVPPlayerSettingsDialog.hpp"

namespace mvpplayer
{
namespace gui
{
namespace qt
{

MVPPlayerSettingsDialog::MVPPlayerSettingsDialog( QDialog *parent )
: QDialog( parent )
{
    widget.setupUi(this);
}

MVPPlayerSettingsDialog::~MVPPlayerSettingsDialog()
{
}

}
}
}
