//
//  user.cpp
//  PetProject
//
//  Created by Daniil Lednik on 28.05.2024.
//
//
//  user.cpp
//  PetProject
//
//  Created by Daniil Lednik on 28.05.2024.
//
#include "user.hpp"
#include <iostream>
#include <algorithm>
#include <random>

User::User() : isAdmin(false), userID(0) {}

void User::generateUserID() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(10000000, 99999999);
    userID = dis(gen);
}

void User::sendVerificationCode() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1000, 9999);
    verificationCode = std::to_string(dis(gen));
    std::cout << "Verification code sent to email: " << verificationCode << std::endl;
}

void User::addFriend(const std::string& friendUsername) {
    if (std::find(friends.begin(), friends.end(), friendUsername) == friends.end()) {
        friends.push_back(friendUsername);
        std::cout << "User " << friendUsername << " added to friends." << std::endl;
    } else {
        std::cout << "User " << friendUsername << " is already in your friends list." << std::endl;
    }
}

void User::removeFriend(const std::string& friendUsername) {
    auto it = std::find(friends.begin(), friends.end(), friendUsername);
    if (it != friends.end()) {
        friends.erase(it);
        std::cout << "User " << friendUsername << " removed from friends." << std::endl;
    } else {
        std::cout << "User " << friendUsername << " is not in your friends list." << std::endl;
    }
}

void User::viewProfile() const {
    std::cout << "Username: " << username << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Gender: " << gender << std::endl;
    std::cout << "Interests: ";
    for (const std::string& interest : interests) {
        std::cout << interest << " ";
    }
    std::cout << std::endl;
    std::cout << "Friends: ";
    for (const std::string& friendName : friends) {
        std::cout << friendName << " ";
    }
    std::cout << std::endl;
}
