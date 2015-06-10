# Boost for the whole mvp-player project

set(Boost_USE_STATIC_LIBS OFF)
add_definitions( -DBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS, -DBOOST_MPL_LIMIT_LIST_SIZE=30 )
find_package(Boost 1.58.0 
    COMPONENTS regex date_time chrono thread serialization system filesystem atomic log program_options timer QUIET)

if (Boost_FOUND) 
  set(MvpPlayerBoost_FOUND 1)
else(Boost_FOUND)
    message("please set BOOST_ROOT environment variable to a proper boost install")
endif(Boost_FOUND)
