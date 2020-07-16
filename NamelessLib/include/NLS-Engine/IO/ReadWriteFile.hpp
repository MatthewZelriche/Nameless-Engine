#pragma once
/** @file */

#include <iniparser.hpp>
#include <Log.hpp>

namespace NLS::IO {
    /**
    * @brief Use to open a config file via the open-source LeksysINI library. 
    * 
    * @param fileName The name of the config file to open, for example "config.ini"
    * @return The LeksysINI File object to read from or write to, if reading the file was successful. 
    */
    INI::File ReadConfigFile(const char *fileName);
}