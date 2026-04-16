#pragma once

#include "object.hpp"
#include "user.hpp"
#include "SFS.hpp"

class SAH
{
public:
    SAH(SFS* sfs)
        : sfs{sfs}
    {}

    char* getObject(User const& user, Object* objMetadata);

private:
    SFS* sfs;
};