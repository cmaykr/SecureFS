#include "Commands/login.hpp"

#include <iostream>


int Login::operator()(Context & context, std::vector<std::string> const& arguments)
{
    std::string username{};
    std::string password{};
    
    std::cout << "Enter your username: ";
    getline(std::cin, username, '\n');
    std::cout << "Enter your password: ";
    getline(std::cin, password, '\n');

    User authUser = context.cs->authenticateUser(User{username, password, 0, 0});

    context.session.setUser(authUser);
    
    return 0;
}