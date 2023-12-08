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
#include <map>
#include <limits>
#include <utility> 
#include <memory>
#include <climits>
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
//-----------------------------------------------------------------------------------------------------------------

//tree
struct GameState {
    char board[SIZE][SIZE];
    int redPieces;
    int blackPieces;
    GameState* parent;
    std::vector<std::unique_ptr<GameState>> children;

    // Constructor to create a game state node.
    GameState(char b[SIZE][SIZE], int rP, int bP, GameState* p)
        : redPieces(rP), blackPieces(bP), parent(p) {
        std::memcpy(board, b, sizeof(char) * SIZE * SIZE);
    }

    // Function to add a child state.
    void addChild(char b[SIZE][SIZE], int rP, int bP) {
        children.push_back(std::make_unique<GameState>(b, rP, bP, this));
    }
};

// Hash Function for evaluating gamestate
size_t hashGameState(const GameState& state) {
    string boardStr;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            boardStr.push_back(state.board[i][j]);
        }
    }
    // Combine the hash of the board string with the hash of the piece counts
    return hash<std::string>{}(boardStr) ^ (hash<int>{}(state.redPieces) << 1) ^ (hash<int>{}(state.blackPieces) << 2);
}

// Use an unordered_map as a transposition table
unordered_map<size_t, int> transpositionTable;


// When evaluating a game state, check the transposition table first
int evaluateGameState(const GameState& state, char aiPlayer) {
    // Simple evaluation: difference in piece count
    int score = 0;
    char humanPlayer = aiPlayer == 'r' ? 'b' : 'r';
    score += (aiPlayer == 'r' ? state.redPieces : state.blackPieces) * 10;
    score -= (humanPlayer == 'r' ? state.redPieces : state.blackPieces) * 10;

    // Add more sophisticated evaluations here if needed

    // Store the evaluation in the transposition table
    size_t stateHash = hashGameState(state);
    transpositionTable[stateHash] = score;

    return score;
}



//graph
class WeightedGraph {
private:
    std::map<std::pair<int, int>, int> nodeWeights; // Stores the weight of each node (square on the board)

public:
    // Constructor
    WeightedGraph() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                nodeWeights[{i, j}] = (board[i][j] != ' ') ? 10 : 1; // Higher weight for occupied squares
            }
        }
    }

    // Update the weight of a node
    void updateWeight(int x, int y, int weight) {
        nodeWeights[{x, y}] = weight;
    }

    // Get the weight of a node
    int getWeight(int x, int y) {
        auto it = nodeWeights.find({ x, y });
        if (it != nodeWeights.end()) {
            return it->second;
        }
        return std::numeric_limits<int>::max();
    }

   
};


bool canJump(int startX, int startY, int endX, int endY, char player) {
    // Check bounds for the start, mid, and end positions
    if (startX < 0 || startX >= SIZE || startY < 0 || startY >= SIZE ||
        endX < 0 || endX >= SIZE || endY < 0 || endY >= SIZE) {
        return false;
    }

    // Check if end location is two squares away diagonally
    if (abs(startX - endX) == 2 && abs(startY - endY) == 2) {
        int midX = (startX + endX) / 2;
        int midY = (startY + endY) / 2;

        // Check for an opponent's piece in the middle square
        char opponent = (player == 'r') ? 'b' : 'r'; // Determine opponent
        if (board[midX][midY] != opponent) {
            return false; // No opponent piece to jump over
        }

        // Ensure the destination square is empty
        if (board[endX][endY] != ' ') {
            return false; // Destination square is not empty
        }

        

        return true; // All checks passed, jump is valid
    }

    return false; // Not a valid jump move
}



bool movePiece(int startX, int startY, int endX, int endY, char player, Game& rpspGame, WeightedGraph& graph) {
    // Check if the coordinates are within bounds.
    if (endX < 0 || endX >= SIZE || endY < 0 || endY >= SIZE) {
        return false;
    }

    // Ensure the starting square has the player's piece and the ending square is empty.
    if (board[startX][startY] != player || board[endX][endY] != ' ') {
        return false;
    }

    // Check for simple move (one square diagonally).
    if (abs(startX - endX) == 1 && abs(startY - endY) == 1) {
        // Execute simple move.
        board[endX][endY] = board[startX][startY];
        board[startX][startY] = ' ';
        // Update graph weights.
        graph.updateWeight(startX, startY, 1); // The starting square is now empty.
        graph.updateWeight(endX, endY, 10); // The ending square is now occupied.
        return true;
    }

    // If not a simple move, check for jump move.
    int midX = (startX + endX) / 2;
    int midY = (startY + endY) / 2;

    if (canJump(startX, startY, endX, endY, player)) {
        // Run the RPSP game and get the result.
        int gameResult = rpspGame.run();

        if (gameResult == 1) { // Player wins RPSP.
            // Execute jump move.
            board[endX][endY] = board[startX][startY];
            board[startX][startY] = ' ';
            board[midX][midY] = ' '; // Remove the opponent's piece.
            // Update graph weights.
            graph.updateWeight(midX, midY, 1); // The jumped square is now empty.
            graph.updateWeight(startX, startY, 1); // The starting square is now empty.
            graph.updateWeight(endX, endY, 10); // The ending square is now occupied.
            // Update piece count.
            if (player == 'r') blackPieces--;
            else redPieces--;
            return true;
        }
        else {
            // Remove the player's piece
            board[startX][startY] = ' ';
            if (player == 'r') redPieces--;
            else blackPieces--;

            // Update graph weights
            graph.updateWeight(startX, startY, 1); // The starting square is now empty
            return false;
        }
    }

    // If the move is neither a simple move nor a jump, it's invalid.
    return false;
}




// Check if a simple move is valid (one square diagonally, must land on an empty square)
bool isValidSimpleMove(int startX, int startY, int endX, int endY, char player) {
    // Check bounds and ensure the destination square is empty
    if (endX < 0 || endX >= SIZE || endY < 0 || endY >= SIZE || board[endX][endY] != ' ') {
        return false;
    }

    // Check that the move is diagonally forward for the player
    int direction = (player == 'r') ? 1 : -1; // Red moves down, Black moves up
    return (endX == startX + direction) && (abs(endY - startY) == 1);
}




std::vector<Move> generateMovesForPiece(int startX, int startY, char player) {
    std::vector<Move> moves;

    // Directions in which a piece can move: Red moves down (1), Black moves up (-1)
    int moveDirection = (player == 'r') ? 1 : -1;

    // Check for simple moves (one square diagonally)
    for (int dx : {-1, 1}) { // dx is -1 for left diagonal, 1 for right diagonal
        int endX = startX + moveDirection;
        int endY = startY + dx;

        if (isValidSimpleMove(startX, startY, endX, endY, player)) {
            moves.push_back({ {startX, startY}, {endX, endY} });
        }
    }

    // Check for jump moves (two squares diagonally)
    for (int dx : {-1, 1}) {
        int jumpEndX = startX + 2 * moveDirection;
        int jumpEndY = startY + 2 * dx;

        if (canJump(startX, startY, jumpEndX, jumpEndY, player)) {
            moves.push_back({ {startX, startY}, {jumpEndX, jumpEndY} });
        }
    }

    return moves;
}

void applyMove(char board[SIZE][SIZE], const Move& move) {
    int startX = move.first.first;
    int startY = move.first.second;
    int endX = move.second.first;
    int endY = move.second.second;

    // Move the piece
    board[endX][endY] = board[startX][startY];
    board[startX][startY] = ' '; // Set the starting position to empty

    // Check if the move was a jump
    if (abs(startX - endX) == 2 && abs(startY - endY) == 2) {
        int midX = (startX + endX) / 2;
        int midY = (startY + endY) / 2;
        board[midX][midY] = ' '; // Remove the jumped piece
    }

}





void aiMove(char board[SIZE][SIZE], WeightedGraph& graph, char aiPlayer, Game& rpspGame) {
    cout << "AI is thinking..." << endl;

    int bestScore = INT_MIN;
    Move bestMove = { {-1, -1}, {-1, -1} };

    // Try to find the best move by evaluating all possible moves
    for (int startX = 0; startX < SIZE; ++startX) {
        for (int startY = 0; startY < SIZE; ++startY) {
            if (board[startX][startY] == aiPlayer) {
                // Generate potential moves for the piece
                std::vector<Move> potentialMoves = generateMovesForPiece(startX, startY, aiPlayer);

                // Evaluate each move
                for (const Move& move : potentialMoves) {
                    // Make the move on a copy of the board
                    char tempBoard[SIZE][SIZE];
                    memcpy(tempBoard, board, sizeof(board));
                    applyMove(tempBoard, move);

                    GameState tempState(tempBoard, redPieces, blackPieces, nullptr);
                    int score = evaluateGameState(tempState, aiPlayer);

                    // Undo the move
                    memcpy(board, tempBoard, sizeof(board));

                    // If the move is better than the best found so far, remember it
                    if (score > bestScore) {
                        bestScore = score;
                        bestMove = move;
                    }
                }
            }
        }
    }

    // Perform the best move
    if (bestMove.first.first != -1 && bestMove.second.first != -1) {
        movePiece(bestMove.first.first, bestMove.first.second, bestMove.second.first, bestMove.second.second, aiPlayer, rpspGame, graph);
        cout << "AI moved from " << bestMove.first.first << " " << bestMove.first.second;
        cout << " to " << bestMove.second.first << " " << bestMove.second.second << endl;
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
    WeightedGraph graph;

   

    // Initialize the root game state with the starting board
    GameState rootState(board, redPieces, blackPieces, nullptr);
    GameState* currentState = &rootState;
    char currentPlayer = 'b';

    int startX, startY, endX, endY;
    char undoChoice; //for undoing a move
    while (true) {
        


        if (currentPlayer == 'b') { // Human player's turn

            cout << "Your turn (Black). Do you want to undo the last move? (y/n): ";
            cin >> undoChoice;
            if (undoChoice == 'y' || undoChoice == 'Y') {
                if (currentState->parent != nullptr && currentState->parent->parent != nullptr) {
                    // Go to a previous state
                    if (currentState->parent != nullptr) {
                        currentState = currentState->parent->parent;
                        // Update the actual game board to match the previous state
                        std::memcpy(board, currentState->board, sizeof(char) * SIZE * SIZE);
                        redPieces = currentState->redPieces;
                        blackPieces = currentState->blackPieces;;
                        displayBoard();

                    }
                    else {
                        cout << "No moves to undo!" << endl;
                    }
                }
            }

            cout << "Your turn (Black)." << endl;
            cout << "Enter the row and column of the piece you want to move (e.g., 2 3): ";
            cin >> startX >> startY;
            cout << "Enter the row and column you want to move to (e.g., 3 4): ";
            cin >> endX >> endY;

            if (movePiece(startX, startY, endX, endY, currentPlayer, rpsp, graph)) {
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
            aiMove(board, graph, 'r', rpsp);
            displayBoard();
            cout << "Black pieces left: " << blackPieces << ", Red pieces left: " << redPieces << endl;
        }

        // Update the turn queue for the next player
            currentState->addChild(board, redPieces, blackPieces);
            currentState = currentState->children.back().get();
            currentPlayer = currentPlayer == 'b' ? 'r' : 'b';

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