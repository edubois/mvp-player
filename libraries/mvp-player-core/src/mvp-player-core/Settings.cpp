#include "Settings.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include <queue>

namespace mvpplayer
{

Settings::Settings( const boost::property_tree::ptree & settings )
: _settings( settings )
{
}

Settings::Settings( const boost::filesystem::path & settingsFilename )
{
    if ( !settingsFilename.empty() )
    {
        read( settingsFilename );
    }
}

bool Settings::read( const boost::filesystem::path & settingsFilename )
{
    try
    {
        if ( boost::algorithm::icontains( settingsFilename.string(), ".xml" ) )
        {
            using namespace boost::property_tree::xml_parser;
            read_xml( settingsFilename.string(), _settings );
            return true;
        }
        else if ( boost::algorithm::icontains( settingsFilename.string(), ".ini" ) )
        {
            using namespace boost::property_tree::ini_parser;
            read_ini( settingsFilename.string(), _settings );
            return true;
        }
        // JSON by default
        else
        {
            using namespace boost::property_tree::json_parser;
            read_json( settingsFilename.string(), _settings );
            return true;
        }
    }
    catch( ... )
    {}
    return false;
}

bool Settings::write( const boost::filesystem::path & settingsFilename ) const
{
    try
    {
        if ( boost::algorithm::icontains( settingsFilename.string(), ".xml" ) )
        {
            using namespace boost::property_tree::xml_parser;
            write_xml( settingsFilename.string(), _settings );
            return true;
        }
        else if ( boost::algorithm::icontains( settingsFilename.string(), ".ini" ) )
        {
            using namespace boost::property_tree::ini_parser;
            write_ini( settingsFilename.string(), _settings );
            return true;
        }
        // JSON by default
        else
        {
            using namespace boost::property_tree::json_parser;
            write_json( settingsFilename.string(), _settings );
            return true;
        }
    }
    catch( ... )
    {
    }
    return false;
}

/**
 * @brief merge settings from another settings object
 * @param other other settings object
 */
void Settings::merge( const Settings & other )
{
    using namespace std;

    // Keep track of keys and values (subtrees) in second property tree
    queue<string> qKeys;
    queue<boost::property_tree::ptree> qValues;
    qValues.push( other._settings );

    // Iterate over second property tree
    while( !qValues.empty() )
    {
        typedef boost::property_tree::ptree::path_type PathT;
        // Setup keys and corresponding values
        boost::property_tree::ptree ptree = qValues.front();
        qValues.pop();
        string keychain = "";
        if( !qKeys.empty() )
        {
            keychain = qKeys.front();
            qKeys.pop();
        }

        // Separator needs to be a impossible char
        const char separator = '\1';

        // Iterate over keys level-wise
        for( const auto & child: ptree )
        {
            // Leaf
            if( child.second.size() == 0 )
            {
                // No "." for first level entries
                string s;
                if( keychain != "" )
                    s = keychain + separator + child.first.data();
                else
                    s = child.first.data();

                // Put into combined property tree
                _settings.put( PathT( s, separator ), child.second.data() );
            }
            // Subtree
            else
            {
                // Put keys (identifiers of subtrees) and all of its parents (where present)
                // aside for later iteration. Keys on first level have no parents
                if( keychain != "" )
                    qKeys.push( keychain + separator + child.first.data() );
                else
                    qKeys.push( child.first.data() );

                // Put values (the subtrees) aside, too
                qValues.push( child.second );
            }
        }
    }
}

}
