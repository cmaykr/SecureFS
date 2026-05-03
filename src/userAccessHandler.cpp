#include "userAccessHandler.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

std::vector<char> UserAccessHandler::getObject(User const &user, Object *objMetadata)
{
    if (ah->authorizeUserActionOnObject(user, *objMetadata))

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