#pragma once

#include "context.hpp"

class Command
{
public:
    Command() = default;

    virtual int operator()(Context & context, std::vector<std::string> const& arguments) = 0;
};