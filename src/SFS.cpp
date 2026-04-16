#include "SFS.hpp"

#include <fstream>
#include <iostream>

File *SFS::createFile(File & newFileMetadata, const char* data)
{
    std::ofstream istream{newFileMetadata.getName()};

    if (!istream.is_open())
    {
        return nullptr;
    }
    else
    {
        istream << data;

        istream.close();
    }
    return nullptr;
}

char* SFS::readFile(File* file) const
{
    // Read file and return the data.
    // Should the data be copied?
}
