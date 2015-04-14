#ifndef _MVPPLAYERRECORDERLOGIC_HPP_
#define	_MVPPLAYERRECORDERLOGIC_HPP_

#include <mvp-player-core/MVPPlayerLogic.hpp>
#include <mvp-player-core/stateMachineEvents.hpp>

#include <iostream>

namespace mvpplayer
{
namespace logic
{

namespace fs = boost::filesystem;
namespace sc = boost::statechart;

namespace plugin
{

/**
 * @brief Recording state
 */
struct Recording : sc::simple_state< Recording, Active >
{
    typedef boost::mpl::list<
      sc::custom_reaction< EvStop >
    > reactions;

    /**
     * @brief reaction on stop track event
     */
    sc::result react( const EvStop & ev )
    {
        std::cout << "record stop." << std::endl;
        context< PlayerStateMachine >().presenter.stopped();
        return transit< Stopped >();
    }

};

}

}
}

#endif
