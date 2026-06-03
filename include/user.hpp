#pragma once

#include <string>
#include <iostream>

struct User
{
    User() = default;
    User(std::string username, std::string password, unsigned int secLevel, unsigned secDomain)
        : username{username}, password{password}, securityLevel{secLevel}, securityDomain{secDomain}
    {}

    std::string username;
    std::string password; /// Need to change to something secure, should not be stored?
    std::string authenticationToken;
    unsigned int securityLevel;
    unsigned int securityDomain;
};

inline std::ostream& operator<<(std::ostream & os, User const& user)
{
    os << "" << user.username << " " << user.password << " " << user.securityDomain << " " << user.securityLevel << "";

    return os;
}

inline std::istream& operator>>(std::istream & is, User & user)
{
    std::string text{};
    is >> user.username >> user.password >> user.securityDomain >> user.securityLevel;


    return is;
}

