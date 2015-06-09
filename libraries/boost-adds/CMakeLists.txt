cmake_minimum_required(VERSION 2.8) 

project(BoostAdds CXX)

# Set sequenceParser versions
set(BOOST_ADDS_VERSION_MAJOR "1")
set(BOOST_ADDS_VERSION_MINOR "0")
set(BOOST_ADDS_VERSION_MICRO "0")
set(BOOST_ADDS_VERSION ${BOOST_ADDS_VERSION_MAJOR}.${BOOST_ADDS_VERSION_MINOR}.${BOOST_ADDS_VERSION_MICRO})

# Define sequenceParser versions
add_definitions(-DBOOST_ADDS_VERSION_MAJOR=${BOOST_ADDS_VERSION_MAJOR})
add_definitions(-DBOOST_ADDS_VERSION_MINOR=${BOOST_ADDS_VERSION_MINOR})
add_definitions(-DBOOST_ADDS_VERSION_MICRO=${BOOST_ADDS_VERSION_MICRO})
add_definitions( -DBOOST_ADDS_STATIC_BUILD )

include(UseMvpPlayerBoost)

if ( MvpPlayerBoost_FOUND )
    # Diplay commands being ran by CMake
    set(CMAKE_VERBOSE_MAKEFILE OFF)

    # The install rule does not depend on all, i.e. everything will not be built before installing
    set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY TRUE)

    # CPP flags on debug / release mode
    if(MSVC)
            set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
            set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    else()
            set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -fPIC -pg -g")
            set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fPIC -O3")
    endif()

    add_subdirectory(src)
else()
   message("Unable to find libs dependency, aborting compilation of boost-adds")
endif()
