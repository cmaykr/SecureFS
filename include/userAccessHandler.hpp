#pragma once

#include "object.hpp"
#include "user.hpp"
#include "secureFileSystem.hpp"
#include "authorizationHandler.hpp"

class UserAccessHandler
{
public:
    UserAccessHandler(SecureFileSystem* sfs, AuthorizationHandler* ah)
        : sfs{sfs}, ah{ah}
    {}

    std::vector<char> getObject(User const& user, Object* objMetadata);

private:
    SecureFileSystem* sfs;
    AuthorizationHandler* ah;
};