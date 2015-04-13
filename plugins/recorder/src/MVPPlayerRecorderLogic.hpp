#ifndef _MVPPLAYERRECORDERLOGIC_HPP_
#define	_MVPPLAYERRECORDERLOGIC_HPP_

#include <mvp-player-core/MVPPlayerLogic.hpp>

namespace mvpplayer
{
namespace logic
{

namespace plugin
{

/**
 * @brief Recording state
 */
struct Recording : sc::simple_state< Recording, Active >
{
    typedef boost::mpl::list<
      sc::custom_reaction< EvStop >
    >;

    /**
     * @brief reaction on stop track event
     */
    sc::result react( const EvStop & ev )
    {
        context< PlayerStateMachine >().presenter.stopped();
        return transit< Stopped >();
    }

};

}
}
}

#endif
