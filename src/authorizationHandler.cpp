#include "authorizationHandler.hpp"
#include "credentialStore.hpp"

Token AuthorizationHandler::authenticateUser(User const &user)
{
    


    return Token(true);
}

bool AuthorizationHandler::authorizeUserActionOnObject(User const &user, Object const &object)
{
    User authenticatedUser {cs->authenticateUser(user)}; // Tries to authenticate the user and to get details from the credentialStore object.

    // Checks that user is authenticated and has the correct security level and domain for the object.
    if (!authenticatedUser.authenticationToken.empty()) // Checks that user is authenticated.
    {
        if (authenticatedUser.securityLevel >= object.getSecurityLevel() && authenticatedUser.securityDomain >= object.getSecurityDomain())
        {
            return true;
        }
    }
    return false;
}