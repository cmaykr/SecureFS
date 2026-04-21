#pragma once

#include "object.hpp"

#include <vector>


class SFS
{
public:
    File* createFile(File & newFile, const char* data);
    std::vector<char> readFile(File const& file) const;

    Directory* getDirectory(std::string const& fileName) const;
private:

};