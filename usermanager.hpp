#ifndef USERMANAGER_HPP
#define USERMANAGER_HPP

#include "user.hpp"
#include <vector>
#include <string>

class UserManager {
private:
    std::vector<User> users;

public:
    User* getCurrentUser(const std::string& email);
    void saveUsers(const std::string& filename);
    void loadUsersFromFile(const std::string& filename);
    void registerUser();
    void login();
    void userMenu(User& currentUser);
    void findUserByID();
    void addFriend(User& currentUser);
    void deleteUser(const std::string& email);
    void becomeModerator(User& currentUser);
    void mainMenu();
};

#endif // USERMANAGER_HPP

