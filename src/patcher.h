#ifndef PATCHER_H
#define PATCHER_H

#include <string>

class Patcher {
public:
    virtual ~Patcher() {}

    virtual void patch(const std::string &newPathToQt, const std::string &fileName) const = 0;
};

#endif // PATCHER_H
