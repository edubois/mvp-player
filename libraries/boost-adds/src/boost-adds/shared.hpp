#ifndef _SHARED_HPP_
#define	_SHARED_HPP_

#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif

/** @brief Platform independent export macro.
 *
 * This macro is to be used before any symbol that is to be
 * exported from a plug-in. This is OS/compiler dependent.
 */
#if ( defined( WIN32 ) || defined( WIN64 ) || defined( _WIN32 ) || defined( _WIN64 ) || defined( __WINDOWS__ ) || defined( __TOS_WIN__ ) || defined( __WIN32__ ) )
 #define Export __declspec( dllexport )
 #define Import __declspec( dllimport )
#elif defined( __GNUC__ )     // Add compiler definition here...
 #if __GNUC__ - 0 > 3 || ( __GNUC__ - 0 == 3 && __GNUC_MINOR__ - 0 > 2 )
  #define Export __attribute__ ( ( visibility( "default" ) ) )
  #define Import
 #else
  #define Export
  #define Import
  #warning "Export not set because of a too old gcc version. The plug-in may not compile with the option -fvisible=hidden."
 #endif
#else
 #error "Export not defined for this compiler..."
#endif

#ifdef BOOST_ADDS_STATIC_BUILD
 #define BUILD_DLL
#else
 #ifdef BUILD_DLL
  #define BUILD_DLL Export
 #else
  #define BUILD_DLL Import
 #endif
#endif

#endif
