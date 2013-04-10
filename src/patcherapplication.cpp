#include "patcherapplication.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include "patcher.h"
#include "binarypatcher.h"
#include "textpatcher.h"
#include "utils/stringformat.h"

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

    return true;
}
PatcherApplication::Error PatcherApplication::patchQtInDir(const std::string& pathToQt) const
{
    const char* executablesDir = "bin";
    std::vector<std::string> executablesToPatch;
    executablesToPatch.push_back("qmake");
    executablesToPatch.push_back("qmake.exe");

    const char* librariesDir = "lib";
    std::vector<std::string> librariesToPatch = createLibraryNamesList("QtCore");

    std::vector<std::string> textFilesToPatch;
    textFilesToPatch.push_back("/mkspecs/default/qmake.conf");
    textFilesToPatch.push_back("/.qmake.cache");

    std::string(executablesDir) == std::string(librariesDir);
    std::string(executablesDir) == pathToQt;
    librariesToPatch.empty();

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
    result.push_back(stringformat("%s.%s", baseLibraryName, "dll"));
    result.push_back(stringformat("%s.%s", baseLibraryName, "lib"));
    // debug
    result.push_back(stringformat("%sd.%s", baseLibraryName, "dll"));
    result.push_back(stringformat("%sd.%s", baseLibraryName, "lib"));

    // on *unix they are called *.so, *.a, *.la or *.dylib
    result.push_back(stringformat("lib%s.%s", baseLibraryName, "so"));
    result.push_back(stringformat("lib%sd.%s", baseLibraryName, "so"));

    result.push_back(stringformat("lib%s.%s", baseLibraryName, "a"));
    result.push_back(stringformat("lib%sd.%s", baseLibraryName, "a"));

    result.push_back(stringformat("lib%s.%s", baseLibraryName, "la"));
    result.push_back(stringformat("lib%sd.%s", baseLibraryName, "la"));

    result.push_back(stringformat("lib%s.%s", baseLibraryName, "dylib"));
    result.push_back(stringformat("lib%sd.%s", baseLibraryName, "dylib"));

    return result;
}

void PatcherApplication::printHelp()
{
    std::cout << "Usage: " << applicationName << " <path-to-qt>" << std::endl;
}

void PatcherApplication::printVersion()
{
    std::cout << applicationName << " v." << applicationVersion << std::endl;
}

