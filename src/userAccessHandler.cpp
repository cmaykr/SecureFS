#include "userAccessHandler.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

std::vector<unsigned char> UserAccessHandler::getObject(Session const& session, Object *objMetadata)
{
    if (!ah->authorizeUserActionOnObject(session.getUser(), *objMetadata))
    {
        return std::vector<unsigned char>{};
    }

    if (dynamic_cast<Directory*>(objMetadata) != nullptr)
    {
        // Object is of type directory, return directory.
    }
    else if (dynamic_cast<File*>(objMetadata) != nullptr)
    {
        // Object is of type File

        std::vector<unsigned char> data {sfs->readFile(dynamic_cast<File*>(objMetadata)->getName())};
        return data;
    }

    return std::vector<unsigned char>{};
}

void UserAccessHandler::writeToFile(Session const &session, File & file, std::vector<unsigned char> const& data)
{
    sfs->createFile(file.getName(), data);
}
