#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>

struct Player {
    std::string name;
    int id;
    bool isAlive;
};

#endif