#ifndef _JM_TEST_UNITTEST_HPP_
#define	_JM_TEST_UNITTEST_HPP_

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/exception/diagnostic_information.hpp>

namespace judymatch {
namespace test {

inline void translateBoostException( const boost::exception &e )
{
	BOOST_FAIL( boost::diagnostic_information(e) );
}

class Fixture
{
public:
	Fixture()
	{
		boost::unit_test::unit_test_monitor.register_exception_translator<boost::exception>( &translateBoostException );
	}
	~Fixture()
	{
	}
};

BOOST_GLOBAL_FIXTURE( Fixture )

}
}


namespace judy {
namespace test {

inline void translateBoostException( const boost::exception &e )
{
	BOOST_FAIL( boost::diagnostic_information(e) );
}

class Fixture
{
public:
	Fixture()
	{
		boost::unit_test::unit_test_monitor.register_exception_translator<boost::exception>( &translateBoostException );
	}
	~Fixture()
	{
	}
};

BOOST_GLOBAL_FIXTURE( Fixture )

}
}

#endif
