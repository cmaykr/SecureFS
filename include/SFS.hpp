#pragma once

#include "object.hpp"


class SFS
{
public:
    File* createFile(File & newFile, const char* data);
    char* readFile(File* file) const;

    Directory* getDirectory(std::string const& fileName) const;
private:

};