#include "Semaphore.hpp"

namespace boost
{

Semaphore::Semaphore()
: _synchro( _mutexSynchro )
{
}

Semaphore::~Semaphore()
{
    post( std::max( 1, -_availableRings + 1 ) );
}

}
