#ifndef PATCHERAPPLICATION_H
#define PATCHERAPPLICATION_H

#include <QCoreApplication>
#include <QTextStream>
#include "arguments.h"

class PatcherApplication : public QCoreApplication {
public:
    PatcherApplication(int& argc, char *argv[]);
    ~PatcherApplication();

    int run();

private:
    QString getPathFromArguments(QStringList arguments);
    bool isValidPathToQt(QString pathToQt);

    void printHelp();
    void printVersion();


    // -- members
    QTextStream cout;
    Arguments args;
};

#endif // PATCHERAPPLICATION_H
