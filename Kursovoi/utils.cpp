#include "utils.h"
#include <iostream>
#include <conio.h>

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

bool isEnterPressed() {
    while (true) {
        int key = _getch();
        return (key == 13);
    }
}