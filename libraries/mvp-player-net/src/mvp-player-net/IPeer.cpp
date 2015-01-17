#include "IPeer.hpp"
#include <boost/exception/all.hpp>

namespace mvpplayer
{
namespace network
{

IPeer::IPeer( boost::asio::io_service *ioService )
: _ioScopedService( ioService ? nullptr : new boost::asio::io_service() )
, _ioService( ioService ? ioService : _ioScopedService.get() )
, _commandLen( 0 )
, _stop( false )
, _socket( *_ioService )
{
    if ( _ioScopedService )
    {
        _ioThread.reset( new boost::thread( boost::bind( &boost::asio::io_service::run, _ioService ) ) );
    }
}

IPeer::~IPeer()
{}

void IPeer::start()
{
    _stop = false;
    _receivingThread.reset( new boost::thread( boost::bind( &This::handleReceiving, this ) ) );
}

std::string IPeer::address() const
{
    return _socket.remote_endpoint().address().to_string() + ":" + 
           std::to_string( _socket.remote_endpoint().port() );
}

void IPeer::presentation( const PeerInfo & peerInfo )
{
    // Serialize peerInfo
    boost::asio::streambuf buf;
    std::ostream os( &buf );
    boost::archive::text_oarchive ar( os );
    ar << peerInfo;

    send( Data( boost::asio::buffer_cast<const boost::uint8_t*>( buf.data() ), buf.size() ) );
}

void IPeer::handleReceiving()
{
    try
    {
        while( !_stop )
        {
            // Read event
            IEvent *event = nullptr;
            recv( event );
            if ( event )
            {
                signalizeEvent( *event );
            }
        }
    }
    catch( ... )
    {
        std::cerr << ::boost::current_exception_diagnostic_information() << std::endl;
    }
}

void IPeer::readEvent()
{
    _commandLen = 0;
    boost::asio::async_read( _socket, boost::asio::buffer( &_commandLen, sizeof( _commandLen ) ),
        boost::bind( &This::handleEvent, this,
                     boost::asio::placeholders::error,
                     boost::asio::placeholders::bytes_transferred ) );
}

void IPeer::handleEvent( const boost::system::error_code& error, std::size_t nbytes )
{
    if ( !error )
    {
        IEvent *event = nullptr;
        readEvent( event, _commandLen );
        if ( event )
        {
            signalizeEvent( *event );
        }
    }
    _receivingLock.notify_one();
}

void IPeer::disconnect()
{
    _stop = true;

    if ( _ioScopedService )
    {
        _ioScopedService->stop();
    }

    if ( _receivingThread )
    {
        _receivingLock.notify_one();
        _receivingThread.reset( nullptr );
    }

    if ( _socket.is_open() )
    {
        try
        {
            _socket.cancel();
            _socket.shutdown( boost::asio::ip::tcp::socket::shutdown_both );
            _socket.close();
        }
        // Ignore errors
        catch( ... )
        {}
    }
}

boost::system::error_code IPeer::readEvent( IEvent *&event, const boost::uint32_t cmdLen )
{
    boost::system::error_code error;
    // read serialized data
    boost::asio::streambuf buf;
    boost::asio::read( _socket, buf.prepare( cmdLen ), error );
    buf.commit( cmdLen );

    // Unserialize
    std::istream is( &buf );
    IArchive archive( is );
    logic::registerClassInArchive( archive );

    archive >> event;
    return error;
}

boost::system::error_code IPeer::sendEvent( const IEvent * event )
{
    // Serialize event
    boost::asio::streambuf buf;
    std::ostream os( &buf );
    OArchive archive( os );
    logic::registerClassInArchive( archive );

    archive << event;

    return send( Data( boost::asio::buffer_cast<const boost::uint8_t*>( buf.data() ), buf.size() ) );
}

boost::system::error_code IPeer::send(  const Data & data )
{
    boost::system::error_code error;
    // Prepare buffers
    if ( !data.length )
    { return boost::system::errc::make_error_code( boost::system::errc::message_size ); }

    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back( boost::asio::buffer( &data.length, sizeof( data.length ) ) );
    buffers.push_back( boost::asio::buffer( &data.buffer[0], data.length ) );

    boost::asio::write( _socket, buffers, boost::asio::transfer_all(), error );

    // If there was an error, shutdown the connection
    if ( error || !_socket.is_open() )
    { _stop = true; }

    return error;
}

void IPeer::receivePeerInfo()
{
    recv( _peerInfo );
}

}
}
