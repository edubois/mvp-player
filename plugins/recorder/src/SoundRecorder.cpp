#include "SoundRecorder.hpp"
#include <iostream>

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

    if ( _dsp )
    {
        _dsp->release();
    }

    if ( _fmodsystem )
    {
        _fmodsystem->close();
        _fmodsystem->release();
    }

    if ( _updaterThread )
    {
        _updaterThread->join();
    }
}

void SoundRecorder::updater()
{
    assert( _fmodsystem != nullptr );
    while( _sound && !paused() )
    {
        {
            boost::mutex::scoped_lock lock( _mutexRecorder );
            _fmodsystem->update();
        }
        std::cout << "ok "<< std::endl;

        // Wait 25ms
        boost::this_thread::sleep( boost::posix_time::milliseconds( 25 ) );
    }
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

    // Create the DSP effect that will track the signal.
    createDSP();
}

void SoundRecorder::createDSP()
{
    assert( _fmodsystem );
    
    FMOD_DSP_DESCRIPTION dspdesc; 
    memset(&dspdesc, 0, sizeof(dspdesc));

    strncpy( dspdesc.name, "DSP for recording", sizeof(dspdesc.name) );
    dspdesc.version = 0x00010000;
    dspdesc.numinputbuffers = 1;
    dspdesc.numoutputbuffers = 1;
    dspdesc.read = &dspCallback;
    dspdesc.userdata = (void *)0x12345678;

    _fmodsystem->createDSP( &dspdesc, &_dsp ); 
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
    // channel to get the data.
    _fmodsystem->playSound( _sound, NULL, false, &_channel );
    assert( _channel != NULL );
    _channel->setVolume( 0 );

    _channel->addDSP( 0, _dsp );
    pauseRecording( false );
    _fmodsystem->update();

    // Start fmod updater thread
    // We need to call update every 20 ms to get fmod system status
    _updaterThread.reset( new boost::thread( boost::bind( &SoundRecorder::updater, this ) ) );
}

void SoundRecorder::pauseRecording( const bool paused )
{
    if ( _dsp )
    {
        _dsp->setBypass( paused );
    }
}

/**
 * @brief stop recording
 */
void SoundRecorder::stopRecording()
{
    // Stop silent playback
    if ( _channel )
    {
        if ( _dsp )
        {
            _channel->removeDSP( _dsp );
        }
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

FMOD_RESULT F_CALLBACK dspCallback( FMOD_DSP_STATE *dspState, float *inbuffer, float *outbuffer, unsigned int length, int inchannels, int *outchannels ) 
{
    FMOD::DSP *thisDSP = (FMOD::DSP *)dspState->instance;
    mvpplayer::SoundRecorder* recorder = nullptr;
    thisDSP->getUserData( (void**)( &recorder ) );

    FMOD::Channel & channel = recorder->channel();
    unsigned int position;

    channel.getPosition( &position, FMOD_TIMEUNIT_PCM );

    std::cout << position << std::endl;

    return FMOD_OK;
}

}
