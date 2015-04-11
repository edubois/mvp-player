#include "PlayerButtonsBar.hpp"

namespace mvpplayer
{
namespace gui
{

PlayerButtonsBar::PlayerButtonsBar()
{
}

PlayerButtonsBar::~PlayerButtonsBar()
{
}

void PlayerButtonsBar::appendButton( const ButtonDescriptor & desc )
{
    _buttons.push_back( desc );
}

void PlayerButtonsBar::prependButton( const ButtonDescriptor & desc )
{
    _buttons.push_front( desc );
}

}
}
