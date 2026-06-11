#include "secureFileSystem.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <vector>

SecureFileSystem::SecureFileSystem(std::string const &filesystemName)
    : files{}, filesystemName{filesystemName}, rootDirectory{new Directory{"root", 2, 1}}
{

    std::ofstream fs{filesystemName, fs.binary | fs.out};

    if (!fs.is_open())
    {
        std::cerr << "File failed to open" << std::endl;
        throw std::runtime_error("File failed to open.");
    }
    fs.write(reinterpret_cast<char*>(&rootDirectory), sizeof rootDirectory);

    files[rootDirectory->getName()] = rootDirectory;

    fs.close();
}

SecureFileSystem::~SecureFileSystem()
{
    for (std::pair<std::string, Object*> object: files)
    {
        delete object.second;
    }
}

bool SecureFileSystem::save()
{
    std::ofstream ofs{filesystemName, ofs.binary | ofs.in};

    // ofs << *rootDirectory << std::endl;
    for (std::pair<std::string, Object*> file: files)
    {
        file.second->print(ofs);
    }

    // ofs.write(reinterpret_cast<char*>(&rootDirectory), size)

    ofs.close();

    return true;
}

File *SecureFileSystem::createFile(File &newFileMetadata, std::string parentDirectoryName, const char *data)
{
    // std::ofstream fs{filesystemName}

    newFileMetadata.addData(data);

    Directory* curDir{newFileMetadata.getParent()};

    while (true)
    {
        if (curDir->getParent() == nullptr)
        {
            // File does not have path to root
            std::cout << "No path to root directory!" << std::endl;
            break;
        }
        else if (curDir->getParent() == rootDirectory)
        {
            // File has path to root
            newFileMetadata.getParent()->addChild(new File{newFileMetadata});
        }
        else
        {
            // Parent is not yet root
            curDir = curDir->getParent();
        }
    }
}

std::vector<char> SecureFileSystem::readFile(File const& file) const
{

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
