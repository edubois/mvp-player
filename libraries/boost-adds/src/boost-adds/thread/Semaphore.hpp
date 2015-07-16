#ifndef _BOOSTADDS_SEMAPHORE_HPP_
#define	_BOOSTADDS_SEMAPHORE_HPP_

#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <algorithm>

namespace boost
{

class Semaphore
{
public:
    Semaphore();
    ~Semaphore();

    /**
     * @brief stack one ring
     */
    void post( const int n = 1 )
    {
        _availableRings += n;
        if ( _availableRings > 0 )
        {
            _synchroCondition.notify_all();
        }
    }

    /**
     * @brief wait until a ring is in
     */
    inline void wait()
    { _synchroCondition.wait( _synchro, [this](){ return take(); } ); }

    /**
     * @brief take on ring
     * @return true if rings are left
     */
    inline bool take()
    {
        if ( _availableRings > 0 )
        {
            return _availableRings-- > 0;
        }
        else
        {
            return false;
        }
    }

    /**
     * @brief take all tickets
     */    
    inline void takeAll()
    { _availableRings = 0; }

private:
    std::atomic_int _availableRings{0};             ///< Rings available
    std::mutex _mutexSynchro;                       ///< Mutex thread
    std::condition_variable _synchroCondition;      ///< Synchronization condition
    std::unique_lock<std::mutex> _synchro;          ///< Lock for condition variable
};

}

#endif
