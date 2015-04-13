#include "MVPPlayerPresenter.hpp"

namespace mvpplayer
{
namespace logic
{

/**
 * @brief pause the processor, call the lambda function, restart the processor
 */
bool MVPPlayerPresenter::processSequencial( const std::function<void()> lambda )
{
    try
    {
        boost::mutex::scoped_lock threadPause( _schedulerWorker.mutex() );
        lambda();
        return false;
    }
    catch( ... )
    {
        return true;
    }
}

/**
 * @brief process an event
 */
void MVPPlayerPresenter::processEvent( IEvent & event )
{
    event.processSelf( _scheduler, _playerProcessor );
}

/**
 * @brief process play, stop, next, previous commands
 * @param commandName command name
 */
void MVPPlayerPresenter::processCommand( const std::string & commandName )
{
    if ( commandName == "Play" )
    {
        processPlay( boost::none );
    }
    else if ( commandName == "Stop" )
    {
        processStop();
    }
    else if ( commandName == "Previous" )
    {
        processPrevious();
    }
    else if ( commandName == "Next" )
    {
        processNext();
    }
}


}
}
