#include "usermanager.hpp"
#include <iostream>
#include <fstream>

void UserManager::saveUsers(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const User& user : users) {
            file << user.username << "," << user.password << "," << user.email << "," << user.age << "," << user.gender;
            for (const std::string& interest : user.interests) {
                file << "," << interest;
            }
            file << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Failed to open file for writing." << std::endl;
    }
}

void UserManager::loadUsersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            User user;
            size_t pos = 0;
            pos = line.find(",");
            user.username = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(",");
            user.password = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(",");
            user.email = line.substr(0, pos);
            line.erase(0, pos + 1);
            user.age = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find(",");
            user.gender = line.substr(0, pos);
            line.erase(0, pos + 1);
            while ((pos = line.find(",")) != std::string::npos) {
                user.interests.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            users.push_back(user);
        }
        file.close();
    } else {
        std::cerr << "Failed to open file for reading." << std::endl;
    }
}

void UserManager::registerUser() {
    User newUser;
    std::cout << "Enter username: ";
    std::getline(std::cin, newUser.username);
    std::string password;
    while (true) {
        std::cout << "Enter password (at least 8 characters): ";
        std::getline(std::cin, password);
        if (password.length() >= 8) {
            newUser.password = password;
            break;
        } else {
            std::cout << "Password must be at least 8 characters long." << std::endl;
        }
    }
    std::cout << "Enter email: ";
    std::getline(std::cin, newUser.email);
    std::cout << "Enter age: ";
    std::cin >> newUser.age;
    std::cin.ignore();
    std::cout << "Enter gender (male/female): ";
    std::getline(std::cin, newUser.gender);

    newUser.generateUserID();
    std::cout << "Your unique ID: " << newUser.userID << std::endl;

    newUser.sendVerificationCode();
    std::string code;
    std::cout << "Enter verification code: ";
    std::getline(std::cin, code);
    if (code == newUser.verificationCode) {
        users.push_back(newUser);
        saveUsers("users.txt");
        std::cout << "Registration successful!" << std::endl;
    } else {
        std::cout << "Invalid verification code. Registration cancelled." << std::endl;
    }
}

void UserManager::login() {
    std::string email;
    std::cout << "Enter email: ";
    std::getline(std::cin, email);
    for (User& user : users) {
        if (user.email == email) {
            std::string password;
            std::cout << "Enter password: ";
            std::getline(std::cin, password);
            if (user.password == password) {
                std::cout << "Login successful!" << std::endl;
                userMenu(user);
                return;
            } else {
                std::cout << "Invalid password." << std::endl;
                return;
            }
        }
    }
    std::cout << "User with this email not found." << std::endl;
}

void UserManager::userMenu(User& currentUser) {
    int choice;
    do {
        std::cout << "1. Find user by ID" << std::endl;
        std::cout << "2. Add friend" << std::endl;
        std::cout << "3. View profile" << std::endl;
        std::cout << "0. Log out" << std::endl;
        std::cout << "Choose an option: ";
        std::cin >> choice;
        std::cin.ignore();
        switch (choice) {
            case 1:
                findUserByID();
                break;
            case 2:
                addFriend(currentUser);
                break;
            case 3:
                currentUser.viewProfile();
                break;
            case 0:
                std::cout << "Logging out..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
                break;
        }
    } while (choice != 0);
}

void UserManager::findUserByID() {
    int userID;
    std::cout << "Enter user ID: ";
    std::cin >> userID;
    std::cin.ignore();
    for (const User& user : users) {
        if (user.userID == userID) {
            std::cout << "User found!" << std::endl;
            user.viewProfile();
            return;
        }
    }
    std::cout << "User with this ID not found." << std::endl;
}

void UserManager::addFriend(User& currentUser) {
    std::string friendUsername;
    std::cout << "Enter the username of the friend to add: ";
    std::getline(std::cin, friendUsername);
    currentUser.addFriend(friendUsername);
}

void UserManager::deleteUser(const std::string& email) {
    std::vector<User>::iterator it = std::remove_if(users.begin(), users.end(), [&](const User& user) {
        return user.email == email;
    });
    if (it != users.end()) {
        users.erase(it, users.end());
        std::cout << "User deleted." << std::endl;
        saveUsers("users.txt");
    } else {
        std::cout << "User not found." << std::endl;
    }
}


