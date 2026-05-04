#pragma once
#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

struct Player {
    std::string name;
    int id;
    bool isAlive;
};


struct Revolver {
    int currentPosition;
    int sound{ 0 };
};

#endif