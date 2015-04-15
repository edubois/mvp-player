#ifndef _MVPPLUGIN_RECORDEREVENTS_HPP_
#define	_MVPPLUGIN_RECORDEREVENTS_HPP_

#include <mvp-player-core/MVPPlayerLogic.hpp>
#include <mvp-player-core/stateMachineEvents.hpp>

namespace mvpplayer
{
namespace logic
{

namespace fs = boost::filesystem;
namespace sc = boost::statechart;

namespace plugin
{

/**
 * @brief event stop
 */
struct EvRecord : IEvent, sc::event< EvRecord >
{
private:
    typedef EvRecord This;
public:
    // This is needed to avoid a strange error on BOOST_CLASS_EXPORT_KEY
    static void operator delete( void *p, const std::size_t n )
    { ::operator delete(p); }

    friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<IEvent>( *this );
    }

    /**
     * @brief process this event (needed to avoid dynamic_casts)
     * @param scheduler event scheduler
     * @param processor event processor
     */
    void processSelf( boost::statechart::fifo_scheduler<> & scheduler, boost::statechart::fifo_scheduler<>::processor_handle & processor )
    {
        scheduler.queue_event( processor, boost::intrusive_ptr< This >( this ) );
    }
};

}

}
}

#endif
