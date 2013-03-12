#include "patcherapplication.h"
#include <iostream>
#include <cstdio>

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
    if (pathToQt.data()) {
        // do nothing
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
    case TooLongPathToQt:
        std::cout << "Warning: Path [ " << pathToQt << " ] is too long. Patcher will most likely fail to read files." << std::endl;
        return;
    default:
        std::cout << "Error: unknown internal error." << std::endl;
        return;
    }
}

void PatcherApplication::printHelp()
{
    std::cout << "Usage: " << applicationName << " <path-to-qt>" << std::endl;
}

void PatcherApplication::printVersion()
{
    std::cout << applicationName << " v." << applicationVersion << std::endl;
}

