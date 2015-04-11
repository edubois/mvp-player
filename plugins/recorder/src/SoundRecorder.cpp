#include "SoundRecorder.hpp"

namespace mvpplayer
{

namespace
{

FMOD_SOUND_FORMAT getTheRightRawFormat( const std::size_t bitDepth )
{
    switch( bitDepth )
    {
        case 8:
            return FMOD_SOUND_FORMAT_PCM8;
        case 16:
            return FMOD_SOUND_FORMAT_PCM16;
        case 24:
            return FMOD_SOUND_FORMAT_PCM24;
        case 32:
            return FMOD_SOUND_FORMAT_PCM32;
        case 64:
            return FMOD_SOUND_FORMAT_PCMFLOAT;
        default:
            return FMOD_SOUND_FORMAT_PCM16;
    }
}

}

SoundRecorder::SoundRecorder()
: _recordDriver( 0 )
, _fmodsystem( nullptr )
, _sound( nullptr )
, _channel( nullptr )
{
    FMOD::System_Create( &_fmodsystem );
    initialize();
}

SoundRecorder::~SoundRecorder()
{
    stopRecording();
}

/**
 * @brief Initializes capture
 */
void SoundRecorder::initialize()
{
    stopRecording();
    memset( &_soundInfo, 0, sizeof( FMOD_CREATESOUNDEXINFO ) );
    _soundInfo.cbsize = sizeof( FMOD_CREATESOUNDEXINFO );
 
    // The length of the entire sample in bytes, calculated as:
    // Sample rate * number of channels * bits per sample per channel * number of seconds
    _soundInfo.length            = _sampleRate * _channels * _bitDepth * _sampleDuration;

    // Number of channels and sample rate
    _soundInfo.numchannels       = _channels;
    _soundInfo.defaultfrequency  = _sampleRate;

    // The sound format
    _soundInfo.format            = getTheRightRawFormat( _bitDepth );

    // Create a user-defined sound with FMOD_LOOP_NORMAL | FMOD_OPENUSER long
    // enought to record a little of sound
    _fmodsystem->createSound( 0, FMOD_LOOP_NORMAL | FMOD_OPENUSER, &_soundInfo, &_sound );
}

/**
 * @brief start recording
 * @warning setNbSamples, setBitDepth, setFilename must have been called
 */
void SoundRecorder::startRecording()
{
    // Create sound recording buffer
    initialize();
    // Start recording sound card output into empty sound, looping back to the start
    // and over-writing the oldest data when the sound is full
    _fmodsystem->recordStart( _recordDriver, _sound, true );

    // Start playing the recorded sound back, silently, so we can use its
    // channel to get the FFT data. The frequency analysis is done before the
    // volume is adjusted so it doesn't matter that we are playing back silently.
    _fmodsystem->playSound( _sound, NULL, false, &_channel );
    _channel->setVolume( 0 );
}

/**
 * @brief stop recording
 */
void SoundRecorder::stopRecording()
{
    // Stop silent playback
    if ( _channel )
    {
        _channel->stop();
        _channel = nullptr;
    }

    // Stop recording
    if ( _recordDriver )
    {
        _fmodsystem->recordStop( _recordDriver );
        _recordDriver = 0;
    }

    // Free sound recording buffer
    if ( _sound )
    {
        _sound->release();
        _sound = nullptr;
    }
}

}
