#ifndef TEXTPATCHER_H
#define TEXTPATCHER_H

#include "patcher.h"

class TextPatcher : public Patcher {
public:
    TextPatcher();
    virtual ~TextPatcher();

    virtual bool patch() const;
};

#endif // TEXTPATCHER_H
