#include "../include/tictactoe.hpp"

int main() {
    // Initialize the game setup and display
    initializeGame();
    //Promp player to select symbol
    selectSymbol();

    // Game loop: Continue until the game is over
    while (!gameOver()) {
        // Player makes a move
        playerTurn();
        // Computer makes a move
        compTurn();
        // Display the updated game board
        displayGrid();
    }
    
    // Print game over message
    std::cout << "Game Over!" << std::endl;

    // Print the result of the game
    if (winner == "None") {
        std::cout << "It is a draw" << std::endl;
    } else {
        std::cout << winner << " wins" << std::endl;
    }

    return 0;
}
