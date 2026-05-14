#pragma once

#include "credentialStore.hpp"
#include "session.hpp"

struct Context
{
    CredentialStore* cs;
    Session& session;
};

