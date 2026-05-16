#pragma once

#include "credentialStore.hpp"
#include "session.hpp"
#include "secureFileSystem.hpp"
#include "userAccessHandler.hpp"

struct Context
{
    CredentialStore* cs;
    UserAccessHandler* uah;
    Session& session;
};

