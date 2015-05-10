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
    Settings( const boost::property_tree::ptree & settings );
    Settings( const boost::filesystem::path & settingsFilename = kDefaultSettingsFilename );
    virtual ~Settings() {}
    
    
    /**
     * @brief clear settings
     */
    inline void clear()
    { _settings.clear(); }

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
     * @brief append a sub property tree
     * @param group the group
     * @param key the setting key
     * @param value the sub property tree
     */
    void set( const std::string & group, const std::string & key, const boost::property_tree::ptree & subtree, const char separator = '.' )
    {
        typedef boost::property_tree::ptree::path_type PathT;
        std::string path;
        path += group;
        if ( !group.empty() )
        {
            path += separator;
        }
        path += key;
        _settings.add_child( PathT( path, separator ), subtree );
    }

    /**
     * @brief set property
     * @param group the group
     * @param key the setting key
     * @param value the setting value
     */
    template<class T>
    void set( const std::string & group, const std::string & key, const T & value, const char separator = '.' )
    {
        try
        {
            typedef boost::property_tree::ptree::path_type PathT;
            std::string path;
            path += group;
            if ( !group.empty() )
            {
                path += separator;
            }
            path += key;
            _settings.put( PathT( path, separator ), boost::lexical_cast<std::string>( value ) );
        }
        catch( ... )
        {
            std::cerr << boost::current_exception_diagnostic_information() << std::endl;
            std::cerr << "Unable to set setting: " << key << std::endl;
        }
    }

    inline bool has( const std::string & group, const std::string & key, const char separator = '.' ) const
    {
        typedef boost::property_tree::ptree::path_type PathT;
        std::string path;
        path += group;
        if ( !group.empty() )
        {
            path += separator;
        }
        path += key;
        return _settings.get_optional<std::string>( PathT( path, separator ) ) != boost::none;
    }

    template<class T>
    T get( const std::string & group, const std::string & key, const char separator = '.' )
    {
        try
        {
            typedef boost::property_tree::ptree::path_type PathT;
            std::string path;
            path += group;
            if ( !group.empty() )
            {
                path += separator;
            }
            path += key;
            return boost::lexical_cast<T>( _settings.get<std::string>( PathT( path, separator ) ) );
        }
        catch( ... )
        {
            std::cerr << boost::current_exception_diagnostic_information() << std::endl;
            std::cerr << "Unable to get setting: " << key << std::endl;
        }
        return T();
    }
    
    const boost::property_tree::ptree & tree() const
    { return _settings; }
    
private:
    boost::property_tree::ptree _settings;  ///< Property tree for the settings
};

}

#endif
