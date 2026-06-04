#include "credentialStore.hpp"

#include <iostream>
#include <fstream>

CredentialStore::CredentialStore(std::string const& credentialsFilename)
    : credentialsFilename{credentialsFilename}
{}

bool CredentialStore::addUser(User const &newUser)
{
    User user{newUser.username, newUser.password, newUser.securityLevel, newUser.securityDomain};

    std::ofstream credentialFile {"data/" + credentialsFilename, std::ios::app};

    credentialFile << user << '\n';

    /// Need to check if user already exists.
    return false;
}

User CredentialStore::authenticateUser(User const &userToAuthenticate) const
{
    std::ifstream credentialFile{"data/" +  credentialsFilename};

    User user{};
    credentialFile >> user;

    if (user.username == userToAuthenticate.username && user.password == userToAuthenticate.password)
        {
            /// Credentials match
            user.authenticationToken = "1";
            return user;
        }

    return User{};
}
