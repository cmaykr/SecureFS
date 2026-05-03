#pragma once

#include <string>

struct User
{
    std::string username;
    std::string authenticationToken;
    std::string password; /// Need to change to something secure, should not be stored?
    unsigned int securityLevel;
    unsigned int securityDomain;
};
