#pragma once
#ifndef GAME_H
#define GAME_H

#include "structs.h"

extern Player* player;
extern Revolver* revolver;
extern bool isGameStart;
extern int playerCount;
extern int aliveCount;

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
void deletePlayers();
void deleteRevolver();
void printGame(int playerIndex);
bool isEnterPressed();
std::string getLimitedInput(int maxLength);

void printLB();
void addScore();

#endif