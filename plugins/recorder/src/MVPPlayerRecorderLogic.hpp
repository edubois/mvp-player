#ifndef _MVPPLAYERRECORDERLOGIC_HPP_
#define	_MVPPLAYERRECORDERLOGIC_HPP_

#include "recorderEvents.hpp"

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

struct RecorderPluginPresenter : IPluginPresenter
{
    boost::signals2::signal<void( const boost::filesystem::path & filename )> signalRecord;
};

/**
 * @brief Recording state
 */
struct Recording : sc::simple_state< Recording, Active >
{
    typedef boost::mpl::list<
      sc::custom_reaction< EvRecord >,
      sc::custom_reaction< EvStop >
    > reactions;

    /**
     * @brief reaction on record event
     */
    sc::result react( const EvRecord & ev );

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
