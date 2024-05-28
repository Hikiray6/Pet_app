#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
public:
    std::string username;
    std::string password;
    std::string email;
    int age;
    std::string gender;
    std::vector<std::string> interests;
    std::vector<std::string> friends;
    bool isAdmin;
    std::string verificationCode;
    int userID;

    User();

    void generateUserID();
    void sendVerificationCode();
    void addFriend(const std::string& friendUsername);
    void removeFriend(const std::string& friendUsername);
    void viewProfile() const;
};

#endif

