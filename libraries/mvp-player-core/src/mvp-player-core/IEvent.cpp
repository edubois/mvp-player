#include "IEvent.hpp"
#include <boost/serialization/export.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

namespace mvpplayer
{

IEvent::IEvent()
{
}

IEvent::~IEvent()
{}

}

BOOST_CLASS_EXPORT_IMPLEMENT( mvpplayer::IEvent );
