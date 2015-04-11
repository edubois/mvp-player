#ifndef _GUI_IUIELEMENT_HPP_
#define	_GUI_IUIELEMENT_HPP_

#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace mvpplayer
{
namespace gui
{

/**
 * @brief class for user interface elements
 */
class IUiElement
{
private:
    typedef IUiElement This;
public:
    IUiElement( const std::string & name = std::string() );
    virtual ~IUiElement();

    /**
     * @brief return the name of the ui element
     */
    inline const std::string & name() const
    { return _name; }
    
    /**
     * @brief read ui element properties
     * @return *this
     */
    This & read( const boost::filesystem::path & filename );
    
    /**
     * @brief save ui element properties
     */
    void write( const boost::filesystem::path & filename );

    /**
     * @brief set a property
     * @param propName property's name
     * @param value property's value
     */
    template<class T>
    void setProperty( const std::string & propName, T & value )
    { _properties.put( std::string( "uielement." ) + propName, value ); }

    /**
     * @brief get property value
     */
    template<class T>
    T property( const std::string & propName ) const
    {
        try {
            return _properties.get<T>( std::string( "uielement." ) + propName );
        }
        catch( ... )
        {
            return T();
        }
    }

private:
    std::string _name;
    boost::property_tree::basic_ptree<std::string, std::string> _properties;
};

}
}

#endif
