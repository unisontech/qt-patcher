#include "arguments.h"
#include <sstream>
#include <algorithm>

Arguments::Arguments()
    : _rawArguments()
{
}

Arguments::Arguments(int &argc, char *argv[])
    : _rawArguments(parseArguments(argc, argv))
{
}

Arguments::~Arguments()
{
}

const Arguments::ArgsList &Arguments::list() const
{
    return _rawArguments;
}

bool Arguments::containsKey(char shortKey, const char *longKey) const
{
    return containsKey(shortKey) || containsLongKey(longKey);
}

bool Arguments::containsKey(char key) const
{
    std::stringstream searchedKey;
    searchedKey << "-" << key;
    return contains(searchedKey.str());
}

bool Arguments::containsLongKey(const char *longKey) const
{
    if (longKey == 0)
        return false;

    std::stringstream searchedKey;
    searchedKey << "--" << longKey;
    return contains(searchedKey.str());
}

bool Arguments::contains(const char *value) const
{
    if (value == 0)
        return false;
    return contains(std::string(value));
}

bool Arguments::contains(const std::string &value) const
{
    if (value.empty())
        return false;

    ArgsList::const_iterator it = std::find(_rawArguments.begin(), _rawArguments.end(), value);
    return it != _rawArguments.end();
}

Arguments::ArgsList Arguments::parseArguments(int &argc, char *argv[]) const
{
    ArgsList result;
    for(int i = 0; i < argc; ++i) {
        result.push_back( argv[i] );
    }
    return result;
}

bool Arguments::isKey(const std::string &value) const
{
    return value.at(0) == '-';
}

bool Arguments::isLongKey(const std::string &value) const
{
    return value.at(0) == '-' && value.at(1) == '-';
}



