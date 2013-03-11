#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <QStringList>

class Arguments {
public:
    Arguments(QStringList rawArguments);
    ~Arguments();

    QString calledBinaryName();

    QString getFirstArgument();

    bool containsKey(const char* shortKey, const char* longKey);
    bool containsKey(const char* key);
    bool containsLongKey(const char* longKey);

private:
    QStringList _rawArguments;
};

#endif //ARGUMENTS_H
