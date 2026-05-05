#include "game.h"
#include "fileManager.h"
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
        else if (command == "lb") {
            printLB();
        }
        else {
            std::cout << "Неверная комманда\n";
            waitingCommand();
        }
    }
}

void title() {
    setlocale(LC_ALL, "Russian");
    system("cls");
    std::cout << "RUSSIAN ROULETTE\n"
        << "To start the game, enter start\n"
        << "To open leaderBoard, enter lb\n"
        << "To exit, enter q\n";
    waitingCommand();
}

void startGame() {
    std::string name{};
    std::cout << "Enter the number of players (maximum 10): ";
    std::cin >> playerCount;
    aliveCount = playerCount;

    while (playerCount > 10 || playerCount < 2) {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "Maximum 10!!!! And not less than 2!!!!\n";
        std::cin >> playerCount;
    }

    std::cout << "Number of players entered: " << std::to_string(playerCount) << std::endl;
    player = new Player[playerCount];
    std::cout << "Enter a name for each player (press ENTER to confirm the name):\n";

    for (int i = 0; i < playerCount; i++) {
        name = getLimitedInput(10);
        initPlayer(name, i);
    }

    std::cout << "Loading game";

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
    std::cout << "Winner: " << player[findWinner()].name << std::endl
        << "Press any key to continue the game\n"
        << "Press Enter to exit the game";

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
        std::cout << "SHOT\n";
        player[playerIndex].isAlive = false;
        aliveCount--;
        Beep(revolver->sound + 1000, 100);
    }
    else {
        std::cout << "CLICK\n";
        Beep(revolver->sound, 100);
    }
}

int findWinner() {
    for (int i = 0; i < playerCount; i++)
        if (player[i].isAlive)
            return i;
    return -1;
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

void printLB() {
    system("cls");
    std::string* leaderBoard = readFile();
    int count = getCountLine();

    if (leaderBoard == nullptr || count == 0) {
        std::cout << "Leaderboard is empty!\n";
        Sleep(2000);
        title();
        return;
    }

    for (int i = 0; i < count; i++) {
        std::string name{};
        std::string score{};

        // Парсим "Имя\tСчет"
        int tabPos = leaderBoard[i].find('\t');

        if (tabPos != std::string::npos) {
            name = leaderBoard[i].substr(0, tabPos);
            score = leaderBoard[i].substr(tabPos + 1);
        }
        else {
            name = leaderBoard[i];
            score = "0";
        }

        std::cout << (i + 1) << ". " << name << ": " << score << std::endl;
    }

    Sleep(3000);
    title();
}