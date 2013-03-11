#ifndef BINARYPATCHER_H
#define BINARYPATCHER_H

#include "patcher.h"

class BinaryPatcher : public Patcher {
public:
    BinaryPatcher();
    virtual ~BinaryPatcher();

    virtual bool patch() const;
};

#endif // BINARYPATCHER_H
