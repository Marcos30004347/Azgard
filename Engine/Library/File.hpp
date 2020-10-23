#ifndef AZGARD_LIB_FILE
#define AZGARD_LIB_FILE

#include <string>

namespace Azgard {

/**
 * @brief Object that represents a path on the platform file system.
 */
class FilePath {
public:
    /**
     * @brief Construct a new File Path object
     * 
     * @param path: Begining of a path.
     * @param ...
     */
    FilePath(const char* path, ...);

private:
    /**
     * @brief buffer that holds the string path.
     */
    std::string buffer;

friend class File;
};

enum FileMode {
    binary = 1,
    atEnd = 2,
    read = 4,
    write = 8,
    truncate = 16,
    append = 32,
};
/**
 * @brief Class used to deal with files.
 */
class File {
public:

    static File* open(const char* path, int fileMode = FileMode::binary);
    static void close(File* file);
    

    void write(std::string data);
    std::string getBuffer();
    std::string getNextLine();
    bool isEndOfFile();
private:
    File();
    ~File();

    class NativeFileHandle;
    NativeFileHandle* handle = nullptr;
};


}
#endif