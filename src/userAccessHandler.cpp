#include "userAccessHandler.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

std::vector<unsigned char> UserAccessHandler::getObject(Session const& session, std::string const& fileName)
{
    Node* node {sfs->getNode(fileName)};
    // if (!ah->authorizeUserActionOnObject(session.getUser(), node))
    // {
    //     return std::vector<unsigned char>{};
    // }

    if (node->isDirectory)
    {
        // Object is of type directory, return directory.
    }
    else
    {
        // Object is of type File

        std::vector<unsigned char> data {sfs->readFile(fileName)};
        return data;
    }

    return std::vector<unsigned char>{};
}

void UserAccessHandler::writeToFile(Session const &session, File & file, std::vector<unsigned char> const& data)
{
    sfs->createFile(file.getName(), data);
}
