#include "IMVPPlayerDialog.hpp"
#include "IUiElement.hpp"

#include <boost/filesystem/operations.hpp>
#include <boost-adds/filesystem/bundle_path.hpp>

namespace mvpplayer
{
namespace gui
{

void IMVPPlayerDialog::readDefaultButtonDescription( const boost::filesystem::path & buttonsDir )
{
    using namespace boost::filesystem;

    directory_iterator end;
    path fullPath = buttonsDir;
#ifdef __APPLE__
    if ( buttonsDir.string()[0] == '.' )
    {
        fullPath = bundle_path() / buttonsDir;
    }
#endif
    for ( directory_iterator pos( fullPath ); pos != end; ++pos )
    {
        if ( is_regular_file( *pos ) )
        {
            path ext = pos->path().filename().extension();
            if ( ext == ".ui" )
            {
                ButtonDescriptor buttonDesc;
                _buttonsBar.appendButton( buttonDesc.read( pos->path() ) );
            }
        }
    }
}

IMVPPlayerDialog::~IMVPPlayerDialog()
{}

}
}
