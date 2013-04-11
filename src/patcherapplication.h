#ifndef PATCHERAPPLICATION_H
#define PATCHERAPPLICATION_H

#include "arguments.h"

class PatcherApplication {
public:
    enum Error {
        Ok = 0,
        // --- arguments
        InvalidArguments = 1,

        // --- pre-patching errors
        ExecutablesNotFound = 11,
        LibrariesNotFound = 12,
        MKSpecsNotFound = 13,

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

    std::vector<std::string> createLibraryNamesList(const char* baseLibraryName) const;

    std::vector<std::string> executablesToPatch(const std::string& pathToQt) const;
    std::vector<std::string> librariesToPatch(const std::string& pathToQt) const;
    std::vector<std::string> mkspecsToPatch(const std::string& pathToQt) const;


    std::vector<std::string> existingFiles(const std::vector<std::string>& files) const;

    void printHelp();
    void printVersion();


    // -- members
    Arguments args;
    std::string applicationName;
    std::string applicationVersion;

};

#endif // PATCHERAPPLICATION_H
