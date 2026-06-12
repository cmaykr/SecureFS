#pragma once

class Session
{
public:
    Session() = default;

    void operator()(std::vector<std::string> & args)
    {
        createSession();
    }

    void createSession()
    {
    }

    User getUser() const
    {
        return user;
    }

    void setUser(User const& newUser)
    {
        user = newUser;
    }
private:
    User user;
};