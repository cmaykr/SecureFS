#include "secureFileSystem.hpp"
#include "object.hpp"
#include "userAccessHandler.hpp"
#include "user.hpp"
#include "authorizationHandler.hpp"
#include "credentialStore.hpp"
#include "Commands/command.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <map>
#include <functional>

int getInt()
{
    std::string input{};
    std::getline(std::cin, input);

    return std::stoi(input);
}

User loginUser(std::string const& username, std::string const& password, CredentialStore* cs)
{
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
    std::getline(std::cin, username);
    std::cout << "Password: ";
    std::getline(std::cin, password);
    std::cout << "Security level: ";
    securityLevel = getInt();
    std::cout << "Security domain: ";
    securityDomain = getInt();
    
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

class Session
{
public:
    Session(CredentialStore * cs)
        : cs{cs}
    {

    }

    void operator()(std::vector<std::string> & args)
    {
        createSession();
    }

    void createSession()
    {
        std::string username{};
        std::string password{};
        std::cout << "Type in username and password:" << std::endl;
        std::cout << "Username: ";
        // std::cin >> username;
        std::getline(std::cin, username);
        std::cout << "Password: ";
        // std::cin >> password;
        std::getline(std::cin, password);

        user = loginUser(username, password, cs);

        if (user.authenticationToken == "1")
        {
            std::cout << "Login successful!" << std::endl;
        }
    }

    User getUser() const
    {
        return user;
    }
private:
    User user;
    CredentialStore* cs;
};

void read(Session const& session)
{
    std::cout << "Current user: " << session.getUser().username << std::endl;
}

// static std::map<std::string, std::function<void(std::vector<std::string>&)>> commands;

int main()
{
    CredentialStore cs{};


    User currentUser{};
    bool exit = false;
    Session currentSession{&cs};
    std::cout << "Welcome to the secure file system handler!" << std::endl;
    while (exit == false)
    {
        std::string command{};
        std::string args{};
        std::vector<std::string> commandTokens{};
        
        std::cout << "> ";
        // std::cin >> command;

        getline(std::cin, args, '\n');
        commandTokens = std::vector<std::string>{tokenizer(args)};

        // while (std::cin >> command)
        // {
        //     commandTokens.push_back(command);
        // }
        // while (commandTokens.empty());
        // {
        //     std::cout << "> ";
        //     getline(std::cin, command, '\n');
        // }

        
        
        if (!commandTokens.empty())
        {
            if (commandTokens.front() == "login")
            {
                currentSession.createSession();
            }
            else if (commandTokens.front() == "addUser")
                createUserMenu(&cs);
            else if (commandTokens.front() == "read")
            {
                read(currentSession);
            }
        }
    }
}