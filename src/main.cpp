#include "secureFileSystem.hpp"
#include "object.hpp"
#include "userAccessHandler.hpp"
#include "user.hpp"
#include "authorizationHandler.hpp"
#include "credentialStore.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

User loginUser(CredentialStore* cs)
{
    

    return User{};
}

void userMenu(User const& loggedInUser)
{

}

void createUserMenu(CredentialStore* cs)
{

    std::string username{};
    std::string password{};
    unsigned int securityLevel{};
    unsigned int securityDomain{};

    std::cout << "Type in username and password:" << std::endl;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;
    std::cout << "Security level: ";
    std::cin >> securityLevel;
    std::cout << "Security domain: ";
    std::cin >> securityDomain;

    User user{username, std::string{}, password, securityLevel, securityDomain};
    cs->addUser(user);
}

int main()
{
    // User user1{"john123", "", "1234", 3, 2};
    // User user2{"erik321", "", "password123", 1, 0};
    CredentialStore cs{};
    // cs.addUser(user1);
    // cs.addUser(user2);

    // SecureFileSystem fs{};
    // AuthorizationHandler ah{&cs};

    // UserAccessHandler sah{&fs, &ah};

    // std::string text{"Hello!!!"};
    // // std::cout << text << std::endl;

    // File file{"test.txt", 2, 0, NULL, 0};

    // fs.createFile(file, text.c_str());

    // // std::cout << fs.readFile(file) << std::endl;

    // std::vector<char> objData {sah.getObject(user1, &file)};

    // std::copy(std::begin(objData), std::end(objData), std::ostream_iterator<char>(std::cout));



    bool exit = false;
    while (exit == false)
    {
        std::cout << "Choose an option: " << std::endl;
        std::cout << "1. Login \n2. Create user \n3. Exit" << std::endl;
        int choice{};
        std::cin >> choice;

        switch(choice)
        {
            case 1:
            {
                User loggedInUser {loginUser(&cs)};
                if (!loggedInUser.username.empty())
                    userMenu(loggedInUser);
                break;
            }
            case 2:
                createUserMenu(&cs);
                break;
            case 3:
                exit = true;
                break;
            default:
                break;
        }
    }
}