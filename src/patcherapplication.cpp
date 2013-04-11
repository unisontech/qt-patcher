#include "patcherapplication.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include "patcher.h"
#include "binarypatcher.h"
#include "textpatcher.h"
#include "utils/stringutils.h"
#include "utils/fileutils.h"

PatcherApplication::PatcherApplication(int& argc, char *argv[])
    : args(argc, argv)
    , applicationName("qt-patcher")
    , applicationVersion("0.1")
{
}

PatcherApplication::~PatcherApplication()
{
}

int PatcherApplication::run()
{
    if (args.containsKey('h', "help")) {
        printHelp();
        return Ok;
    }

    if (args.containsKey('v', "version")) {
        printVersion();
        return Ok;
    }

    if ( !isArgumentsValid(args) ) {
        printErrorMessage("", InvalidArguments);
        return InvalidArguments;
    }

    // --- main workflow
    std::string pathToQt = args.list().at(1);
    Error error = patchQtInDir(pathToQt);
    if (error != Ok) {
        printErrorMessage(pathToQt, error);
        return error;
    }

    return Ok;
}

bool PatcherApplication::isArgumentsValid(Arguments args) const
{
    if ( args.list().size() != 2 )
        return false;
    if ( args.list().at(1).empty() )
        return false;
    if ( !file_utils::isDirectory(args.list().at(1)) )
        return false;

    return true;
}
PatcherApplication::Error PatcherApplication::patchQtInDir(const std::string& pathToQt) const
{
    string_utils::strings executables = executablesToPatch(pathToQt);
    if (executables.empty())
        return ExecutablesNotFound;

    string_utils::strings libraries = librariesToPatch(pathToQt);
    if (libraries.empty())
        return LibrariesNotFound;

    string_utils::strings mkspecs = mkspecsToPatch(pathToQt);
    if (mkspecs.empty())
        return MKSpecsNotFound;

    std::cout << "Will patch following files:" << std::endl;
    for(string_utils::strings::iterator it = executables.begin(); it != executables.end(); ++ it) {
        std::cout << *it << std::endl;
    }
    for(string_utils::strings::iterator it = libraries.begin(); it != libraries.end(); ++ it) {
        std::cout << *it << std::endl;
    }
    for(string_utils::strings::iterator it = mkspecs.begin(); it != mkspecs.end(); ++ it) {
        std::cout << *it << std::endl;
    }

    return Ok;
}

void PatcherApplication::printErrorMessage(const std::string& pathToQt, PatcherApplication::Error error)
{
    switch(error) {
    case Ok:
        return;
    case InvalidArguments:
        printHelp();
        return;
    case ExecutablesNotFound:
        std::cout << "Error: Failed to find Qt executables in dir [" << pathToQt << "]." << std::endl;
        return;
    case LibrariesNotFound:
        std::cout << "Error: Failed to find Qt libraries in dir [" << pathToQt << "]." << std::endl;
        return;
    case MKSpecsNotFound:
        std::cout << "Error: Failed to find Qt mkspec files in dir [" << pathToQt << "]." << std::endl;
        return;
    case TooLongPathToQt:
        std::cout << "Warning: Path [ " << pathToQt << " ] is too long. Patcher will most likely fail to read files." << std::endl;
        return;
    default:
        std::cout << "Error: unknown internal error." << std::endl;
        return;
    }
}

std::vector<std::string> PatcherApplication::createLibraryNamesList(const char *baseLibraryName) const
{
    std::vector<std::string> result;
    if (baseLibraryName == 0)
        return result;

    // on Windows every library is called dll and lib
    // release
    result.push_back(string_utils::format("%s.%s", baseLibraryName, "dll"));
    result.push_back(string_utils::format("%s.%s", baseLibraryName, "lib"));
    // debug
    result.push_back(string_utils::format("%sd.%s", baseLibraryName, "dll"));
    result.push_back(string_utils::format("%sd.%s", baseLibraryName, "lib"));

    // on *unix they are called *.so, *.a, *.la or *.dylib
    result.push_back(string_utils::format("lib%s.%s", baseLibraryName, "so"));
    result.push_back(string_utils::format("lib%sd.%s", baseLibraryName, "so"));

    result.push_back(string_utils::format("lib%s.%s", baseLibraryName, "a"));
    result.push_back(string_utils::format("lib%sd.%s", baseLibraryName, "a"));

    result.push_back(string_utils::format("lib%s.%s", baseLibraryName, "la"));
    result.push_back(string_utils::format("lib%sd.%s", baseLibraryName, "la"));

    result.push_back(string_utils::format("lib%s.%s", baseLibraryName, "dylib"));
    result.push_back(string_utils::format("lib%sd.%s", baseLibraryName, "dylib"));

    return result;
}

std::vector<std::string> PatcherApplication::executablesToPatch(const std::string &pathToQt) const
{
    const char* executablesDir = "bin";
    string_utils::strings executablesToPatch;
    executablesToPatch.push_back(pathToQt + '/' + executablesDir + '/' + "qmake");
    executablesToPatch.push_back(pathToQt + '/' + executablesDir + '/' + "qmake.exe");

    return existingFiles(executablesToPatch);
}

std::vector<std::string> PatcherApplication::librariesToPatch(const std::string &pathToQt) const
{
    const char* librariesDir = "lib";
    std::vector<std::string> librariesToPatch = createLibraryNamesList("QtCore");
    string_utils::strings libraries;

    for(string_utils::strings::iterator it = librariesToPatch.begin(); it != librariesToPatch.end(); ++ it) {
        libraries.push_back(pathToQt + '/' + librariesDir + '/' + *it);
    }

    return existingFiles(libraries);
}

std::vector<std::string> PatcherApplication::mkspecsToPatch(const std::string &pathToQt) const
{
    string_utils::strings mkspecs;
    mkspecs.push_back(pathToQt + "/mkspecs/default/qmake.conf");
    mkspecs.push_back(pathToQt + "/.qmake.cache");

    return existingFiles(mkspecs);
}

std::vector<std::string> PatcherApplication::existingFiles(const std::vector<std::string> &files) const
{
    string_utils::strings foundFiles;
    for(string_utils::strings::const_iterator it = files.begin();
        it != files.end(); ++it) {
        if (file_utils::fileExists(*it))
            foundFiles.push_back(*it);
    }
    return foundFiles;
}

void PatcherApplication::printHelp()
{
    std::cout << "Usage: " << applicationName << " <path-to-qt>" << std::endl;
}

void PatcherApplication::printVersion()
{
    std::cout << applicationName << " v." << applicationVersion << std::endl;
}

