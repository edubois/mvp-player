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

}
}
