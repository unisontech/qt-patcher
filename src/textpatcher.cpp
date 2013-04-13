#include "textpatcher.h"

#include <fstream>
#include <algorithm>
#include <stdexcept>

TextPatcher::TextPatcher()
{
}

TextPatcher::~TextPatcher()
{
}

void TextPatcher::patch(const std::string& newPathQt, const std::string& fileName) const
{
    newPathQt.empty();
    fileName.empty();

    string_utils::strings strings = readStringsFromFile(fileName);

    string_utils::strings::iterator end = strings.end();
    for(string_utils::strings::iterator it = strings.begin(); it != end; ++it) {
        string_utils::strings parts = string_utils::split(*it, "=");
        if (parts.size() == 2) {
            if (isQtMkSpecDefinition(parts.front(), parts.back())) {
                *it = parts.front() + "=" + newPathQt + "/mkspecs" + string_utils::split(parts.back(), "mkspecs").at(1);
            } else if (isQtFilesTreeDefinition(parts.front())) {
                *it = parts.front() + "=" + newPathQt;
            }
        }
    }
    writeStringsToFile(fileName, strings);
}

string_utils::strings TextPatcher::readStringsFromFile(const std::string &fileName) const
{
    std::ifstream file(fileName.c_str(), std::ios::in | std::ios::ate);
    if (!file.is_open())
        throw std::runtime_error(string_utils::format("Coundn't open file for reading: %s", fileName.c_str()));

    string_utils::strings fileData;

    file.seekg(0, std::ios::beg);
    while( !file.eof() ) {
        std::string line;
        if (std::getline(file, line).bad())
            throw std::runtime_error(string_utils::format("Failed to read from file: %s", fileName.c_str()));
        fileData.push_back(line);
    }

    return fileData;
}

bool TextPatcher::isQtMkSpecDefinition(const std::string& firstPart, const std::string& secondPart) const
{
    std::string trimmedFirstPart = string_utils::trim(firstPart);
    return string_utils::contains(secondPart, "mkspecs")
            &&
            (
                trimmedFirstPart == "QMAKESPEC_ORIGINAL"
                ||
                trimmedFirstPart == "QMAKESPEC"
                );
}

bool TextPatcher::isQtFilesTreeDefinition(const std::string& firstPart) const
{
    std::string trimmedFirstPart = string_utils::trim(firstPart);
    return  trimmedFirstPart == "QT_BUILD_TREE"
            ||
            trimmedFirstPart == "QT_SOURCE_TREE";
}

void TextPatcher::writeStringsToFile(const std::string& fileName, const string_utils::strings& strings) const
{
    std::ofstream file(fileName.c_str(), std::ios::out | std::ios::trunc);
    if (!file.is_open())
        throw std::runtime_error(string_utils::format("Coundn't open file for reading: %s", fileName.c_str()));

    file.seekp(0, std::ios::beg);
    for ( string_utils::strings::const_iterator it = strings.begin(); it != strings.end(); ++it ) {
        std::string line = *it;
        if (it + 1 != strings.end()) {
            // true for all but last line in strings list
            line += '\n';
        }

        if (!file.write(line.c_str(), line.size()))
            throw std::runtime_error(string_utils::format("Failed to write to file: %s", fileName.c_str()));
    }
}
