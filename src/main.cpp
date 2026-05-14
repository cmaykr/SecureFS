#include "secureFileSystem.hpp"
#include "object.hpp"
#include "userAccessHandler.hpp"
#include "user.hpp"
#include "authorizationHandler.hpp"
#include "credentialStore.hpp"
#include "Commands/command.hpp"
#include "Commands/login.hpp"

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

int read(Context & context, std::vector<std::string> const&)
{
    std::cout << "Current user: " << context.session.getUser().username << std::endl;

    return 0;
}

int addUser(Context & context, std::vector<std::string> const&)
{
    createUserMenu(context.cs);

    return 0;
}

int main()
{
    std::unordered_map<std::string, std::function<int(Context&, std::vector<std::string>&)>> commands{};

    commands.emplace("login", Login{});
    commands.emplace("read", read);
    commands.emplace("addUser", addUser);
    
    
    CredentialStore cs{};

    User currentUser{};
    bool exit = false;
    Session currentSession{};
    currentSession.createSession();

    Context context{&cs, currentSession};
    std::cout << "Welcome to the secure file system handler!" << std::endl;

    Login login{};
    while (exit == false)
    {
        std::string command{};
        std::string args{};
        std::vector<std::string> commandTokens{};
        
        std::cout << "> ";
        
        getline(std::cin, args, '\n');
        commandTokens = std::vector<std::string>{tokenizer(args)};

        
        
        if (!commandTokens.empty())
        {
            commands[commandTokens.front()](context, commandTokens);
        }
    }
}