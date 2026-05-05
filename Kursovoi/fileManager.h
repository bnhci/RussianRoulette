#pragma once
#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>

extern int countLine;
extern std::string* oldList;
extern const std::string fileName;

std::string* readFile();
void writeFile(const std::string* arr, const std::string* score, int size);
int getCountLine();
std::string* getList();


#endif
