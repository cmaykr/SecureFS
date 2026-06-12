#pragma once

#include "credentialStore.hpp"
#include "session.hpp"
#include "secureFileSystem.hpp"
#include "userAccessHandler.hpp"
#include "object.hpp"

struct Context
{
    CredentialStore* cs;
    UserAccessHandler* uah;
    Session& session;

    Directory* currentDirectory;

    const Node * currentDir;

    int error {0};
};

