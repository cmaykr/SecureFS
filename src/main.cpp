#include "SFS.hpp"
#include "object.hpp"
#include "SAH.hpp"
#include "user.hpp"

#include <iostream>

int main()
{
    SFS fs{};
    SAH sah{};

    std::string text{"Hello!!!"};
    // std::cout << text << std::endl;

    File file{"test.txt", 0, 0, NULL, 0};

    fs.createFile(file, text.c_str());

    fs.readFile(file.getName());

    User usr{"John", "1"};
    std::string objName {sah.getObject(usr, &file)};

    std::cout << objName << std::endl;
}