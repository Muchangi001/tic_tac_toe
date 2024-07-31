#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

//global variables declaration
extern std::string grid[3][3];
extern std::string symbols[2];
extern std::string playerSymbol;
extern std::string compSymbol;
extern std::string winner;
extern std::vector<int> playerInputs;
extern std::vector<int> compInputs;
extern unsigned playerCount;

//functions declaration
int mapRawInput(const std::string &in);
void compTurn();
void playerTurn();
void displayGrid();
void selectSymbol();
void initializeGame();
void setPlayerPosition(const int &pos);
void setPosition(const int &position,const std::string &symbol);
bool gameOver();
bool isWinningLine(const std::string &a, const std::string &b, const std::string &c);

#endif