#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>

namespace file_utils {

    /**
     * Check if a file exists
     * @param[in] filename - the name of the file to check
     * @return    true if the file exists, else false
     */
    bool fileExists(const std::string& filename);

    bool isDirectory(const std::string& filename);
}

#endif // FILEUTILS_H
