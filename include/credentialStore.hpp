#pragma once

#include "user.hpp"
#include "object.hpp"

#include <map>

class CredentialStore
{
public:
    CredentialStore() = default;

    bool addUser(User const& newUser);

    User authenticateUser(User const& user) const;
private:
    std::map<std::string, User> users;
};