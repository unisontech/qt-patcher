#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <vector>
#include <string>

class Arguments {
public:
    typedef std::vector<std::string> ArgsList;

    explicit Arguments();
    explicit Arguments(int &argc, char *argv[]);
    ~Arguments();

    const ArgsList& list() const;

    std::string calledBinaryName() const;

    bool containsKey(char shortKey, const char* longKey) const;
    bool containsKey(char key) const;
    bool containsLongKey(const char* longKey) const;
    bool contains(const char* value) const;
    bool contains(const std::string& value) const;

private:
    ArgsList parseArguments(int& argc, char* argv[]) const;
    bool isKey(const std::string& value) const;
    bool isLongKey(const std::string& value) const;


    ArgsList _rawArguments;
};

#endif //ARGUMENTS_H
