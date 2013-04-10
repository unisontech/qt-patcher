#ifndef TEXTPATCHER_H
#define TEXTPATCHER_H

#include "patcher.h"

class TextPatcher : public Patcher {
public:
    TextPatcher();
    virtual ~TextPatcher();

    virtual void patch(const std::string &newPathQt, const std::string &fileName) const;
};

#endif // TEXTPATCHER_H
