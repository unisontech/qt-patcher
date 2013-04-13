#include "fileutils.h"
#include <sys/types.h>
#include <sys/stat.h>

namespace file_utils {

bool fileExists(const std::string& filename)
{
    struct stat buf;
    return ::stat(filename.c_str(), &buf) != -1;
}

bool isDirectory(const std::string& filename)
{
    struct stat buf;
    return ::stat(filename.c_str(), &buf) != -1 && (buf.st_mode & __S_IFDIR);
}

}
