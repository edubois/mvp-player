#ifndef _MVPPLAYER_CORE_SETTINGS_HPP_
#define	_MVPPLAYER_CORE_SETTINGS_HPP_

#include "Singleton.hpp"

#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include <iostream>

namespace mvpplayer
{

static const std::string kDefaultSettingsFilename( ".mvpPlayerSettings.json" );

class Settings : public Singleton<Settings>
{
public:
    Settings( const boost::filesystem::path & settingsFilename = kDefaultSettingsFilename );
    virtual ~Settings() {}
    
    /**
     * Read settings from a file
     * @param settingsFilename the file name
     */
    bool read( const boost::filesystem::path & settingsFilename );

    /**
     * Write settings to a file
     * @param settingsFilename the file name
     */
    bool write( const boost::filesystem::path & settingsFilename = kDefaultSettingsFilename ) const;
    
    /**
     * @brief merge settings from another settings object
     * @param other other settings object
     */
    void merge( const Settings & other );

    /**
     * @brief set property
     * @param group the group
     * @param key the setting key
     * @param value the setting value
     */
    template<class T>
    void set( const std::string & group, const std::string & key, const T & value )
    {
        try
        {
            std::string path = "settings.";
            path += group;
            if ( !group.empty() )
            {
                path += ".";
            }
            path += key;
            _settings.put( path, boost::lexical_cast<std::string>( value ) );
        }
        catch( ... )
        {
            std::cerr << boost::current_exception_diagnostic_information() << std::endl;
            std::cerr << "Unable to set setting: " << key << std::endl;
        }
    }
    
    inline bool has( const std::string & group, const std::string & key ) const
    {
        std::string path = "settings.";
        path += group;
        if ( !group.empty() )
        {
            path += ".";
        }
        path += key;
        return _settings.get_optional<std::string>( path ) != boost::none;
    }

    template<class T>
    T get( const std::string & group, const std::string & key )
    {
        try
        {
            std::string path = "settings.";
            path += group;
            if ( !group.empty() )
            {
                path += ".";
            }
            path += key;
            return boost::lexical_cast<T>( _settings.get<std::string>( path ) );
        }
        catch( ... )
        {
            std::cerr << boost::current_exception_diagnostic_information() << std::endl;
            std::cerr << "Unable to get setting: " << key << std::endl;
        }
        return T();
    }
    
private:
    boost::property_tree::ptree _settings;  ///< Property tree for the settings
};

}

#endif
