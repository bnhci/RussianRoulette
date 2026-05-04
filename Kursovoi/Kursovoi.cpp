#include "game.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

int main() {

    system("chcp 1251 > nul");
    system("cls");

    setlocale(LC_ALL, "Russian");    
    srand(time(NULL));
    title();
}