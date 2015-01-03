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
    connect( widget.btnPrevious, SIGNAL( clicked(bool) ), this, SLOT( slotViewHitPreviousBtn() ) );
}

MVPPlayerDialog::~MVPPlayerDialog()
{
}

void MVPPlayerDialog::slotViewHitPlayStopBtn()
{
    if ( widget.btnPlay->text().toStdString() == kStopCaption )
    {
        signalViewHitStop();
    }
    else
    {
        signalViewHitPlay( std::string() );
    }
}

void MVPPlayerDialog::slotViewHitPreviousBtn()
{
    signalViewHitPrevious();
}

}
}
}
