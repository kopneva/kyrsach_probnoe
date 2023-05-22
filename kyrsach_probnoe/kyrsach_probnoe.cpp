#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <windows.h>

using namespace std;

struct Player {
    string name;
    string surname;
    string position;
    int goals_scored;
    int penalty_minutes;
};

vector<Player> players;
struct User {
    string login;
    string password;
    string role;
};

vector<User> users;

void savePlayersToFile() {
    ofstream file("players.txt");
    if (file.is_open()) {
        for (Player player : players) {
            file << player.name << "," << player.surname << "," << player.position << "," << player.goals_scored << "," << player.penalty_minutes << std::endl;
        }
        file.close();
    }
}

void loadPlayersFromFile() {
    ifstream file("players.txt");
    if (file.is_open()) {
        string name, surname, position, goalsscoredstr, penaltyminutesstr;
        int goalsscored, penaltyminutes;
        while (file >> name >> surname >> position >> goalsscored >> penaltyminutes) {
            players.push_back({ name, surname, position, goalsscored, penaltyminutes });
        }
        file.close();
    }
}

void saveUsersToFile() {
    ofstream file("users.txt");
    if (file.is_open()) {
        for (User user : users) {
            file << user.login << "," << user.password << "," << user.role << endl;
        }
        file.close();
    }
}

void loadUsersFromFile() {
    ifstream file("users.txt");
    if (file.is_open()) {
        string login, password, role;
        while (file >> login >> password >> role) {
            users.push_back({ login, password, role });
        }
        file.close();
    }
}


void registerUser() {
    cout << "Пожалуйства,введите логин: ";
    string login;
    cin >> login;
    for (User user : users) {
        if (user.login == login) {
            cout << "Пользователь с таким логином уже существует,введите другой" << endl;
            return;
        }
    }
    cout << "Пожалуйства,введите пароль: ";
    string password;
    cin >> password;
    cout << "Пожалуйста,выберите свою роль (user/admin): ";
    string role;
    cin >> role;
    users.push_back({ login, password, role });
    saveUsersToFile();
    cout << "Регистрация прошла успешна!" << endl;
}

User* loginUser() {
    cout << "Пожалуйства,введите свой логин: ";
    string login;
    cin >> login;
    cout << "Пожалуйства,введите свой пароль: ";
    string password;
    cin >> password;
    for (User& user : users) {
        if (user.login == login && user.password == password) {
            return &user;
        }
    }
    cout << "Пользователь не найден.Пожалуйста,зарегестрируйтесь." << endl;
    return nullptr;
}

void addPlayer() {
    Player player;
    cout << "Введите имя игрока: ";
    cin >> player.name;
    cout << "Введите фамилию игрока: ";
    cin >> player.surname;
    cout << "Ведите позицию игрока: ";
    cin >> player.position;
    cout << "Введите количество голов забитых игроком: ";
    cin >> player.goals_scored;
    cout << "Введите количество штрафных минут игрока: ";
    cin >> player.penalty_minutes;
    players.push_back(player);
    savePlayersToFile();
    cout << "Игрок успешно добавлен!" << endl;
}

void editPlayer() {
    string fullName;
    cout << "Введите имя и фамилию игрока,которого вы хотите отредактировать: ";
    getline(cin, fullName);
    string searchname = fullName.substr(0, fullName.find(' '));
    string searchsurname = fullName.substr(fullName.find(' ') + 1);
    for (int i = 0; i < players.size(); i++) {
        if (players[i].name == searchname && players[i].surname == searchsurname) {
            cout << "Введите новую позицию игрока: ";
            cin >> players[i].position;
            cout << "Введите новое количество голов,забитых игроком: ";
            cin >> players[i].goals_scored;
            cout << "Введите новое количество штрафных минут  грока: ";
            cin >> players[i].penalty_minutes;
            savePlayersToFile();
            cout << "Данные игрока отредактированы успешно!" << endl;
            return;
        }
    }
    cout << "Player not found." << endl;
}

void deletePlayer() {
    string name;
    cout << "Введите имя игрока,которого вы хотите удалить: ";
    cin >> name;
    for (int i = 0; i < players.size(); i++) {
        if (players[i].name == name) {
            players.erase(players.begin() + i);
            savePlayersToFile();
            cout << "Игрок удалён успешно!" << endl;
            return;
        }
    }
    cout << "Игрок не найден." << endl;
}

void displayPlayers() {
    cout << "| " << setw(15) << left << "Player Name" << " | "
        << setw(15) << left << "Player Surname" << " | "
        << setw(15) << left << "Position" << " | "
        << setw(8) << right << "Goals Scored" << " | "
        << setw(8) << right << "Penalty Minutes" << " |" << endl;
    cout << "|-----------------|-----------------|-----------------|--------------|-----------------|" << endl;

    for (int i = 0; i < players.size(); i++) {
        cout << "| " << setw(15) << left << players[i].name << " | "
            << setw(15) << left << players[i].surname << " | "
            << setw(15) << left << players[i].position << " | "
            << setw(8) << right << players[i].goals_scored << " | "
            << setw(8) << right << players[i].penalty_minutes << " |" << endl;
    }
}


void searchPlayer() {
    string name;
    cout << "Введите имя игрока,которого вы хотите найти: ";
    cin >> name;
    for (int i = 0; i < players.size(); i++) {
        if (players[i].name == name) {
            cout << "Игрок найден!" << endl;
            cout << "Player Name\tPlayer Surame\tPosition\tGoals Scored\tPenalty Minutes" << endl;
            cout << players[i].name << "\t" << players[i].surname <<"\t" << players[i].position << "\t" << players[i].goals_scored << "\t\t" << players[i].penalty_minutes << endl;
            return;
        }
    }
    cout << "Игрок не найден." << endl;
}

bool compareByGoals(const Player& a, const Player& b) {
    return a.goals_scored > b.goals_scored;
}

bool compareByPenaltyMinutes(const Player& a, const Player& b) {
    return a.penalty_minutes > b.penalty_minutes;
}

bool compareByName(const Player& a, const Player& b) {
    return a.name < b.name;
}
bool compareBySurname(const Player& a, const Player& b) {
    return a.surname < b.surname;
}

void sortPlayers() {
    int choice;
    cout << "По каким данным вы хотите отсортировать игроков?" << endl;
    cout << "1. По забитым голам" << endl;
    cout << "2. По штрафным минутам" << endl;
    cout << "3. По имени" << endl;
    cout << "4. По фамилии" << endl;
    cin >> choice;
    switch (choice) {
    case 1:
        sort(players.begin(), players.end(), compareByGoals);
        cout << "Игроки отсортированы по голам:" << endl;
        displayPlayers();
        break;
    case 2:
        sort(players.begin(), players.end(), compareByPenaltyMinutes);
        cout << "Игроки отсортированы по штрафным минутам:" << endl;
        displayPlayers();
        break;
    case 3:
        sort(players.begin(), players.end(), compareByName);
        cout << "Игроки отсортированы по имени:" << endl;
        displayPlayers();
        break;
    case 4:
        sort(players.begin(), players.end(), compareBySurname);
        cout << "Игроки отсортированы по фамилии:" << endl;
        displayPlayers();
        break;
    default:
        cout << "Неверный выбор." << endl;
        break;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    loadPlayersFromFile();
    loadUsersFromFile();
    int choice;
    bool isRunning = true;
    while (isRunning) {
        cout << "Пожалуйста,выберите опцию:" << endl;
        cout << "1. Зарегистрироваться" << endl;
        cout << "2. Войти в систему" << endl;
        cout << "3. Выйти" << endl;
        int option;
        cin >> option;
        switch (option) {
        case 1:
            registerUser();
            break;
        case 2: {
            User* user = loginUser();
            if (user != nullptr) {
                cout << "Вход в систему прошёл успешно!Добро пожаловать в программу учёта сведений об игроках хоккейной команды) " << user->login << "!" << endl;
                bool isLoggedIn = true;
                while (isLoggedIn) {
                    cout << "Пожалуйства,выберите опцию:" << endl;
                    if (user->role == "admin") {
        cout << "1. Добавить игрока" << endl;
        cout << "2. Отредактировать данные игрока" << endl;
        cout << "3. Удалить игрока" << endl;
        cout << "4. Поиск игрока" << endl;
        cout << "5. Посмотреть список игроков" << endl;
        cout << "6. Сортировка игроков" << endl;
        cout << "7. Выход из системы" << endl;
    int option; cin >> option;
        switch (option) {
        case 1:
            addPlayer();
        break; 
        case 2:
            editPlayer();
            break;
        case 3:
            deletePlayer();
            break; 
        case 4: 
            searchPlayer();
            break;
        case 5: 
            displayPlayers();
            break; 
        case 6:
            sortPlayers();
            break; 
        case 7: 
            cout << "Выход из системы заыершён успешно!" << endl;
            return 0;
            default: cout << "Неверный выбор." << endl;
                  break;
                  }
             }
 else if (user->role == "user") {
        cout << "1. Поиск игрока" << endl;
        cout << "2. Посмотреть список игроков" << endl;
        cout << "3. Сортировка игроков" << endl;
        cout << "4. Выход из системы" << endl;
    int option;
        cin >> option;
        switch (option) {
        case 1:
            searchPlayer();
            break;
        case 2: 
            displayPlayers();
            break;
        case 3:
            sortPlayers();
            break;
        case 4:
            cout << "Выход из системы завершён успешно!" << endl;
        return 0;
        default:
            cout << "Неверный выбор." << endl; break;
                  }
            }
 else {
     cout << "У вас нет разрешения на выполнение этого действия" << endl;
     isLoggedIn = false;
                }
             }
        }
 break;
        } 
        case 3:
     isRunning = false;
     break;
        default: 
     cout << "Неверный выбор." << endl;
     break; 
        } 
    }
    savePlayersToFile();
    saveUsersToFile();
    return 0;
}
