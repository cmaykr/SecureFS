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

    std::vector<unsigned char> getObject(Session const& session, std::string const& fileName);

    void createFile(Session const& session, std::string const& filename);

    void writeToFile(Session const& session, File & file, std::vector<unsigned char> const& data);

private:
    SecureFileSystem* sfs;
    AuthorizationHandler* ah;
};