#pragma once

class Command
{
public:
    Command() = default;

    virtual int operator()() = 0;
};