#pragma once

#include "object.hpp"

#include <vector>
#include <map>


class SecureFileSystem
{
public:
    SecureFileSystem(std::string const& filesystemName);

    ~SecureFileSystem();

    /// Saves the filesystem to a file
    bool save();

    File* createFile(File & newFile, std::string parentDirectoryName, const char* data);
    std::vector<char> readFile(File const& file) const;

    int createDirectory(Directory & newDirectory, Directory const& parentDirectory);
    Directory getDirectoryMetaData(Directory const& newDirectory) const;

    // Directory* getDirectory(std::string const& fileName) const;
private:
    std::map<std::string, Object*> files; /// Stores the metadata about the objects on the system, and data location. Stores every single object on the system

    std::string filesystemName;
    Directory* rootDirectory;
};