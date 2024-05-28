#include "usermanager.hpp"

int main() {
    UserManager userManager;
    userManager.loadUsersFromFile("users.txt");
    userManager.mainMenu();
    userManager.saveUsers("users.txt");
    return 0;
}
