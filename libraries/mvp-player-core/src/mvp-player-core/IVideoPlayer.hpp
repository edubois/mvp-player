#ifndef _CORE_IVIDEOPLAYER_HPP_
#define	_CORE_IVIDEOPLAYER_HPP_

#include "IFilePlayer.hpp"

namespace mvpplayer
{

class IVideoPlayer : public IFilePlayer
{
public:
    IVideoPlayer() {}
    virtual ~IVideoPlayer() {}
};

}

#endif
