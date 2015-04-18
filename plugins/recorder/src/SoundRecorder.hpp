#ifndef _PLUG_SOUNDRECORDER_HPP_
#define	_PLUG_SOUNDRECORDER_HPP_

#include "ISoundRecorder.hpp"
#include <mvp-player-core/Singleton.hpp>

#include <boost/thread.hpp>
#include <boost/scoped_ptr.hpp>

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
     * @brief pause recording
     */
    void pauseRecording( const bool paused );

    /**
     * @brief stop recording
     */
    void stopRecording();

    inline FMOD::Channel & channel()
    { return *_channel; }

    /**
     * @brief is recording paused ?
     * @return 
     */
    inline bool paused() const
    {
        if ( _dsp )
        {
            bool isPaused = false;
            _dsp->getBypass( &isPaused );
            return isPaused;
        }
        else
        {
            return false;
        }
    }

private:
    void initialize();
    void createDSP();
    void updater();

protected:
    int _recordDriver;                      ///< Recording driver handle
    FMOD::System* _fmodsystem;              ///< FMOD engine
    FMOD::Sound* _sound;                    ///< Sound instance
    FMOD::Channel* _channel;                ///< Sound channel
    FMOD::DSP* _dsp;                        ///< DSP used to track the signal
    FMOD_CREATESOUNDEXINFO _soundInfo;      ///< Sound buffer where we do the capture

private:
    boost::scoped_ptr<boost::thread> _updaterThread; ///< Updater thread
    mutable boost::mutex _mutexRecorder;             ///< For thread safetyness
};

FMOD_RESULT F_CALLBACK dspCallback( FMOD_DSP_STATE *dspState, float *  inbuffer, float *  outbuffer, unsigned int  length, int  inchannels, int *outchannels );

}

#endif
