#pragma once

#include "command.hpp"
#include "user.hpp"
#include "credentialStore.hpp"

class Login : public Command
{
public:
    int operator()(Context & context, std::vector<std::string> const& arguments) override;
};