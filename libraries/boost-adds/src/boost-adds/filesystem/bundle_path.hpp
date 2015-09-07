#ifndef BUNDLE_PATH_HPP
#define	BUNDLE_PATH_HPP

#include <boost/filesystem.hpp>

#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif
namespace boost
{
namespace filesystem
{
// ----------------------------------------------------------------------------
// This makes relative paths work in C++ in Xcode by changing directory to the Resources folder inside the .app bundle
inline boost::filesystem::path bundle_path()
{
#ifdef __APPLE__    
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[4096];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, 1, (UInt8 *)path, 4096))
    {
        return boost::filesystem::current_path();
    }
    CFRelease(resourcesURL);

    chdir(path);
    return std::string( path );
#else
    return boost::filesystem::current_path();
#endif
}
}
}

#endif
