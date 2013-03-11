#ifndef PATCHER_H
#define PATCHER_H

class Patcher {
public:
    virtual ~Patcher() {}

    virtual bool patch() const = 0;
};

#endif // PATCHER_H
