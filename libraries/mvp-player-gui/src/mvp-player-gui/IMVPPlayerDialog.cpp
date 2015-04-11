#include "IMVPPlayerDialog.hpp"
#include "IUiElement.hpp"

#include <boost/filesystem/operations.hpp>

namespace mvpplayer
{
namespace gui
{

void IMVPPlayerDialog::readDefaultButtonDescription( const boost::filesystem::path & buttonsDir )
{
    using namespace boost::filesystem;

    directory_iterator end;
    for ( directory_iterator pos( buttonsDir ); pos != end; ++pos )
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
