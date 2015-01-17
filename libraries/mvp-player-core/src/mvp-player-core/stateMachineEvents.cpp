#include <boost/serialization/export.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "stateMachineEvents.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( mvpplayer::logic::EvStop );
BOOST_CLASS_EXPORT_IMPLEMENT( mvpplayer::logic::EvRestartTrack );
BOOST_CLASS_EXPORT_IMPLEMENT( mvpplayer::logic::EvPreviousTrack );
BOOST_CLASS_EXPORT_IMPLEMENT( mvpplayer::logic::EvNextTrack );
BOOST_CLASS_EXPORT_IMPLEMENT( mvpplayer::logic::EvClearPlaylist );
BOOST_CLASS_EXPORT_IMPLEMENT( mvpplayer::logic::EvModelClearedPlaylist );
BOOST_CLASS_EXPORT_IMPLEMENT( mvpplayer::logic::EvStartPlaylist );
BOOST_CLASS_EXPORT_IMPLEMENT( mvpplayer::logic::EvEndOfTrack );
BOOST_CLASS_EXPORT_IMPLEMENT( mvpplayer::logic::EvPlay );
BOOST_CLASS_EXPORT_IMPLEMENT( mvpplayer::logic::EvPlayed );
BOOST_CLASS_EXPORT_IMPLEMENT( mvpplayer::logic::EvAddTrack );
BOOST_CLASS_EXPORT_IMPLEMENT( mvpplayer::logic::EvAddedTrack );
BOOST_CLASS_EXPORT_IMPLEMENT( mvpplayer::logic::EvOpenedPlaylist );
BOOST_CLASS_EXPORT_IMPLEMENT( mvpplayer::logic::EvPlayingItemIndex );
BOOST_CLASS_EXPORT_IMPLEMENT( mvpplayer::logic::EvPlayItemAtIndex );
BOOST_CLASS_EXPORT_IMPLEMENT( mvpplayer::logic::EvReset );
