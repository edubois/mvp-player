#include "ISoundRecorder.hpp"
#include <iostream>

namespace mvpplayer
{

ISoundRecorder::ISoundRecorder()
: _thresholdVolumeHigh( 50.00 )
, _sampleDuration( 1.0 / 100.0 )
, _bitDepth( 0 )
, _sampleRate( 0 )
{
    _lastVolumeHighTime = std::chrono::system_clock::now();
}

ISoundRecorder::~ISoundRecorder()
{
}

/**
 * @brief stop recording
 * @param volume captured sample
 */
void ISoundRecorder::signalizeVolumeHigh( const float volume )
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    if ( std::chrono::duration_cast<std::chrono::milliseconds>( now - _lastVolumeHighTime ).count() >= kLatencyVolumeHighThreshold )
    {
        _lastVolumeHighTime = now;
        signalVolumeHigh( volume );
    }
}


}
