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
#include <iterator>

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
    std::vector<unsigned char> text {context.uah->getObject(context.session, &filename)};

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


    context.uah->writeToFile(context.session, fileToCreate, std::vector<unsigned char>(text.begin(), text.end()));
    
    return 0;
}

int main()
{
    SecureFileSystem sfs{"root"};
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

    commands.emplace("ls", std::function<FunctionType>([&sfs](Context & context, std::vector<std::string> const&){
        std::vector<Node*> children {sfs.getDirectoryChildren(context.currentDir->name)};

        for (Node* child: children)
        {
            std::cout << child->name << " ";
        }
        std::cout << std::endl;

        return 0;
    }));

    commands.emplace("pwd", std::function<FunctionType>([&sfs](Context & context, std::vector<std::string> const&){
        std::vector<std::string> absolutePath {sfs.getDirectoryTree(context.currentDir->name)};

        std::copy(std::rbegin(absolutePath), std::rend(absolutePath), std::ostream_iterator<std::string>(std::cout, "/"));
        std::cout << std::endl;

        return 0;
    }));
    commands.emplace("cd", std::function<FunctionType>([&sfs](Context & context, std::vector<std::string> const& args){

        Node* newNode{sfs.getNode(args[1])};

        if (newNode == nullptr)
        {
            std::cout << "Directory does not exist!" << std::endl;
            return 1;
        }
        if (newNode->isDirectory)
        {
            context.currentDir = newNode;
        }
        return 0;
    }));
    
    
    CredentialStore cs{"credentials"};

    User currentUser{};
    bool exit = false;
    Session currentSession{};
    currentSession.createSession();

    AuthorizationHandler ah{&cs};
    UserAccessHandler uah{&sfs, &ah};
    Context context{&cs, &uah, currentSession, new Directory{"root", 0, 0}};
    std::cout << "Welcome to the secure file system handler!" << std::endl;

    Directory* childDir = new Directory{"private", 2, 1};
    childDir->addChild(new Directory{"test", 3, 2});
    // context.currentDirectory->addChild(childDir);
    context.currentDir = sfs.getRootNode();
    
    std::string text{"Hello, this is file test1"};
    sfs.createFile("test1", std::vector<unsigned char>{std::begin(text), std::end(text)}, "root");
    sfs.createDirectory("layer1", "root");
    sfs.createDirectory("layer2", "layer1");
    text = {"This is a layer2 file"};
    sfs.createFile("layer2_file", std::vector<unsigned char>{std::begin(text), std::end(text)}, "layer2");

    while (!std::cin.eof())
    {
        std::string command{};
        std::string args{};
        std::vector<std::string> commandTokens{};
        
        // std::cout << context.currentDirectory->getDirectoryTree() << " > ";
        std::vector<std::string> currDirTree { sfs.getDirectoryTree(context.currentDir->name)};
        std::copy(std::rbegin(currDirTree), std::rend(currDirTree), std::ostream_iterator<std::string>(std::cout, "/"));
        std::cout << " > ";
        
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