#include "stringutils.h"
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <cstdio>

namespace string_utils {

std::string vformat (const char *format, va_list argumentsList)
{
    // Allocate a buffer on the stack that's big enough for us almost
    // all the time.  Be prepared to allocate dynamically if it doesn't fit.
    size_t size = 1024;
    char stackbuf[1024];
    std::vector<char> dynamicbuf;
    char *buf = &stackbuf[0];

    while (1) {
        // Try to vsnprintf into our buffer.
        int needed = vsnprintf(buf, size, format, argumentsList);
        // NB. C99 (which modern Linux and OS X follow) says vsnprintf
        // failure returns the length it would have needed.  But older
        // glibc and current Windows return -1 for failure, i.e., not
        // telling us how much was needed.

        if (needed <= (int)size && needed >= 0) {
            // It fit fine so we're done.
            return std::string(buf, (size_t) needed);
        }

        // vsnprintf reported that it wanted to write more characters
        // than we allotted.  So try again using a dynamic buffer.  This
        // doesn't happen very often if we chose our initial size well.
        size = (needed > 0) ? (needed+1) : (size*2);
        dynamicbuf.resize (size);
        buf = &dynamicbuf[0];
    }
}

std::string format (const char *format, ...)
{
    va_list ap;
    va_start (ap, format);
    std::string buf = string_utils::vformat (format, ap);
    va_end (ap);
    return buf;
}

bool contains(const std::string& string, const std::string& needle)
{
    return string.find(needle) != std::string::npos;
}

strings split(const std::string& string, const std::string& delimiter)
{
    strings result;

    // TODO: not really most efficient but simple implementation
    std::size_t pos = string.find(delimiter);
    if (pos == std::string::npos) {
        result.push_back(string);
    } else {
        result.push_back(string.substr(0, pos));
        strings otherResuts = string_utils::split(string.substr(pos + delimiter.length()), delimiter);
        result.insert(result.end(), otherResuts.begin(), otherResuts.end());
    }

    return result;
}

std::string ltrim(const std::string& string)
{
    std::string s = string;
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

std::string rtrim(const std::string& string) {
    std::string s = string;
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

std::string trim(const std::string& string) {
    return string_utils::ltrim(string_utils::rtrim(string));
}

}
