#ifndef _PLUG_ISOUNDRECORDER_HPP_
#define	_PLUG_ISOUNDRECORDER_HPP_

#include <boost/filesystem/path.hpp>
#include <string>

namespace mvpplayer
{

class ISoundRecorder
{
public:
    ISoundRecorder(): _sampleDuration( 0 ), _bitDepth( 0 ), _sampleRate( 0 )
    {}
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
     * @brief start recording
     * @warning setChannels, setSampleRate, setBitDepth, setFilename must have been called
     */
    virtual void startRecording() = 0;

    /**
     * @brief stop recording
     */
    virtual void stopRecording() = 0;

protected:
    std::size_t _sampleDuration;        ///< Duration in second of the capture window
    std::size_t _channels;
    std::size_t _bitDepth;
    std::size_t _sampleRate;
    boost::filesystem::path _filename;
};

}

#endif
