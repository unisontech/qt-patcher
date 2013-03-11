#include "patcherapplication.h"
#include <QStringList>
#include <QFileInfo>
#include "stdio.h"

PatcherApplication::PatcherApplication(int& argc, char *argv[])
    : QCoreApplication(argc, argv)
    , cout(stdout, QIODevice::WriteOnly)
    , args(arguments())
{
    setApplicationName("qt-patcher");
    setApplicationVersion("0.1");
}

PatcherApplication::~PatcherApplication()
{
}

int PatcherApplication::run()
{
    if (args.containsKey("h", "help")) {
        printHelp();
        return 0;
    }

    if (args.containsKey("v", "version")) {
        printVersion();
        return 0;
    }

    QString pathToQt = args.getFirstArgument();
    if ( !isValidPathToQt( pathToQt ) ) {
        cout << "Path [ " << pathToQt << " ] is not a valid writeable directory"; endl(cout);
        return 1;
    }



    return 0;
}

bool PatcherApplication::isValidPathToQt(QString pathToQt)
{
    if (pathToQt.isEmpty())
        return false;

    QFileInfo fileInfo( pathToQt );
    if ( !fileInfo.isDir() )
        return false;
    if ( !fileInfo.isWritable() )
        return false;

    return true;
}

void PatcherApplication::printHelp()
{
    cout << "Usage: " << args.calledBinaryName() << " <path-to-qt>"; endl(cout);
}

void PatcherApplication::printVersion()
{
    cout << applicationName() << " v." << applicationVersion(); endl(cout);
}

