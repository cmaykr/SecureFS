#include "SFS.hpp"
#include "object.hpp"
#include "SAH.hpp"
#include "user.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

int main()
{
    SFS fs{};
    SAH sah{&fs};

    std::string text{"Hello!!!"};
    // std::cout << text << std::endl;

    File file{"test.txt", 0, 0, NULL, 0};

    fs.createFile(file, text.c_str());

    // std::cout << fs.readFile(file) << std::endl;

    User usr{"John", "1"};
    std::vector<char> objData {sah.getObject(usr, &file)};

    std::copy(std::begin(objData), std::end(objData), std::ostream_iterator<char>(std::cout));
}