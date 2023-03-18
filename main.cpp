#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

// 4x4 board 2048 is played on. 
int board[4][4];
// Up, Right, Down, Left.
int dirRow[] = {1, 0, -1, 0};
int dirCol[] = {0, 1, 0, -1};
// Keeping track of score. 
int score; 
int highscore;

/**
 * Adds a 2 into a randomly generated position. 
*/
void addPiece() {
    // Randomly chooses an empty position. 
    bool occupied = true;
    int row, col;
    while (occupied) {
        // Picks a random row and col.
        row = rand() % 4;
        col = rand() % 4;
        // Find a unoccupied position.
        if (board[row][col] == 0) {
            occupied = false;
        }
    }
    // Inserts a 2 into the position. 
    pair<int, int> pos = make_pair(row, col);
    // Randomly generates random number between 0 and 9 inclusive. 
    int rand_num = rand() % 10;
    // Allows for 10% chance of generating a 4. 
    if (rand_num == 0) {
        board[pos.first][pos.second] = 4;
    }
    else {
        board[pos.first][pos.second] = 2;
    }
}

/**
 * Creates the initial board. 
*/
void newGame() {
    // Reset board to all 0s. 
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++) 
            board[i][j] = 0;
    // Starting board with a randomly placed singular 2.
    addPiece();
}

/**
 * Prints the current board. 
*/
void printUI() {
    // Clears the screen inbetween every run. 
    system("clear");
    // Prints out the current board. 
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                cout << setw(4) << ".";
            } else {
                cout << setw(4) << board[i][j];
            }
        }
        cout << "\n";
    }
    // Controls for the game.
    cout << "Controls: WASD - Movement, n - New Game/Reset, q - Quit \n";
    cout << "Score: " << score << endl;
    cout << "Highscore: " << highscore << endl;
}

/**
 * Checks if a move is possible. 
*/
bool canDoMove(int row, int col, int nextRow, int nextCol) {
    // Check if next move is in bounds first. Then perform additional checks. 
    if(nextRow < 0 || nextCol < 0 || nextRow >= 4 || nextCol >= 4 
        || (board[row][col] != board[nextRow][nextCol] && board[nextRow][nextCol] != 0)){
        return false;
    }
    return true;
}

/**
 * Moves all pieces in a input direction. 
*/
void applyMove(int direction) {
    int startRow = 0, startCol = 0, rowStep = 1, colStep = 1;
    // Down.
    if (direction == 0) {
        startRow = 3;
        rowStep = -1;
    }
    // Right.
    if (direction == 1) {
        startCol = 3;
        colStep = -1;
    }
    bool movePossible;
    bool canAddPiece = false;
    // Use of do while allows for movement of more than 1 square at a time. 
    do {
        movePossible = false;
        for (int i = startRow; i >= 0 &&  i < 4; i += rowStep) {
            for (int j = startCol; j >= 0 &&  j < 4; j += colStep) {
                int nextRow = i + dirRow[direction];
                int nextCol = j + dirCol[direction];
                // cout << i << " " << j << " " << nextRow << " " << nextCol << "\n";
                // If move is possible, add the two slots and set previous to be 0. 
                if(board[i][j] && canDoMove(i, j, nextRow, nextCol)){
                    if(board[nextRow][nextCol] != 0){
                        if(highscore <= score){
                            highscore += (board[i][j] + board[nextRow][nextCol]);
                        }
                        score += (board[i][j] + board[nextRow][nextCol]);
                    }
                    board[nextRow][nextCol] += board[i][j];
                    board[i][j] = 0;
                    movePossible = true;
                    canAddPiece = true;
                }
            }
        } 
        // Simulates dragging effect by printing UI between iteration. 
        printUI();
    } while (movePossible); 
    // Add a piece if the game isn't over. 
    if(canAddPiece) {
        addPiece();
    }
}

/**
 * Runs the program. 
*/
int main() {
    // Generates a random empty position.
    srand(time(0));
    // Mapping of all ASCII characters. 
    char commandToDir[128];
    commandToDir['s'] = 0; // Down
    commandToDir['d'] = 1; // Right
    commandToDir['w'] = 2; // Up
    commandToDir['a'] = 3; // Left
    // commandToDir['B'] = 0; // Down arrow
    // commandToDir['C'] = 1; // Right arrow
    // commandToDir['A'] = 2; // Up arrow
    // commandToDir['D'] = 3; // Left arrow
    newGame();

    while (true) {
        printUI();
        char command;
        cin >> command;
        // Initialization. 
        if (command == 'n') {
            // Resets scores between games. 
            if(highscore < score) {
                highscore = score;
            }
            score = 0;
            newGame();
        } 
        // Quit.
        else if (command == 'q') {
            break;
        }
        // Movement.
        else {
            int currentDirection = commandToDir[command];
            // cout << currentDirection << "\n";
            applyMove(currentDirection);
        }
    }
    return 0;
}