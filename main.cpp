#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm> // For std::find

using namespace std;

class User {
public:
    string username;
    string password;
    string email;
    int age;
    string gender;
    vector<string> interests;
    vector<string> friends; // Vector for storing friend names

    void addFriend(const string& friendUsername) {
        if (find(friends.begin(), friends.end(), friendUsername) == friends.end()) {
            friends.push_back(friendUsername);
            cout << "Пользователь " << friendUsername << " добавлен в друзья." << endl;
        } else {
            cout << "Пользователь " << friendUsername << " уже в списке друзей." << endl;
        }
    }

    void removeFriend(const string& friendUsername) {
        auto it = find(friends.begin(), friends.end(), friendUsername);
        if (it != friends.end()) {
            friends.erase(it);
            cout << "Пользователь " << friendUsername << " удален из друзей." << endl;
        } else {
            cout << "Пользователь " << friendUsername << " не найден в списке друзей." << endl;
        }
    }

    void viewProfile() const {
        cout << "Имя пользователя: " << username << endl;
        cout << "Email: " << email << endl;
        cout << "Возраст: " << age << endl;
        cout << "Пол: " << gender << endl;
        cout << "Интересы: ";
        for (const string& interest : interests) {
            cout << interest << " ";
        }
        cout << endl;
        cout << "Друзья: ";
        for (const string& friendName : friends) {
            cout << friendName << " ";
        }
        cout << endl;
    }
};

class UserManager {
private:
    vector<User> users;

public:
    void loadUsersFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
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

                pos = line.find(",");
                user.age = stoi(line.substr(0, pos));
                line.erase(0, pos + 1);

                pos = line.find(",");
                user.gender = line.substr(0, pos);
                line.erase(0, pos + 1);

                while ((pos = line.find(",")) != string::npos) {
                    user.interests.push_back(line.substr(0, pos));
                    line.erase(0, pos + 1);
                }
                user.interests.push_back(line); // Last interest

                users.push_back(user);
            }
            file.close();
        }
    }

    void saveUserToFile(const User& user, const string& filename) {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << user.username << "," << user.password << "," << user.email << ","
                 << user.age << "," << user.gender;
            for (const string& interest : user.interests) {
                file << "," << interest;
            }
            file << endl;
            file.close();
        } else {
            cerr << "Не удалось открыть файл для записи." << endl;
        }
    }

    void registerUser() {
        User newUser;

        cout << "Введите имя пользователя: ";
        getline(cin, newUser.username);

        string password;
        while (true) {
            cout << "Введите пароль: (не менее 8 символов): ";
            getline(cin, password);
            if (password.length() >= 8) {
                newUser.password = password;
                break;
            } else {
                cout << "Пароль должен быть не короче 8 символов." << endl;
            }
        }

        cout << "Введите email: ";
        string email;
        while (true) {
            getline(cin, email);
            if (email.find("@mail") != string::npos ||
                email.find("@gmail") != string::npos ||
                email.find("@yandex") != string::npos) {
                newUser.email = email;
                break;
            } else {
                cout << "Email должен содержать одну из директив: @mail, @gmail, @yandex. Попробуйте еще раз: ";
            }
        }

        cout << "Введите возраст: ";
        cin >> newUser.age;
        cin.ignore(); // Игнорируем символ новой строки

        cout << "Введите пол (мужчина/женщина): ";
        string gender;
        while (true) {
            getline(cin, gender);
            if (gender == "Муж" || gender == "Жен" || gender == "М" || gender == "Ж" || gender == "мужчина" || gender == "женщина") {
                newUser.gender = gender;
                break;
            } else {
                cout << "Некорректный пол. Введите 'мужчина' или 'женщина': ";
            }
        }

        cout << "Введите интересы через запятую: ";
        string interests;
        getline(cin, interests);
        size_t pos = 0;
        while ((pos = interests.find(",")) != string::npos) {
            newUser.interests.push_back(interests.substr(0, pos));
            interests.erase(0, pos + 1);
        }
                            
                            newUser.interests.push_back(interests); // Last interest

                            users.push_back(newUser);
                            saveUserToFile(newUser, "users.txt");

                            cout << "Регистрация успешна!" << endl;
                        }

                        void login() {
                            string username, password;

                            cout << "Введите имя пользователя: ";
                            getline(cin, username);

                            cout << "Введите пароль: ";
                            getline(cin, password);

                            for (User& user : users) {
                                if (user.username == username && user.password == password) {
                                    cout << "Вход успешно выполнен!" << endl;
                                    userMenu(user);
                                    return;
                                }
                            }

                            cout << "Неверное имя пользователя или пароль." << endl;
                        }

                        void userMenu(User& currentUser) {
                            int choice;
                            do {
                                cout << "1. Найти пользователя по имени" << endl;
                                cout << "2. Добавить друга" << endl;
                                cout << "3. Посмотреть профиль" << endl;
                                cout << "0. Выйти" << endl;
                                cout << "Выберите действие: ";
                                cin >> choice;
                                cin.ignore();

                                switch (choice) {
                                    case 1:
                                        findUserByName();
                                        break;
                                    case 2:
                                        addFriend(currentUser);
                                        break;
                                    case 3:
                                        currentUser.viewProfile();
                                        break;
                                    case 0:
                                        cout << "Выход из меню пользователя..." << endl;
                                        break;
                                    default:
                                        cout << "Неверный выбор. Попробуйте еще раз." << endl;
                                        break;
                                }
                            } while (choice != 0);
                        }

                        void findUserByName() {
                            string name;
                            cout << "Введите имя пользователя: ";
                            getline(cin, name);

                            for (const User& user : users) {
                                if (user.username == name) {
                                    cout << "Пользователь найден!" << endl;
                                    user.viewProfile();
                                    return;
                                }
                            }

                            cout << "Пользователь с таким именем не найден." << endl;
                        }

                        void addFriend(User& currentUser) {
                            string friendUsername;
                            cout << "Введите имя пользователя, которого хотите добавить в друзья: ";
                            getline(cin, friendUsername);

                            for (User& user : users) {
                                if (user.username == friendUsername) {
                                    currentUser.addFriend(friendUsername);
                                    return;
                                }
                            }

                            cout << "Пользователь с таким именем не найден." << endl;
                        }

                        void findPeople() {
                            cout << "Теперь вы можете найти людей." << endl;
                            cout << "Выберите категорию для поиска: " << endl;
                            cout << "1 - По интересам, 2 - По возрасту, 3 - По имени: " << endl;
                            int choice;
                            cin >> choice;
                            cin.ignore(); // Игнорируем символ новой строки

                            switch (choice) {
                                case 1:
                                    findUsersWithHobby();
                                    break;
                                case 2:
                                    findUsersWithAge();
                                    break;
                                case 3:
                                    findUserByName();
                                    break;
                                default:
                                    cout << "Неверный выбор." << endl;
                                    break;
                            }
                        }

                        void findUsersWithHobby() {
                            string hobby;
                            cout << "Введите интересующее хобби: ";
                            getline(cin, hobby);

                            for (const User& user : users) {
                                if (find(user.interests.begin(), user.interests.end(), hobby) != user.interests.end()) {
                                    cout << "Пользователь: " << user.username << endl;
                                }
                            }
                        }

                        void findUsersWithAge() {
                            int age;
                            cout << "Введите интересующий возраст: ";
                            cin >> age;
                            cin.ignore();

                            for (const User& user : users) {
                                if (user.age == age) {
                                    cout << "Пользователь: " << user.username << endl;
                                }
                            }
                        }

                        void viewAllUsers() {
                            ifstream file("users.txt");
                            if (file.is_open()) {
                                string line;
                                while (getline(file, line)) {
                                    cout << line << endl; // Output user information
                                }
                                file.close();
                            } else {
                                cerr << "Не удалось открыть файл с пользователями." << endl;
                            }
                        }

                        void deleteUser(const string& username) {
                            auto it = remove_if(users.begin(), users.end(), [&](const User& user) { return user.username == username; });
                            if (it != users.end()) {
                                users.erase(it, users.end());
                                cout << "Пользователь удален." << endl;
                                // Rewrite users file
                                ofstream file("users.txt");
                                if (file.is_open()) {
                                    for (const User& user : users) {
                                        saveUserToFile(user, "users.txt");
                                    }
                                    file.close();
                                }
                            } else {
                                cout << "Пользователь не найден." << endl;
                            }
                        }

                        void adminMenu() {
                            int choice;
                            string username; // Declare username variable outside the switch block

                            cout << "1. Удалить пользователя" << endl;
                            cout << "Выберите действие: ";
                            cin >> choice;
                            cin.ignore(); // Игнорируем символ новой строки

                            switch (choice) {
                                case 1:
                                    cout << "Введите имя пользователя для удаления: ";
                                    getline(cin, username);
                                    deleteUser(username);
                                    break;
                                default:
                                    cout << "Неверный выбор. Попробуйте еще раз." << endl;
                                    break;
                            }
                        }
                    };

int main() {
    UserManager userManager;
    userManager.loadUsersFromFile("users.txt");
    int choice;

    do {
        cout << "1. Регистрация" << endl;
        cout << "2. Вход" << endl;
        cout << "3. Найти людей" << endl;
        cout << "4. Просмотреть всех пользователей" << endl;
        cout << "5. Админ-меню" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore(); // Игнорируем символ новой строки

        switch (choice) {
            case 1:
                userManager.registerUser();
                break;
            case 2:
                userManager.login();
                break;
            case 3:
                userManager.findPeople();
                break;
            case 4:
                userManager.viewAllUsers();
                break;
            case 5:
                userManager.adminMenu();
                break;
            case 0:
                cout << "Выход из приложения..." << endl;
                break;
            default:
                cout << "Неверный выбор. Попробуйте еще раз." << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
