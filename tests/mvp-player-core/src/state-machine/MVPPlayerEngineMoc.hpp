#ifndef _TESTS_MVPPLAYERENGINEMOC_HPP_
#define	_TESTS_MVPPLAYERENGINEMOC_HPP_

#include <mvp-player-core/IMVPPlayerEngine.hpp>

namespace mvpplayer
{
namespace tests
{

/**
 * @brief MOC Engine for music player tests
 */
class MVPPlayerEngineMoc : public IMVPPlayerEngine
{
public:
    MVPPlayerEngineMoc();
    virtual ~MVPPlayerEngineMoc();
};

}
}

#endif	/* MVPPLAYERENGINEMOC_HPP */
