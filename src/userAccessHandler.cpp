#include "userAccessHandler.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

std::vector<char> UserAccessHandler::getObject(Session const& session, Object *objMetadata)
{
    if (!ah->authorizeUserActionOnObject(session.getUser(), *objMetadata))
    {
        return std::vector<char>{};
    }

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