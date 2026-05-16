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
    while (getline(ss, token, ' '))
    {
        tokens.push_back(token);
    }
    
    
    return tokens;
}

int read(Context & context, std::vector<std::string> const& args)
{
    if (args.size() != 2)
        return -1;


    File filename{args[1]};
    std::vector<char> text {context.uah->getObject(context.session, &filename)};

    if (text.empty())
        return -1;

    std::copy(std::begin(text), std::end(text), std::ostream_iterator<char>(std::cout, ""));
    std::cout << std::endl;

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

    SecureFileSystem sfs{};
    AuthorizationHandler ah{&cs};
    UserAccessHandler uah{&sfs, &ah};
    Context context{&cs, &uah, currentSession};
    std::cout << "Welcome to the secure file system handler!" << std::endl;

    Login login{};
    File text{"test.txt", 2, 2, 0, 0};
    sfs.createFile(text, "hello");

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