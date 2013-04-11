#ifndef STRINGUTILS_H
#define STRINGUTILS_H

// FIXME: on windows vsprintf considered unsave.
// as a replacement vsprintf_s is provided, but we can't be sure
// if there is such function in non-windows systems
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <cstdarg>
#include <vector>

namespace string_utils {
    typedef std::vector<std::string> strings;

    std::string vformat (const char *format, va_list argumentsList);
    std::string format (const char *format, ...);

    bool contains(const std::string& string, const std::string& needle);
    strings split(const std::string& string, const std::string& delimiter);

    // trim from start
    std::string ltrim(const std::string& string);
    // trim from end
    std::string rtrim(const std::string& string);
    // trim from both ends
    std::string trim(const std::string& string);
}

#endif // STRINGUTILS_H
