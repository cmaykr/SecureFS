#include "secureFileSystem.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <vector>

SecureFileSystem::SecureFileSystem(std::string const &fileBasePath)
    : files{}, baseDirectory{"/", 0, 0}, basePath{fileBasePath}
{

}

File *SecureFileSystem::createFile(File &newFileMetadata, const char *data)
{
    std::ofstream ostream(basePath + "/" + newFileMetadata.getName());

    // if (ostream.good())
    // {
    //     return nullptr;
    // }
    
    if (!ostream.is_open())
    {
        std::cout << "Couldn't open file" << std::endl;
        return nullptr;
    }
    else
    {
        ostream << data;
        ostream.close();

    }
    return nullptr;
}

std::vector<char> SecureFileSystem::readFile(File const& file) const
{
    // Read file and return the data.
    // Should the data be copied?

    std::ifstream ifs{basePath + "/" + file.getName()};
    std::vector<char> data{};

    int i = 0;
    char c{};
    while (ifs.get(c))
    {
        data.push_back(c);
        ++i;
    }

    return data;
}

int SecureFileSystem::createDirectory(Directory &newDirectory, Directory const& parentDirectory)
{
    Object* parent = files[parentDirectory.getName()];

    if (!dynamic_cast<Directory*>(parent))
        return -1;

    Directory* parentDir = dynamic_cast<Directory*>(parent);

    parentDir->addChild(new Object{newDirectory});

    return 0;

}

Directory SecureFileSystem::getDirectoryMetaData(Directory const &newDirectory) const
{
    Directory* dir = dynamic_cast<Directory*>(files.at(newDirectory.getName()));

    if (dir != nullptr)
    {
        return *dir;
    }

    return Directory();
}
