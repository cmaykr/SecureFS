#pragma once

#include "object.hpp"
#include "user.hpp"
#include "secureFileSystem.hpp"
#include "authorizationHandler.hpp"
#include "session.hpp"

class UserAccessHandler
{
public:
    UserAccessHandler(SecureFileSystem* sfs, AuthorizationHandler* ah)
        : sfs{sfs}, ah{ah}
    {}

    std::vector<char> getObject(Session const& session, Object* objMetadata);

    void createFile(Session const& session, std::string const& filename);

    void writeToFile(Session const& session, File & file, const char* data);

private:
    SecureFileSystem* sfs;
    AuthorizationHandler* ah;
};