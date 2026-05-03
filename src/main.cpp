#include "secureFileSystem.hpp"
#include "object.hpp"
#include "userAccessHandler.hpp"
#include "user.hpp"
#include "authorizationHandler.hpp"
#include "credentialStore.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

int main()
{
    User user1{"john123", "", "1234", 3, 2};
    User user2{"erik321", "", "password123", 1, 0};
    CredentialStore cs{};
    cs.addUser(user1);
    cs.addUser(user2);

    SecureFileSystem fs{};
    AuthorizationHandler ah{&cs};

    UserAccessHandler sah{&fs, &ah};

    std::string text{"Hello!!!"};
    // std::cout << text << std::endl;

    File file{"test.txt", 2, 0, NULL, 0};

    fs.createFile(file, text.c_str());

    // std::cout << fs.readFile(file) << std::endl;

    std::vector<char> objData {sah.getObject(user1, &file)};

    std::copy(std::begin(objData), std::end(objData), std::ostream_iterator<char>(std::cout));
}