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

using FunctionType = int(Context&, std::vector<std::string>&);

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
    {
        std::cout << "Invalid number of arguments!" << std::endl;
        return -1;
    }

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

int write(Context & context, std::vector<std::string> const&)
{
    std::string filename{};
    int intInput {};
    
    std::cout << "What should the file be called? ";
    std::getline(std::cin, filename, '\n');
    File fileToCreate{filename};
    std::cout << "Which security domain should the file exist in? ";
    intInput = getInt();
    fileToCreate.setSecurityDomain(intInput);
    std::cout << "Which security level should the file have? ";
    intInput = getInt();
    fileToCreate.setSecurityLevel(intInput);

    std::cout << "Write the text that should be written to the file:" << std::endl;
    
    std::string text{};
    std::getline(std::cin, text, '\n');


    context.uah->writeToFile(context.session, fileToCreate, text.c_str());
    
    return 0;
}

int main()
{
    std::unordered_map<std::string, std::function<FunctionType>> commands{};

    commands.emplace("login", Login{});
    commands.emplace("read", read);
    commands.emplace("addUser", addUser);
    commands.emplace("write", write);

    auto func = std::function<FunctionType>([&commands](Context & context, std::vector<std::string> const&)
        {
            auto it = commands.begin();

            std::cout << "Commands: " << std::endl;
            for (; it != commands.end(); ++it)
            {
                std::cout << "  " << it->first << std::endl;
            }
            return 0;
        });

    commands.emplace("help", func);
    commands.emplace("logout", std::function<FunctionType>([](Context & context, std::vector<std::string> const&)
    {
        context.session.setUser(User{});
        return 0;
    }));

    commands.emplace("pwd", std::function<FunctionType>([](Context & context, std::vector<std::string> const&){
        std::cout << context.currentDirectory->getDirectoryTree() << std::endl;

        return 0;
    }));
    commands.emplace("cd", std::function<FunctionType>([](Context & context, std::vector<std::string> const& args){
        // std::cout << context.currentDirectory.getAbsolutePath() << std::endl;

        if (args.size() != 2)
            return -1;
        
        Directory* newDir = new Directory{args[1], 0, 0, context.currentDirectory}; // change to do this inside the Directory class
        context.currentDirectory = newDir;
        // context.currentDirectory = context->currentDirectory.switchDirectory(newDir);

        return 0;
    }));
    
    
    CredentialStore cs{"credentials"};

    User currentUser{};
    bool exit = false;
    Session currentSession{};
    currentSession.createSession();

    SecureFileSystem sfs{"root"};
    AuthorizationHandler ah{&cs};
    UserAccessHandler uah{&sfs, &ah};
    Context context{&cs, &uah, currentSession, new Directory{"root", 0, 0}};
    std::cout << "Welcome to the secure file system handler!" << std::endl;

    Directory* childDir = new Directory{"private", 2, 1};
    childDir->addChild(new Directory{"test", 3, 2});
    context.currentDirectory->addChild(childDir);
    


    while (!std::cin.eof())
    {
        std::string command{};
        std::string args{};
        std::vector<std::string> commandTokens{};
        
        std::cout << context.currentDirectory->getDirectoryTree() << " > ";
        
        getline(std::cin, args, '\n');
        commandTokens = std::vector<std::string>{tokenizer(args)};

        if (!commandTokens.empty())
        {
            auto it = commands.find(commandTokens.front());

            if (it != commands.end())
                commands[commandTokens.front()](context, commandTokens);
            else
                std::cout << "Command not found! Type 'help' for a list of commands" << std::endl;
        }
    }

    sfs.save();
}