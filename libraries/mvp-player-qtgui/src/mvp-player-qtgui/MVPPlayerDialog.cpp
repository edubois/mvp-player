/* 
 * File:   MVPPlayerDialog.cpp
 * Author: djarwood
 * 
 * Created on 10 avril 2015, 23:56
 */

#include "MVPPlayerDialog.hpp"

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

}
}
}
