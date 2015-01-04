#include "fileUtils.hpp"
#include <sstream>

namespace mvpplayer
{
namespace gui
{
namespace ncurses
{

boost::filesystem::path openFile( CDKSCREEN* cdkscreen, const std::string & title, const std::string & extensions )
{
    CDKFSELECT *fileSelect = newCDKFselect( cdkscreen,
                                            CENTER,
                                            CENTER,
                                            19,
                                            64,
                                            title.c_str(), "Music file:", A_NORMAL, '_', A_REVERSE,
                                            "</5>", "</48>", "</N>", "</N>",
                                            TRUE,
                                            FALSE );

    const char* filename = activateCDKFselect( fileSelect, NULL );
    std::ostringstream os;
    os << filename;
    destroyCDKFselect( fileSelect );
    refreshCDKScreen( cdkscreen );
    return os.str();
}

}
}
}
