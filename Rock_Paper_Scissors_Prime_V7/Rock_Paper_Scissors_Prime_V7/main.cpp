#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unordered_map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <utility> // For std::pair
#include "RPSP.h"

using namespace std;

const int SIZE = 8; // Standard checkerboard size
char board[SIZE][SIZE];
int redPieces = 12, blackPieces = 12; // Initial number of pieces for each player


// Global unordered_map to store AI choices based on the player's last move
unordered_map<char, set<char>> aiChoices;

// Define a Move type as a pair of pairs
using Move = pair<std::pair<int, int>, pair<int, int>>;

// Global list to store the move history
std::list<Move> moveHistory;

// Global stack for undo functionality
std::stack<Move> undoStack;

// Global queue for turn order
std::queue<char> turnQueue;

//implementation of the Rock Paper Scissors Prime class
Game::Game() : primeCounter(0), playerHealth(100), aiHealth(100), maxHealth(100) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

int Game::run() {
    int roundResult = -1;
    while (playerHealth > 0 && aiHealth > 0) {
        roundResult = playRound();
    }

    return roundResult;
}

int Game::sieveOfE(int n) {
    if (n < 2) {
        return 0; // No primes less than 2
    }

    bool* primeList = new bool[n + 1];
    memset(primeList, true, n + 1); // Initialize all elements to true

    primeList[0] = primeList[1] = false; // 0 and 1 are not prime numbers

    for (int p = 2; p * p <= n; p++) {
        if (primeList[p]) {
            for (int i = p * p; i <= n; i += p) {
                primeList[i] = false;
            }
        }
    }

    int primeCount = 0;
    for (int i = 2; i <= n; i++) {
        if (primeList[i]) {
            primeCount++;
        }
    }

    delete[] primeList; // Deallocate the memory
    return primeCount;
}

bool Game::isPrime(int n) {
    if (n <= 1) {
        return false;
    }

    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void Game::displayHealthBar(int health, int maxHealth) {
    int barWidth = 20; // Width of the health bar
    int healthUnits = (health * barWidth) / maxHealth; // Calculate the number of '#' characters
    cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < healthUnits) {
            cout << "#"; // Health remaining
        }
        else {
            cout << "-"; // Health lost
        }
    }
    cout << "] " << health << " / " << maxHealth << endl; // Display current health and max health
}

void Game::displayAsciiArt(char choice) {
    switch (choice) {
    case 'r':
        cout <<
            "    _______\n"
            "---'   ____)\n"
            "      (_____)\n"
            "      (_____)\n"
            "      (____)\n"
            "---.__(___)\n";
        break;
    case 'p':
        cout <<
            "    _______\n"
            "---'   ____)____\n"
            "          ______)\n"
            "          _______)\n"
            "         _______)\n"
            "---.__________)\n";
        break;
    case 's':
        cout <<
            "    _______\n"
            "---'   ____)____\n"
            "          ______)\n"
            "       __________)\n"
            "      (____)\n"
            "---.__(___)\n";
        break;
    case '1': // Assuming '1' is the character for PRIME
        cout <<
            "    /\\  \n"
            "   /  \\ \n"
            "  /____\\ \n"
            "  \\    / \n"
            "   \\  /  \n"
            "    \\/   \n";
        break;

    default:
        cout << "Invalid choice\n";
        break;
    }
}

int Game::comparison(char input, char artificialInput, int primeCounter) {
    if (input == 'r' && artificialInput == 's') {
        return 1;

    }

    if (input == 'r' && artificialInput == 'p') {
        return 0;

    }

    if (input == 'p' && artificialInput == 'r') {
        return 1;

    }

    if (input == 'p' && artificialInput == 's') {
        return 0;

    }

    if (input == 's' && artificialInput == 'p') {
        return 1;

    }

    if (input == 's' && artificialInput == 'r') {
        return 0;

    }

    if (input == '1') {
        if (isPrime(primeCounter)) {

            return 2;

        }

        else {
            cout << endl << "Prime Counter is not prime your choice will count as ROCK" << endl;

            input = 'r';

            return comparison(input, artificialInput, primeCounter);

        }
    }

    else {
        return 3;

    }
}

void initAIChoices() {
    aiChoices['r'] = { 'p' };  // AI chooses paper when the last human choice was rock
    aiChoices['p'] = { 's' };  // AI chooses scissors when the last human choice was paper
    aiChoices['s'] = { 'r' };  // AI chooses rock when the last human choice was scissors
}


void Game::aiData(char input) {
    if (input == 'r') {
        aiChoices['r'].insert('p'); // AI chooses paper against rock
    }
    if (input == 'p') {
        aiChoices['p'].insert('s'); // AI chooses scissors against paper
    }
    if (input == 's') {
        aiChoices['s'].insert('r'); // AI chooses rock against scissors
    }
}


void Game::aiChoice(char& artificialInput, char input) {
    if (aiChoices.find(input) != aiChoices.end()) {
        const set<char>& choices = aiChoices[input];
        int random_index = rand() % choices.size();

        auto it = choices.begin();
        advance(it, random_index); // Advance the iterator to a random position
        artificialInput = *it;
    }
    else {
        artificialInput = 'r'; // Default to rock
    }
}

int Game::playRound() {

    char input, artificialInput;


    while (playerHealth > 0 && aiHealth > 0) {
        cout << "Your health: " << endl;
        displayHealthBar(playerHealth, maxHealth);
        cout << endl << "A.I. health: " << endl;
        displayHealthBar(aiHealth, maxHealth);
        cout << endl << "Prime: " << primeCounter << endl;
        //cout << endl << boolalpha << "Prime number is prime: " << isPrime(primeCounter) << endl << endl; //This is for debugging purposes
        input = 0;

        aiData(input);
        aiChoice(artificialInput, input);

        cout << "Input r for rock, p for paper, s for scissors or 1 for Prime." << endl;

        cin >> input;
        cout << endl << "Your choice: " << endl;
        displayAsciiArt(input);
        aiData(input);
        cout << endl << "A.I. choice: " << endl;
        displayAsciiArt(artificialInput);
        int result = comparison(input, artificialInput, primeCounter);

        if (result == 1) {
            aiHealth -= 25;

            cout << "ai took damage." << endl;

        }

        else if (result == 0) {
            playerHealth -= 25;
            cout << " You took damage." << endl;


        }


        else if (result == 3) {
            cout << "Prime!" << endl;
            primeCounter = rand() % 100;
        }

        else if (result == 2) {
            cout << "PRIME has been casted!" << endl;
            numberOfPrimes = sieveOfE(primeCounter);

            aiHealth -= 25 * numberOfPrimes;

        }

        if (aiHealth <= 0) {

            cout << endl << "You win!" << endl;
            return 1;
        }

        if (playerHealth <= 0) {
            cout << endl << "You lost!" << endl;
            return 2;
        }
        cout << endl;
    }
    return 0;
}

//Checkers part of the code

bool canJump(int startX, int startY, int endX, int endY, char player) {
    int boardSize = 8;

    // Check bounds
    if (startX < 0 || startX >= boardSize || startY < 0 || startY >= boardSize ||
        endX < 0 || endX >= boardSize || endY < 0 || endY >= boardSize) {
        return false;
    }

    // Check if end location is two squares away diagonally
    if (abs(startX - endX) == 2 && abs(startY - endY) == 2) {
        int midX = (startX + endX) / 2;
        int midY = (startY + endY) / 2;

        // Bounds check for the middle square
        if (midX < 0 || midX >= boardSize || midY < 0 || midY >= boardSize) {
            return false;
        }

        // Check for an opponent's piece in the middle square
        if (board[midX][midY] != ' ' && board[midX][midY] != player) {
            return true;
        }
    }

    return false;
}


bool movePiece(int startX, int startY, int endX, int endY, char player, Game& rpspGame) {

    if (endX < 0 || endX >= SIZE || endY < 0 || endY >= SIZE) {
        return false;
    }

    if (board[startX][startY] != player || board[endX][endY] != ' ') {
        return false;
    }

    if (canJump(startX, startY, endX, endY, player)) {
        int midX = (startX + endX) / 2;
        int midY = (startY + endY) / 2;

        int gameResult = rpspGame.run(); // Run the RPSP game and get the result

        if (gameResult == 1) { // Player wins RPSP
            // Execute logic for player winning the RPSP game
            // Remove the opponent's piece
            board[midX][midY] = ' ';
            if (player == 'r') blackPieces--;
            else redPieces--;
        }
        else { // Player loses RPSP
         // Execute logic for player losing the RPSP game
         // Remove the player's piece
            board[startX][startY] = ' ';
            if (player == 'r') redPieces--;
            else blackPieces--;
            return false; // Jump failed
        }
    }

    board[endX][endY] = board[startX][startY];
    board[startX][startY] = ' ';

    if (board[endX][endY] == player) {
        moveHistory.push_back({ {startX, startY}, {endX, endY} });
        undoStack.push({ {startX, startY}, {endX, endY} });
    }

    return true;
}

void aiMove() {
    cout << "AI is thinking" << endl;

    Game rpsp;
    srand(static_cast<unsigned int>(time(0)));

    bool moved = false;

    while (!moved) {
        int startX = rand() % SIZE;
        int startY = rand() % SIZE;

        if (board[startX][startY] == 'r') {
            // Try jump moves first
            int jumpDirections[4][2] = { {2, 2}, {2, -2}, {-2, 2}, {-2, -2} };
            for (int i = 0; i < 4; ++i) {
                int endX = startX + jumpDirections[i][0];
                int endY = startY + jumpDirections[i][1];
                if (movePiece(startX, startY, endX, endY, 'r', rpsp)) {
                    moved = true;
                    cout << "AI jumped from " << startX << " " << startY << " to " << endX << " " << endY << endl;
                    return; // Exit the function after a successful move
                }
            }

            // If no jump move is possible, try regular moves
            int moveDirections[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
            for (int i = 0; i < 4; ++i) {
                int endX = startX + moveDirections[i][0];
                int endY = startY + moveDirections[i][1];
                if (movePiece(startX, startY, endX, endY, 'r', rpsp)) {
                    moved = true;
                    cout << "AI moved from " << startX << " " << startY << " to " << endX << " " << endY << endl;
                    return; // Exit the function after a successful move
                }
            }
        }
    }
}

void undoLastMove() {
    if (undoStack.size() < 2) {
        cout << "Cannot Undo" << endl;
        return;
    }

    for (int i = 0; i < 2; ++i) {
        Move lastMove = undoStack.top();
        undoStack.pop();

        // Revert the move
        int startX = lastMove.first.first;
        int startY = lastMove.first.second;
        int endX = lastMove.second.first;
        int endY = lastMove.second.second;

        char player = board[endX][endY];
        board[startX][startY] = player;
        board[endX][endY] = ' ';

        // If this was a jump, put back the captured piece
        if (abs(startX - endX) == 2 && abs(startY - endY) == 2) {
            int midX = (startX + endX) / 2;
            int midY = (startY + endY) / 2;
            board[midX][midY] = player == 'r' ? 'b' : 'r'; 
            if (player == 'r') {
                blackPieces++; // Increment the count of black pieces
            }
            else {
                redPieces++; // Increment the count of red pieces
            }
        }
    }

    
    cout << "Undo Done" << endl;
}



// Initialize the board with pieces
void initBoard() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if ((i + j) % 2 == 1) { // Checkers are placed on black squares
                if (i < 3)
                    board[i][j] = 'r'; // Red pieces for AI at the top
                else if (i > 4)
                    board[i][j] = 'b'; // Black pieces for the player at the bottom
                else
                    board[i][j] = ' '; // Empty space
            }
            else {
                board[i][j] = ' '; // Empty space
            }
        }
    }
}


void displayBoard() {
    cout << "  ";
    for (int col = 0; col < SIZE; ++col) {
        cout << col << " "; // Column headers
    }
    cout << endl;

    for (int i = 0; i < SIZE; ++i) {
        cout << i << " "; // Row headers
        for (int j = 0; j < SIZE; ++j) {
            if ((i + j) % 2 == 0) {
                cout << "."; // Represent white squares with a dot
            }
            else {
                if (board[i][j] == ' ') {
                    cout << "_"; // Represent empty black squares with an underscore
                }
                else {
                    cout << board[i][j]; // Pieces on black squares
                }
            }
            cout << " ";
        }
        cout << endl;
    }
}



int main() {
    Game rpsp;
    initBoard();
    displayBoard();

    // Initialize the turn queue
    turnQueue.push('b'); // Black (Human) starts first
    turnQueue.push('r'); // Red (AI) follows

    int startX, startY, endX, endY;
    char undoChoice; //for undoing a move
    while (true) {
        char currentPlayer = turnQueue.front();
        turnQueue.pop();


        if (currentPlayer == 'b') { // Human player's turn

            cout << "Your turn (Black). Do you want to undo the last move? (y/n): ";
            cin >> undoChoice;
            if (undoChoice == 'y' || undoChoice == 'Y') {
                undoLastMove();
                displayBoard();
                turnQueue.push(currentPlayer);
                continue; // Skip the rest of the loop to allow player to make a new move
            }

            cout << "Your turn (Black)." << endl;
            cout << "Enter the row and column of the piece you want to move (e.g., 2 3): ";
            cin >> startX >> startY;
            cout << "Enter the row and column you want to move to (e.g., 3 4): ";
            cin >> endX >> endY;

            if (movePiece(startX, startY, endX, endY, currentPlayer, rpsp)) {
                displayBoard();
                cout << "Black pieces left: " << blackPieces << ", Red pieces left: " << redPieces << endl;
            }
            else {
                cout << "Invalid move. Please try again." << endl;
                turnQueue.push(currentPlayer); // Put the player back in the queue to retry
                continue;
            }
        }
        else { // AI's turn
            cout << "AI's turn (Red)." << endl;
            aiMove();
            displayBoard();
            cout << "Black pieces left: " << blackPieces << ", Red pieces left: " << redPieces << endl;
        }

        // Update the turn queue for the next player
        turnQueue.push(currentPlayer);

        // Check for game over conditions based on piece counts
        if (blackPieces == 0 && redPieces > 0) {
            cout << "Game Over! AI Wins!" << endl;
            break;
        }

        if (blackPieces > 0 && redPieces == 0) {
            cout << "You Win!!!" << endl;
            break;
        }
    }

    return 0;
}

