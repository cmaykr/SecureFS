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
#include <map>


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

void login(int)
{
    
}

static std::map<std::string, void(*)(int)> commandFunctionPointers{{"login", login}};

int main()
{
    commandFunctionPointers.at("login")(0);
    CredentialStore cs{};

    User currentUser{};
    bool exit = false;
    std::cout << "Welcome to the secure file system handler!" << std::endl;
    while (exit == false)
    {
        std::string command{};
        std::cout << "> ";
        getline(std::cin, command, '\n');

        std::vector<std::string> commandTokens {tokenizer(command)};


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
            std::cout << "Unknown command!" << std::endl;
        }

        
    }
}