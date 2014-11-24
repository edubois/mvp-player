#include "MVPPlayerDialog.hpp"

#include <QtWidgets/QFileDialog>

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

    connect( widget.btnPlay, SIGNAL( clicked(bool) ), this, SLOT( slotViewHitPlayStopBtn() ) );
}

MVPPlayerDialog::~MVPPlayerDialog()
{
}

void MVPPlayerDialog::slotViewHitPlayStopBtn()
{
    if ( widget.btnPlay->text() == kStopCaption )
    {
        signalViewHitStop();
    }
    else
    {
        signalViewHitPlay( std::string() );
    }
}

}
}
}
