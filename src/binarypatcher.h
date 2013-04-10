#ifndef BINARYPATCHER_H
#define BINARYPATCHER_H

#include "patcher.h"
#include <vector>

class BinaryPatcher : public Patcher {
    // TODO: change to std::array if it will be possible to use C++11 on all platforms
    typedef std::vector<char> ByteArray;
    typedef std::pair<std::string, std::string> PatchedPath;
    typedef std::vector<PatchedPath> PatchedPaths;
public:
    BinaryPatcher();
    virtual ~BinaryPatcher();

    virtual void patch(const std::string &newPathToQt, const std::string &fileName) const;

private:
    PatchedPaths getPatchedPaths() const;

    ByteArray readFileData(const std::string& fileName) const;

    ByteArray changePath(ByteArray data,
                         const std::string& pathName,
                         const std::string& pathValue) const;

    void saveDataToFile(const std::string& fileName, const ByteArray& data) const;
};

#endif // BINARYPATCHER_H
