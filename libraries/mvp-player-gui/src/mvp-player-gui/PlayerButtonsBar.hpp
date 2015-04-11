#ifndef _PLAYERBUTTONSBAR_HPP_
#define	_PLAYERBUTTONSBAR_HPP_

#include "ButtonDescriptor.hpp"

#include <deque>

namespace mvpplayer
{
namespace gui
{

class PlayerButtonsBar
{
public:
    typedef std::deque<ButtonDescriptor> ButtonCollection;
public:
    PlayerButtonsBar();
    virtual ~PlayerButtonsBar();
    
    /**
     * @brief get the buttons of the button bar
     */
    inline const ButtonCollection & buttons() const
    { return _buttons; }

    /**
     * @brief append button descriptor at the end
     */
    void appendButton( const ButtonDescriptor & desc );

    /**
     * @brief preppend button descriptor at the beginning
     */
    void prependButton( const ButtonDescriptor & desc );

private:
    std::deque<ButtonDescriptor> _buttons;
};

}
}

#endif
