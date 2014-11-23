#include "MVPPlayerDialog.hpp"

namespace mvpplayer
{
namespace gui
{
namespace qt
{

MVPPlayerDialog::MVPPlayerDialog( QWidget *parent )
: QDialog( parent )
{
    widget.setupUi(this);
}

MVPPlayerDialog::~MVPPlayerDialog()
{
}

}
}
}
