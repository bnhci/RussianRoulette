#include "game.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <random>
#include <iomanip>
#include <windows.h>
#include <conio.h>

Player* player = nullptr;
Revolver* revolver = nullptr;
bool isGameStart = false;
int playerCount{};
int aliveCount{};

void waitingCommand() {
    std::string command{};
    command = getLimitedInput(5);

    if (!isGameStart) {
        if (command == "start") {
            startGame();
        }
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
    system("chcp 1251 > nul");
    system("cls");

    setlocale(LC_ALL, "Russian");
    system("cls");
    std::cout << "РУССКАЯ РУЛЕТКА\n"
        << "Для начаал игры введите start\n"
        << "Для выхода введите q\n";
    waitingCommand();
}

void startGame() {
    std::string name{};
    std::cout << "Введите кол-во игроков (максимум 10): ";
    std::cin >> playerCount;
    aliveCount = playerCount;

    while (playerCount > 10 || playerCount < 2) {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "Максимум 10!!!! И не меньше 2!!!!\n";
        std::cin >> playerCount;
    }

    std::cout << "Введённое кол-во игрококв: " << std::to_string(playerCount) << std::endl;
    player = new Player[playerCount];
    std::cout << "Введите имя каждому игроку (для подтверждения имени требуется нажaть ENTER):\n";

    for (int i = 0; i < playerCount; i++) {
        name = getLimitedInput(10);
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
    gamePlay();
}

void gamePlay() {
    bool flag{ true };

    while (flag) {
        for (int i = 0; i < playerCount; i++) {
            while (!player[i].isAlive) {
                if (playerCount - 1 == i)
                    i = 0;
                else
                    i++;
            }

            printGame(i);

        checkEnter:
            if (isEnterPressed())
                shot(i);
            else
                goto checkEnter;

            if (aliveCount == 1) {
                flag = false;
                gameOver();
            }

            Sleep(1500);
        }
    }
}

void gameOver() {
    system("cls");
    std::cout << "Победитель: " << player[findWinner()].name << std::endl
        << "Для продолжения игры нажмите любую клавишу\n"
        << "Для выхода из игры нажмите Enter";

    if (isEnterPressed()) {
        deletePlayers();
        deleteRevolver();
        title();
    }
    else {
        deleteRevolver();

        for (int i = 0; i < playerCount; i++)
            player[i].isAlive = true;

        aliveCount = playerCount;
        startRound();
    }
}

void shot(int playerIndex) {
    int randomBullet = rand() % 6;

    if (randomBullet == revolver->currentPosition) {
        std::cout << "ВЫСТРЕЛ\n";
        player[playerIndex].isAlive = false;
        aliveCount--;
        Beep(revolver->sound + 1000, 100);
    }
    else {
        std::cout << "ОСЕЧКА\n";
        Beep(revolver->sound, 100);
    }
}

int findWinner() {
    for (int i = 0; i < playerCount; i++)
        if (player[i].isAlive)
            return i;
    return -1; // Добавлен return для всех путей выполнения
}

void initPlayer(std::string name, int id) {
    player[id].name = name;
    player[id].id = id;
    player[id].isAlive = true;
}

void initRevolver() {
    int combatBullet = rand() % 6;
    revolver->currentPosition = combatBullet;
    revolver->sound = rand() % 2000;
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
    system("cls");

    for (int i = 0; i < playerCount; i++) {
        if (player[i].isAlive) {
            if (i == playerIndex)
                std::cout << player[i].name << " <<<\n";
            else
                std::cout << player[i].name << std::endl;
        }
        else {
            std::cout << "{ " << player[i].name << " }\n";
        }
    }
}