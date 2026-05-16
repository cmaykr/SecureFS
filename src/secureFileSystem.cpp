#include "secureFileSystem.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <vector>

File *SecureFileSystem::createFile(File & newFileMetadata, const char* data)
{
    std::ofstream ostream(newFileMetadata.getName());

    // if (ostream.good())
    // {
    //     return nullptr;
    // }

    if (!ostream.is_open())
    {
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

    std::ifstream ifs{file.getName()};
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
