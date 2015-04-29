#ifndef _MVPPLAYER_CORE_IEVENT_HPP_
#define	_MVPPLAYER_CORE_IEVENT_HPP_

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/statechart/fifo_scheduler.hpp>


namespace mvpplayer
{

/**
 * Makes event serializable
 */
struct IEvent
{
    IEvent();
    virtual ~IEvent() = 0;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {}

    /**
     * @brief tell if this event shall be dispatched thru the network
     */
    virtual bool shallDispatch() const
    { return true; }

    /**
     * @brief process this event (needed to avoid dynamic_casts)
     * @param scheduler event scheduler
     * @param processor event processor
     */
    virtual void processSelf( boost::statechart::fifo_scheduler<> & scheduler, boost::statechart::fifo_scheduler<>::processor_handle & processor ) = 0;
};

}

BOOST_SERIALIZATION_ASSUME_ABSTRACT( mvpplayer::IEvent );
BOOST_CLASS_EXPORT_KEY( mvpplayer::IEvent );

#endif
