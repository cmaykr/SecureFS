#pragma once

#include "command.hpp"
#include "user.hpp"
#include "credentialStore.hpp"

class Login : public Command
{
public:
    // int operator()(User const& user, CredentialStore * cs) override;
};