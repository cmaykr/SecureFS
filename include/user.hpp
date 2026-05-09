#pragma once

#include <string>

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
