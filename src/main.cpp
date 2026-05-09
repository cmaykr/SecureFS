#include "secureFileSystem.hpp"
#include "object.hpp"
#include "userAccessHandler.hpp"
#include "user.hpp"
#include "authorizationHandler.hpp"
#include "credentialStore.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>

User loginUser(CredentialStore* cs)
{
    std::string username{};
    std::string password{};

    std::cout << "Enter your username: ";
    std::cin >> username;
    std::cout << "Enter your password: ";
    std::cin >> password;

    User authUser = cs->authenticateUser(User{username, password, 0, 0});

    return authUser;
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

    User user{username,password, securityLevel, securityDomain};
    cs->addUser(user);
}

std::vector<std::string> tokenizer(std::string const& command)
{
    std::vector<std::string> tokens{};
    std::istringstream ss{command};
    
    std::string token{};
    while (getline(ss, token))
    {
        tokens.push_back(token);
    }


    return tokens;
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



    
    User currentUser{};
    bool exit = false;
    std::cout << "Welcome to the secure file system handler!" << std::endl;
    while (exit == false)
    {
        std::string command{};
        getline(std::cin, command, '\n');

        std::vector<std::string> commandTokens {tokenizer(command)};

        std::copy(std::begin(commandTokens), std::end(commandTokens), std::ostream_iterator<std::string>(std::cout, " "));
        std::cout << std::endl;

        if (command == "login")
        {
            currentUser = loginUser(&cs);
        }
        else if (command == "createuser")
        {
            createUserMenu(&cs);
        }
        else
        {
            std::cout << "Invalid command!" << std::endl;
        }

        
    }
}