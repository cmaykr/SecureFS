#include "credentialStore.hpp"

bool CredentialStore::addUser(User const &newUser)
{
    User user{newUser.username, std::string{}, newUser.password, newUser.securityLevel, newUser.securityDomain};
    users.try_emplace(user.username, user);
    /// Need to check if user already exists.
    return false;
}

User CredentialStore::authenticateUser(User const &userToAuthenticate) const
{
    auto it = users.find(userToAuthenticate.username);
    if (it != users.end()) // Check if user exists.
    {
        if (it->second.password == userToAuthenticate.password)
        {
            /// Credentials match
            User storedUser {it->second};
            storedUser.authenticationToken = "1";
            return storedUser;
        }

    }

    return User{};
}
