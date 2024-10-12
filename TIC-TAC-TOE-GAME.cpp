#include <iostream>
using namespace std;

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};  // Game board
char currentPlayer = 'X';  // Current player
int moves = 0;  // To track number of moves

void displayBoard() {
    // Function to display the current game board
    cout << "-------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

bool checkWin() {
    // Function to check if a player has won
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return true;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return true;
        }
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return true;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return true;
    }
    return false;
}

bool checkDraw() {
    // Function to check if the game is a draw
    return (moves == 9);  // If 9 moves have been made, the game is a draw
}

void switchPlayer() {
    // Function to switch the player
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

bool isValidMove(int choice) {
    // Function to check if the chosen move is valid
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;
    return board[row][col] != 'X' && board[row][col] != 'O';
}

void makeMove(int choice) {
    // Function to update the board with the player's move
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;
    board[row][col] = currentPlayer;
    moves++;
}

void resetGame() {
    // Function to reset the game board
    char num = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = num++;
        }
    }
    moves = 0;
    currentPlayer = 'X';
}

int main() {
    int choice;
    bool playAgain = true;

    cout << "Welcome to Tic-Tac-Toe!\n";

    while (playAgain) {
        displayBoard();  // Display initial board state

        while (true) {
            cout << "Player " << currentPlayer << ", enter your move (1-9): ";
            cin >> choice;

            // Check for valid move
            if (choice >= 1 && choice <= 9 && isValidMove(choice)) {
                makeMove(choice);  // Update the board

                displayBoard();  // Show the updated board

                if (checkWin()) {
                    cout << "Player " << currentPlayer << " wins the game!\n";
                    break;
                } else if (checkDraw()) {
                    cout << "The game is a draw!\n";
                    break;
                } else {
                    switchPlayer();  // Switch turns
                }
            } else {
                cout << "Invalid move! Please try again.\n";
            }
        }

        // Ask if players want to play again
        char response;
        cout << "Do you want to play again? (y/n): ";
        cin >> response;
        if (response == 'y' || response == 'Y') {
            resetGame();  // Reset the board for a new game
        } else {
            playAgain = false;  // End the game
        }
    }

    cout << "Thanks for playing Tic-Tac-Toe!\n";
    return 0;
}
