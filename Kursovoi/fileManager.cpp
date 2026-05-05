#include <iostream>
#include <fstream>
#include <string>

const std::string fileName = "F:\\prog\\C++ program\\Kursovoi\\Kursovoi\\laederBoard.txt";
int countLine = 0;
std::string* oldList = nullptr;

std::string* readFile() {
    countLine = 0;
    std::ifstream tableReference(fileName);

    if (!tableReference.is_open()) {
        std::cout << "close";
        return nullptr;
    }

    std::string line;
    while (std::getline(tableReference, line)) {
        countLine++;
    }


    if (countLine == 0) {
        tableReference.close();
        return nullptr;
    }

    oldList = new std::string[countLine];

    tableReference.clear();
    tableReference.seekg(0, std::ios::beg);

    for (int i = 0; i < countLine; i++) {
        std::getline(tableReference, line);
        oldList[i] = line;  // Сохраняем "Имя\tСчет"
    }

    tableReference.close();
    return oldList;
}

void writeFile(const std::string* name, const std::string* score, int size) {
    std::ofstream file(fileName, std::ios::trunc);

    for (int i = 0; i < size; i++) {
        // Формат: "Имя\tСчет"
        file << name[i] << "\t" << score[i] << "\n";
    }

    file.close();
    delete[] oldList;
    oldList = nullptr;
    countLine = 0;
}


int getCountLine() {
	return countLine;
}