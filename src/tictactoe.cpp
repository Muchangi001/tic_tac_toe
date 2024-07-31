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
    auto bestMove = findBestMove();
    int row = bestMove.first;
    int col = bestMove.second;

    if (row != -1 && col != -1) {
        grid[row][col] = compSymbol;
        int pos = row * 3 + col + 1;
        compInputs.push_back(pos);
    }
}

bool isWinningLine(const std::string &a, const std::string &b, const std::string &c) {
    // Check if three symbols in a row are the same and not empty
    return (a == b && b == c && c != " ");
}

bool gameOver() {
    // Check for rows
    for (int i = 0; i < 3; ++i) {
        if (isWinningLine(grid[i][0], grid[i][1], grid[i][2])) {
            winner = (grid[i][0] == compSymbol) ? "Computer" : "Player";
            return true;
        }
    }
    // Check for columns
    for (int i = 0; i < 3; ++i) {
        if (isWinningLine(grid[0][i], grid[1][i], grid[2][i])) {
            winner = (grid[0][i] == compSymbol) ? "Computer" : "Player";
            return true;
        }
    }
    // Check diagonals
    if (isWinningLine(grid[0][0], grid[1][1], grid[2][2])
        || isWinningLine(grid[0][2], grid[1][1], grid[2][0])) {
        winner = (grid[1][1] == compSymbol) ? "Computer" : "Player";
        return true;
    }
    // Check for draws
    if (playerCount == 5 && winner == "") {
        winner = "None";
        return true;
    }
    return false;
}

int evaluate() {
    // Evaluate rows
    for (int row = 0; row < 3; ++row) {
        if (grid[row][0] == grid[row][1] && grid[row][1] == grid[row][2]) {
            if (grid[row][0] == compSymbol)
                return +10;
            else if (grid[row][0] == playerSymbol)
                return -10;
        }
    }

    // Evaluate columns
    for (int col = 0; col < 3; ++col) {
        if (grid[0][col] == grid[1][col] && grid[1][col] == grid[2][col]) {
            if (grid[0][col] == compSymbol)
                return +10;
            else if (grid[0][col] == playerSymbol)
                return -10;
        }
    }

    // Evaluate diagonals
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
        if (grid[0][0] == compSymbol)
            return +10;
        else if (grid[0][0] == playerSymbol)
            return -10;
    }

    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
        if (grid[0][2] == compSymbol)
            return +10;
        else if (grid[0][2] == playerSymbol)
            return -10;
    }

    // If no one has won
    return 0;
}

bool isMovesLeft() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (grid[i][j] == " ")
                return true;
    return false;
}

int minimax(int depth, bool isMax) {
    int score = evaluate();

    // If the computer has won the game, return the evaluated score
    if (score == 10)
        return score;

    // If the player has won the game, return the evaluated score
    if (score == -10)
        return score;

    // If there are no more moves and no winner, then it is a tie
    if (!isMovesLeft())
        return 0;

    // If it is the maximizer's move (computer)
    if (isMax) {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                // Check if cell is empty
                if (grid[i][j] == " ") {
                    // Make the move
                    grid[i][j] = compSymbol;

                    // Call minimax recursively and choose the maximum value
                    best = std::max(best, minimax(depth + 1, !isMax));

                    // Undo the move
                    grid[i][j] = " ";
                }
            }
        }
        return best;
    }

    // If it is the minimizer's move (player)
    else {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                // Check if cell is empty
                if (grid[i][j] == " ") {
                    // Make the move
                    grid[i][j] = playerSymbol;

                    // Call minimax recursively and choose the minimum value
                    best = std::min(best, minimax(depth + 1, !isMax));

                    // Undo the move
                    grid[i][j] = " ";
                }
            }
        }
        return best;
    }
}

std::pair<int, int> findBestMove() {
    int bestVal = -1000;
    std::pair<int, int> bestMove = {-1, -1};

    // Traverse all cells, evaluate minimax function for all empty cells
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            // Check if cell is empty
            if (grid[i][j] == " ") {
                // Make the move
                grid[i][j] = compSymbol;

                // Compute evaluation function for this move
                int moveVal = minimax(0, false);

                // Undo the move
                grid[i][j] = " ";

                // If the value of the current move is more than the best value, update best
                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}