#include "SAH.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

std::vector<char> SAH::getObject(User const &user, Object *objMetadata)
{
    if (dynamic_cast<Directory*>(objMetadata) != nullptr)
    {
        // Object is of type directory, return directory.
    }
    else if (dynamic_cast<File*>(objMetadata) != nullptr)
    {
        // Object is of type File

        std::vector<char> data {sfs->readFile(*dynamic_cast<File*>(objMetadata))};
        return data;
    }

    return std::vector<char>{};
}