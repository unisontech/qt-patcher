#include "binarypatcher.h"

#include <fstream>
#include <algorithm>
#include <stdexcept>

#include "utils/stringutils.h"

BinaryPatcher::BinaryPatcher()
{
}

BinaryPatcher::~BinaryPatcher()
{
}

void BinaryPatcher::patch(const std::string &newPathToQt,const std::string& fileName) const
{
    ByteArray fileData = readFileData(fileName);
    PatchedPaths patchedPaths = getPatchedPaths();
    for (PatchedPaths::iterator it = patchedPaths.begin(); it != patchedPaths.end(); ++it) {
        fileData = changePath(fileData, it->first, newPathToQt + it->second);
    }
    saveDataToFile(fileName, fileData);
}

BinaryPatcher::PatchedPaths BinaryPatcher::getPatchedPaths() const
{
    PatchedPaths paths;
    paths.push_back(PatchedPath("qt_prfxpath", ""));
    paths.push_back(PatchedPath("qt_docspath", "/doc"));
    paths.push_back(PatchedPath("qt_hdrspath", "/include"));
    paths.push_back(PatchedPath("qt_libspath", "/lib"));
    paths.push_back(PatchedPath("qt_binspath", "/bin"));
    paths.push_back(PatchedPath("qt_plugpath", "/plugins"));
    paths.push_back(PatchedPath("qt_datapath", ""));
    paths.push_back(PatchedPath("qt_trnspath", "/translations"));
    paths.push_back(PatchedPath("qt_xmplpath", "/examples"));
    paths.push_back(PatchedPath("qt_demopath", "/demos"));

    // TODO: for payed Qt versions only:
    // need to patch License?
    /*
    changePath(tmp,"qt_lcnsuser=", "$LICENSE_USER")
    changePath(tmp,"qt_lcnsprod=", "$LICENSE_PRODUCT")
    */

    return paths;
}

BinaryPatcher::ByteArray BinaryPatcher::readFileData(const std::string &fileName) const
{
    std::ifstream file(fileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
    if (!file.is_open())
        throw std::runtime_error(string_utils::format("Coundn't open file for reading: %s", fileName.c_str()));

    std::ifstream::pos_type fileSize = file.tellg();
    //ByteArray fileData('\0', fileSize);
    ByteArray fileData(static_cast<unsigned int>(fileSize), '\0');

    file.seekg(0, std::ios::beg);
    if( !file.read(&fileData[0], fileSize) )
        throw std::runtime_error(string_utils::format("Failed to read from file: %s", fileName.c_str()));

    return fileData;
}

BinaryPatcher::ByteArray BinaryPatcher::changePath
    (
        BinaryPatcher::ByteArray data,
        const std::string& pathName,
        const std::string& pathValue
    ) const
{
    std::string newValue = pathName + '=' + pathValue + '\0';
    std::string needle = pathName + '=';
    ByteArray::iterator end = data.end();

    ByteArray::iterator it = std::search(
                data.begin(),
                end,
                needle.begin(),
                needle.end()
                );

    while(it != end) {
        std::copy(newValue.begin(), newValue.end(), it);
        ++it;
        it = std::search(
                    it + 1,
                    end,
                    needle.begin(),
                    needle.end());
    }

    return data;
}

void BinaryPatcher::saveDataToFile(
        const std::string &fileName,
        const BinaryPatcher::ByteArray &data) const
{
    std::ofstream file(fileName.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
    if (!file.is_open())
        throw std::runtime_error(string_utils::format("Coundn't open file for writing: %s", fileName.c_str()));

    file.seekp(0, std::ios::beg);
    if (!file.write(&data[0], data.size()))
        throw std::runtime_error(string_utils::format("Coundn't write to file: %s", fileName.c_str()));
}
