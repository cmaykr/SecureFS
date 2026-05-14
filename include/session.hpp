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
        // std::string username{};
        // std::string password{};
        // std::cout << "Type in username and password:" << std::endl;
        // std::cout << "Username: ";
        // // std::cin >> username;
        // std::getline(std::cin, username);
        // std::cout << "Password: ";
        // // std::cin >> password;
        // std::getline(std::cin, password);

        // user = loginUser(username, password, cs);

        // if (user.authenticationToken == "1")
        // {
        //     std::cout << "Login successful!" << std::endl;
        // }
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