
#ifndef AZGARD_LIB_FILE_MANAGER
#define AZGARD_LIB_FILE_MANAGER

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

friend class FileManager;
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
class FileManager {
public:

    static FileManager* open(const char* path, int fileMode = FileMode::binary);
    static void close(FileManager* file);
    

    void write(std::string data);
    std::string getBuffer();
    std::string getNextLine();
    bool isEndOfFile();
private:
    FileManager();
    ~FileManager();

    class NativeFileHandle;
    NativeFileHandle* handle = nullptr;
};


}
#endif