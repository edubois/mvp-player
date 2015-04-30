#ifndef _MVPPLAYER_ICLIENT_HPP_
#define	_MVPPLAYER_ICLIENT_HPP_

#include <mvp-player-core/stateMachineEvents.hpp>

#include <mvp-player-net/Data.hpp>
#include <mvp-player-net/PeerInfo.hpp>
#include <mvp-player-core/IEvent.hpp>

#include <boost/asio.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/signals2.hpp>

namespace mvpplayer
{
namespace network
{

/**
 * @brief mvp_player network client instance
 */
class IPeer : public boost::signals2::trackable
{
private:
    typedef boost::archive::text_iarchive IArchive;
    typedef boost::archive::text_oarchive OArchive;
    typedef IPeer This;
public:
    IPeer( boost::asio::io_service *ioService = nullptr );
    virtual ~IPeer();

    inline boost::asio::ip::tcp::socket & socket()
    { return _socket; }

    std::string address() const;

    inline const PeerInfo & peerInfo() const
    { return _peerInfo; }

    void disconnect();
    void start();

    void receivePeerInfo();
    void presentation( const PeerInfo & peerInfo );

    boost::system::error_code sendEvent( const IEvent * event );

private:
    template<class T>
    boost::system::error_code recv( T & data );
    boost::system::error_code readEvent( IEvent *&event, const boost::uint32_t cmdLen );
    boost::system::error_code send( const Data & data );
    void handleReceiving();

public:
//- signals
    boost::signals2::signal<void( IEvent& )> signalEvent;

private:
    std::unique_ptr<boost::asio::io_service> _ioScopedService; ///< Boost asio IO service
    boost::asio::io_service *_ioService;                ///< Boost asio IO service
    std::size_t _commandLen;                            ///< Command length
    bool _stop;                                         ///< Stop receiver thread
    mutable boost::mutex _receiverMutex;                ///< Mutex for read data waiter
    boost::asio::ip::tcp::socket _socket;               ///< Socket for the connection
    boost::scoped_ptr<boost::thread> _receivingThread;  ///< Thread for receiver loop
    boost::scoped_ptr<boost::thread> _ioThread;         ///< Service IO thread
    PeerInfo _peerInfo;                                 ///< Peer informations
};

template<class T>
boost::system::error_code IPeer::recv( T & data )
{
    boost::system::error_code error;
    // read data length
    boost::uint32_t dataLen = 0;
    boost::asio::read( _socket,
                        boost::asio::buffer( &dataLen, sizeof( dataLen ) ),
                        error
                     );

    if ( dataLen )
    {
        // read serialized data
        boost::asio::streambuf buf;
        boost::asio::read( _socket,
                           buf.prepare( dataLen ),
                           error
                         );
        buf.commit( dataLen );

        // Unserialize
        std::istream is( &buf );
        boost::archive::text_iarchive archive( is );
        logic::registerClassInArchive( archive );
        archive >> data;
    }
    return error;
}

}
}

#endif
