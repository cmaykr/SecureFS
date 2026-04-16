#include "SAH.hpp"

#include <iostream>

char *SAH::getObject(User const &user, Object *objMetadata)
{
    if (dynamic_cast<Directory*>(objMetadata) != nullptr)
    {
        // Object is of type directory, return directory.
    }
    else if (dynamic_cast<File*>(objMetadata) != nullptr)
    {
        // Object is of type File

        return sfs->readFile(dynamic_cast<File*>(objMetadata));
    }

    return "test";
}