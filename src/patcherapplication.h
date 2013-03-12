#ifndef PATCHERAPPLICATION_H
#define PATCHERAPPLICATION_H

#include "arguments.h"

class PatcherApplication {
public:
    enum Error {
        Ok = 0,
        // --- arguments
        InvalidArguments = 1,

        // --- patching errors


        // --- windows specific
        TooLongPathToQt = 1000
    };

    PatcherApplication(int& argc, char *argv[]);
    ~PatcherApplication();

    int run();

private:
    bool isArgumentsValid(Arguments args) const;
    Error checkPathToQt(const std::string& pathToQt) const;
    Error patchQtInDir(const std::string& pathToQt) const;

    void printErrorMessage(const std::string &pathToQt, Error error);

    void printHelp();
    void printVersion();


    // -- members
    Arguments args;
    std::string applicationName;
    std::string applicationVersion;

};

#endif // PATCHERAPPLICATION_H
