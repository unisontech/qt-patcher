#ifndef TEXTPATCHER_H
#define TEXTPATCHER_H

#include "patcher.h"
#include "utils/stringutils.h"
#include <vector>

class TextPatcher : public Patcher {
public:
    TextPatcher();
    virtual ~TextPatcher();

    virtual void patch(const std::string &newPathQt, const std::string &fileName) const;

private:
    string_utils::strings readStringsFromFile(const std::string& fileName) const;
    bool isQtMkSpecDefinition(const std::string& firstPart, const std::string& secondPart) const;
    bool isQtFilesTreeDefinition(const std::string& firstPart) const;
    void writeStringsToFile(const std::string& fileName, const string_utils::strings& strings) const;
};

#endif // TEXTPATCHER_H
