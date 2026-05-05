#include "fileManager.h"
#include <fstream>

const std::string fileName = "leaderBoard.txt";
int countLine = 0;
std::string* oldList = nullptr;

std::string* readFile() {
    std::string bufferName{};
    std::string bufferScore{};
    countLine = 0;

    std::ifstream tableReference(fileName);
    
    if (!tableReference.is_open()) {
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
        oldList[i] = line;
    }

    tableReference.close();
    return oldList;
}

void writeFile(const std::string* name, const std::string* score, int size) {
	std::ofstream file(fileName, std::ios::trunc);

	for (int i = 0; i < size; i++) {
		file << (i + 1) << ". " << name[i] << "\t:\t" << score[i] << "\n";
	}

	file.close();

	delete[] oldList;
	oldList = nullptr;

}

int getCountLine() {
	return countLine;
}