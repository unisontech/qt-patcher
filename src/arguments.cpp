#include "arguments.h"
#include <QFileInfo>

Arguments::Arguments(QStringList rawArguments)
    : _rawArguments(rawArguments)
{
}

Arguments::~Arguments()
{
}

QString Arguments::calledBinaryName()
{
    QFileInfo info(_rawArguments.first());
    return info.fileName();
}

QString Arguments::getFirstArgument()
{
    const int argsToSkip = 1;
    for (QStringList::iterator it = _rawArguments.begin() + argsToSkip; it != _rawArguments.end(); ++it) {
        if (!it->startsWith("-") && !it->startsWith("--"))
            return *it;
    }

    return "";
}

bool Arguments::containsKey(const char *shortKey, const char *longKey)
{
    return containsKey(shortKey) || containsLongKey(longKey);
}

bool Arguments::containsKey(const char *key)
{
    if (key == 0)
        return false;

    return _rawArguments.contains(QString("-%1").arg(key));
}

bool Arguments::containsLongKey(const char *longKey)
{
    if (longKey == 0)
        return false;

    return _rawArguments.contains(QString("--%1").arg(longKey));
}



