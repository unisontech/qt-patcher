#ifndef STRINGFORMAT_H
#define STRINGFORMAT_H

// FIXME: on windows vsprintf considered unsave.
// as a replacement vsprintf_s is provided, but we can't be sure
// if there is such function in non-windows systems
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <cstdarg>

std::string stringvformat (const char *format, va_list argumentsList);
std::string stringformat (const char *format, ...);

#endif // STRINGFORMAT_H
