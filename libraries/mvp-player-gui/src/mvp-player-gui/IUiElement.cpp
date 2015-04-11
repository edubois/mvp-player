#include "IUiElement.hpp"

namespace mvpplayer
{
namespace gui
{

IUiElement::IUiElement( const std::string & name )
: _name( name )
{
}

IUiElement::~IUiElement()
{
}

/**
 * @brief read ui element properties
 * @return *this
 */
IUiElement::This & IUiElement::read( const boost::filesystem::path & filename )
{
    using namespace boost::property_tree::xml_parser;
    read_xml( filename.string(), _properties );
    _name = property<std::string>( "name" );
    return *this;
}

/**
 * @brief save ui element properties
 */
void IUiElement::write( const boost::filesystem::path & filename )
{
    using namespace boost::property_tree::xml_parser;
    setProperty( "name", _name );
    read_xml( filename.string(), _properties );
}

}
}
