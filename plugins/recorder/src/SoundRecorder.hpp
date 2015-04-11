#ifndef _CORE_SOUNDRECORDER_HPP_
#define	_CORE_SOUNDRECORDER_HPP_

#include "ISoundRecorder.hpp"
#include <mvp-player-core/Singleton.hpp>

#include <fmod.hpp>

namespace mvpplayer
{

class SoundRecorder : public ISoundRecorder, public Singleton<SoundRecorder>
{
public:
    SoundRecorder();
    virtual ~SoundRecorder();

    /**
     * @brief start recording
     * @warning setNbSamples, setBitDepth, setFilename must have been called
     */
    void startRecording();

    /**
     * @brief stop recording
     */
    void stopRecording();

private:
    void initialize();

protected:
    int _recordDriver;                      ///< Recording driver handle
    FMOD::System* _fmodsystem;              ///< FMOD engine
    FMOD::Sound* _sound;                    ///< Sound instance
    FMOD::Channel* _channel;                ///< Sound channel
    FMOD_CREATESOUNDEXINFO _soundInfo;      ///< Sound buffer where we do the capture
};

}

#endif
