#include <iostream>
#include <string>
#include <random>
#include <iomanip>
#include <windows.h>
#include <conio.h>

struct Player {
    std::string name;
    int id;
    bool isAlive;
};

struct Revolver {
    int chambers[6];        // 0 - пусто, 1 - патрон
    int currentPosition;    // текущая позиция барабана
};

Player* player = nullptr;
Revolver* revolver = nullptr;

bool isGameStart = false;
int playerCount{};
int aliveCount{};

std::string getLimitedInput(int maxLength);

void waitingCommand();

void title();
void startGame();
void startRound();
void gamePlay();
void gameOver();

void shot(int playerIndex);

int findWinner();

void initPlayer(std::string name, int id);
void initRevolver();

void deleteStructure();
void deletePlayers();
void deleteRevolver();

void printGame(int playerIndex);

bool isEnterPressed();


int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    title();

}

std::string getLimitedInput(int maxLength) {
    std::string input;
    char ch;

    while (true) {
        ch = _getch();

        if (ch == '\r') {
            std::cout << std::endl;
            break;
        }
        else if (ch == '\b') {
            if (!input.empty()) {
                std::cout << "\b \b";
                input.pop_back();
            }
        }
        else if (input.length() < maxLength && isprint(ch)) {
            input += ch;
            std::cout << ch;
        }
    }

    return input;
}

void waitingCommand() {
    std::string command{};
    command = getLimitedInput(5);
    if (!isGameStart) {
        if (command == "start")
            startGame();

        else if (command == "q") {
            deletePlayers();
            deleteRevolver();
            std::quick_exit(0);
        }
        else {
            std::cout << "Неверная комманда\n";
            waitingCommand();
        }
    }
}

void title() {
    system("cls");
    std::cout << "РУССКАЯ РУЛЕТКА\n" << "Для начаал игры введите start\n" << "Для выхода введите q\n";
    waitingCommand();
}

void startGame() {
    std::string name{};
    std::cout << "Введите кол-во игроков (максимум 10): ";
    std::cin >> playerCount;
    aliveCount = playerCount;
    while (playerCount > 10) {
        std::cout << "Максимум 10!!!!\n";
        std::cin >> playerCount;
    }
    std::cout << "Введённое кол-во игрококв: " << std::to_string(playerCount) << std::endl;
    player = new Player[playerCount];
    std::cout << "Введите имя каждому игроку (для подтверждения имени требуется нажaть ENTER):\n";
    for (int i = 0; i < playerCount; i++) {
        std::cin >> name;
        initPlayer(name, i);
    }

    std::cout << "Загрузка игры";

    for (int i = 0; i < 5; i++) {
        std::cout << ".";
        Sleep(500);
    }


    startRound();
}

void startRound() {
    system("cls");

    revolver = new Revolver;
    initRevolver();


    for (int i = 0; i < playerCount; i++) {
        if (i == 0)
            std::cout << player[i].name << " <<<\n";
        else
            std::cout << player[i].name << "\n";
    }

    gamePlay();

}

void gamePlay() {

    for (int i = 0; i < playerCount; i++) {

        printGame(i);

        checkEnter:
        if (isEnterPressed())
            shot(i);
        else
            goto checkEnter;

        if (aliveCount == 1)
            gameOver();

            
        Sleep(1500);

    }
}

void gameOver() {
    system("cls");
    std::cout << "Победитель: " << findWinner() << std::endl <<
        "Для продолжения игры нажмите любую клавишу\n" <<
        "Для выхода из игры нажмите Enter";

    if (isEnterPressed) {

        deletePlayers();
        deleteRevolver();
        title();

    }
    else {
        deleteRevolver();

        for (int i = 0; i < playerCount; i++)
            player[i].isAlive = true;

        startRound();

    }
}

void shot(int playerIndex) {

    int randomBullet = rand() % 7;

    if (randomBullet == revolver->currentPosition) {

        std::cout << "ВЫСТРЕЛ\n";
        player[playerIndex].isAlive = false;
        aliveCount--;

    }
    else
        std::cout << "ОСЕЧКА\n";
    
}

int findWinner() {

    for (int i = 0; i < playerCount; i++)
        if (player[i].isAlive)
            return i;
    
}


void initPlayer(std::string name, int id) {
    player[id].name = name;
    player[id].id = id;
    player[id].isAlive = true;
}

void initRevolver() {
    int combatBullet = rand() % 7;
    for (int i = 0; i < 6; i++) {
        if (i == combatBullet)
            revolver->chambers[i] = 1;
        revolver->chambers[i] = 0;
    }
}

void deletePlayers() {
    delete[] player;
    player = nullptr;
}

void deleteRevolver() {
    delete revolver;
    revolver = nullptr;
}

void printGame(int playerIndex) {

    for (int i = 0; i < playerCount; i++) {

        if (player[i].isAlive) {

            if (i == playerIndex)
                std::cout << player[i].name << " <<<\n";
            else
                std::cout << player[i].name << std::endl;

        }
        else
            std::cout << "{ " << player[i].name << " }\n";

    }

}

bool isEnterPressed() {

    while (true) {
        int key = _getch();
        if (key == 13)
            return true;
        else
            return false;
    }

}

