#include "../include/tictactoe.hpp"

// Global variables definition
std::string grid[3][3]; // Game grid
std::string symbols[2] = {"O", "X"}; // Symbols for players
std::string playerSymbol = ""; // Player's chosen symbol
std::string compSymbol = ""; // Computer's symbol
std::string winner = ""; // Winner of the game
std::vector<int> playerInputs; // Stores player's moves
std::vector<int> compInputs; // Stores computer's moves
unsigned playerCount = 0; // Counts player's moves

// Function definitions
void initializeGame() {
    // Display the initial positions using tempGrid
    std::string tempGrid[3][3] = {
        {"A1","A2","A3"},
        {"B1","B2","B3"},
        {"C1","C2","C3"}
    };
    // Initialize the grid to be empty
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            grid[i][j] = " ";
        }
    }
    // Display the initial tempGrid
    std::cout << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "|";
        for (int j = 0; j < 3; ++j) {
            std::cout << " " << tempGrid[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
}

void displayGrid() {
    // Display the current game grid
    std::cout << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "|";
        for (int j = 0; j < 3; ++j) {
            std::cout << " " << grid[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
}

void selectSymbol() {
    // Prompt player to select a symbol
    std::cout << "Select your symbol ('O' or 'X'): ";
    std::cin >> playerSymbol;

    if (playerSymbol == symbols[0]) {
        compSymbol = symbols[1];
        std::cout << "Computer symbol: '" << symbols[1] << '\'' << std::endl;
    } else if (playerSymbol == symbols[1]) {
        compSymbol = symbols[0];
        std::cout << "Computer symbol: '" << symbols[0] << '\'' << std::endl;
    } else {
        // If invalid input, prompt again
        std::cout << "Enter either '" << symbols[0] << "' or '" << symbols[1] 
                  << "' (uppercase)" << std::endl << std::endl;
        selectSymbol();
    }
}

void playerTurn() {
    // Player's turn to choose a position
    int position = -1;
    std::string rawInput = "";

    while (position == -1) {
        std::cout << "Enter valid position (e.g A1): ";
        std::cin >> rawInput;
        position = mapRawInput(rawInput);
    }
    setPlayerPosition(position);
}

int mapRawInput(const std::string &in) {
    // Map the raw input to a grid position number
    if (in == "A1") return 1;
    if (in == "A2") return 2;
    if (in == "A3") return 3;
    if (in == "B1") return 4;
    if (in == "B2") return 5;
    if (in == "B3") return 6;
    if (in == "C1") return 7;
    if (in == "C2") return 8;
    if (in == "C3") return 9;

    std::cout << "Enter valid position corresponding to the grid (e.g. A1)" << std::endl;
    return -1; // Return -1 if input is invalid
}

void setPosition(const int &position, const std::string &symbol) {
    // Set the position on the grid with the specified symbol
    switch (position) {
        case 1: grid[0][0] = symbol; break;
        case 2: grid[0][1] = symbol; break;
        case 3: grid[0][2] = symbol; break;
        case 4: grid[1][0] = symbol; break;
        case 5: grid[1][1] = symbol; break;
        case 6: grid[1][2] = symbol; break;
        case 7: grid[2][0] = symbol; break;
        case 8: grid[2][1] = symbol; break;
        case 9: grid[2][2] = symbol; break;
    }
}

void setPlayerPosition(const int &pos) {
    // Set the player's position if it hasn't been taken
    if (playerCount == 0 || (std::count(playerInputs.cbegin(), playerInputs.cend(), pos) == 0 
        && std::count(compInputs.cbegin(), compInputs.cend(), pos) == 0)) {
        playerInputs.push_back(pos);
        ++playerCount;
        setPosition(pos, playerSymbol);
    } else {
        // If position already taken, prompt again
        std::cout << "Position already picked. Try again." << std::endl;
        playerTurn();
    }
}

void compTurn() {
    // Computer's turn to choose a position
    int randPos;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 9);

    // Generate a random position that hasn't been taken
    do {
        randPos = distribution(generator); 
    } while (std::count(playerInputs.cbegin(), playerInputs.cend(), randPos) > 0
        || std::count(compInputs.cbegin(), compInputs.cend(), randPos) > 0);

    compInputs.push_back(randPos);
    setPosition(randPos, compSymbol);
}

bool isWinningLine(const std::string &a, const std::string &b, const std::string &c) {
    // Check if three symbols in a row are the same and not empty
    return (a == b && b == c && c != " ");
}

bool gameOver() {
    // Check for rows
    for (int i = 0; i < 3; ++i) {
        if (isWinningLine(grid[i][0], grid[i][1], grid[i][2])) {
            winner = (grid[i][0] == symbols[0]) ? "Computer" : "Player";
            return true;
        }
    }
    // Check for columns
    for (int i = 0; i < 3; ++i) {
        if (isWinningLine(grid[0][i], grid[1][i], grid[2][i])) {
            winner = (grid[0][i] == symbols[0]) ? "Computer" : "Player";
            return true;
        }
    }
    // Check diagonals
    if (isWinningLine(grid[0][0], grid[1][1], grid[2][2])
        || isWinningLine(grid[0][2], grid[1][1], grid[2][0])) {
        winner = (grid[1][1] == symbols[0]) ? "Computer" : "Player";
        return true;
    }
    // Check for draws
    if (playerCount == 5 && winner == "") {
        winner = "None";
        return true;
    }
    return false;
}