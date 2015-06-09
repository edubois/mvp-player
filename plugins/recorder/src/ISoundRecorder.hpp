#ifndef _PLUG_ISOUNDRECORDER_HPP_
#define	_PLUG_ISOUNDRECORDER_HPP_

#include <boost/filesystem/path.hpp>
#include <boost/signals2/signal.hpp>
#include <string>
#include <chrono>

namespace mvpplayer
{

static const int kLatencyVolumeHighThreshold( 100 );

class ISoundRecorder : public boost::signals2::trackable
{
public:
    ISoundRecorder();
    virtual ~ISoundRecorder() = 0;

    void setChannels( const std::size_t channels )
    { _channels = channels; }

    void setBitDepth( const std::size_t bitDepth )
    { _bitDepth = bitDepth; }

    void setSampleRate( const std::size_t sampleRate )
    { _sampleRate = sampleRate; }

    void setFilename( const boost::filesystem::path & filename )
    { _filename = filename; }

    /**
     * @brief return bit depth (ex. 16)
     * @return bit depth in bits
     */
    std::size_t bitDepth() const
    { return _bitDepth; }

    /**
     * @brief return number of channels (ex. 2)
     * @return number of channels
     */
    std::size_t channels() const
    { return _channels; }

    /**
     * @brief return sample rate (ex. 44100)
     * @return sample rate in hz
     */
    std::size_t sampleRate() const
    { return _sampleRate; }

    /**
     * @brief signalize that the volume has been over a threshold
     * @return the threshold value
     */
    inline float thresholdVolumeHigh() const
    { return _thresholdVolumeHigh; }

    /**
     * @brief return filename
     * @return file name
     */
    inline const boost::filesystem::path & filename() const
    { return _filename; }
    
    virtual void initialize() = 0;

    /**
     * @brief start recording
     * @warning setChannels, setSampleRate, setBitDepth, setFilename must have been called
     */
    virtual void startRecording() = 0;

    /**
     * @brief stop recording
     */
    virtual void stopRecording() = 0;

    /**
     * @brief stop recording
     * @param volume captured sample
     */
    void signalizeVolumeHigh( const float volume );
    
public:
    boost::signals2::signal<void(const float volume)> signalVolumeHigh; ///< signalize that the volume has been over a threshold

protected:
    std::chrono::system_clock::time_point _lastVolumeHighTime;
    float _thresholdVolumeHigh;     ///< Threshold value for signalizing volume high
    double _sampleDuration;         ///< Duration in second of the capture window
    std::size_t _channels;          ///< Number of channels
    std::size_t _bitDepth;          ///< Bit depth
    std::size_t _sampleRate;        ///< Number of samples per seconds
    boost::filesystem::path _filename;  ///< Output filename
};

}

#endif
