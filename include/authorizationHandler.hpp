#pragma once

#include "user.hpp"
#include "object.hpp"
#include "credentialStore.hpp"

using Token = bool;

class AuthorizationHandler 
{
public:
    AuthorizationHandler(CredentialStore* credentialStore)
        : cs{credentialStore}
    {};

    Token authenticateUser(User const& user);

    bool authorizeUserActionOnObject(User const& user, Object const& object);
private:
    CredentialStore* cs;
};