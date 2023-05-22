#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct User {
    string login;
    string password;
    string role;
};

vector<User> users;

void registerUser() {
    cout << "Please enter your login: ";
    string login;
    cin >> login;
    for (User user : users) {
        if (user.login == login) {
            cout << "User with this login already exists" << endl;
            return;
        }
    }
    cout << "Please enter your password: ";
    string password;
    cin >> password;
    cout << "Please select your role (user/admin): ";
    string role;
    cin >> role;
    users.push_back({ login, password, role });
    cout << "Registration successful!" << endl;
}

User* loginUser() {
    cout << "Please enter your login: ";
    string login;
    cin >> login;
    cout << "Please enter your password: ";
    string password;
    cin >> password;
    for (User& user : users) {
        if (user.login == login && user.password == password) {
            return &user;
        }
    }
    cout << "User not found. Please register." << endl;
    return nullptr;
}

void viewInformation() {
    ifstream file("information.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
}

void addInformation() {
    ofstream file("information.txt", ios_base::app);
    if (file.is_open()) {
        cout << "Please enter the information you want to add: ";
        string information;
        cin.ignore();
        getline(cin, information);
        file << information << endl;
        file.close();
        cout << "Information added successfully" << endl;
    }
    else {
        cout << "Unable to open file" << endl;
    }
}

int main() {
    bool isRunning = true;
    while (isRunning) {
        cout << "Please select an option:" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        int option;
        cin >> option;
        switch (option) {
        case 1:
            registerUser();
            break;
        case 2: {
            User* user = loginUser();
            if (user != nullptr) {
                cout << "Login successful! Welcome, " << user->login << "!" << endl;
                bool isLoggedIn = true;
                while (isLoggedIn) {
                    cout << "Please select an option:" << endl;
                    if (user->role == "admin") {
                        cout << "1. Add information" << endl;
                    }
                    cout << "2. View information" << endl;
                    cout << "3. Logout" << endl;
                    int option;
                    cin >> option;
                    switch (option) {
                    case 1:
                        if (user->role == "admin") {
                            addInformation();
                        }
                        else {
                            cout << "You don't have permission to perform this action" << endl;
                        }
                        break;
                    case 2:
                        viewInformation();
                        break;
                    case 3:
                        isLoggedIn = false;
                        break;
                    default:
                        cout << "Invalid option" << endl;
                        break;
                    }
                }
            }
            break;
        }
        case 3:
            isRunning = false;
            break;
        default:
            cout << "Invalid option" << endl;
            break;
        }
    }
    return 0;
}