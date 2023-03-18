#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

// 4x4 board 2048 is played on. 
int board[4][4];
// Up, Right, Down, Left.
int dirRow[] = {1, 0, -1, 0};
int dirCol[] = {0, 1, 0, -1};

/*
* Random chooses a empty position
*/
pair<int, int> generateEmptyPosition() {
    int occupied = true, row, col;
    while (occupied) {
        // Picks a random row and col.
        row = rand() % 4;
        col = rand() % 4;
        if (board[row][col] == 0) {
            occupied = false;
        }
    }
    return make_pair(row, col);
}

void addPiece() {
    // Starting board with a singular 2.
    pair<int, int> pos = generateEmptyPosition();
    board[pos.first][pos.second] = 2;
}

void newGame() {
    // Reset board to all 0s. 
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++) 
            board[i][j] = 0;
    addPiece();
}

void printUI() {
    system("clear");
    // Prints out the current board. 
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            if (board[i][j] == 0)
                cout << setw(4) << ".";
            else
                cout << setw(4) << board[i][j];
        cout << "\n";
    }
    // Controls for the game.
    cout << "Controls: WASD - Movement, n - New Game/Reset, q - Quit \n";
}

bool canDoMove(int row, int col, int nextRow, int nextCol) {
    // Check if next move is in bounds first.
    if(nextRow < 0 || nextCol < 0 || nextRow >= 4 || nextCol >= 4 
        || (board[row][col] != board[nextRow][nextCol] && board[nextRow][nextCol] != 0)){
        return false;
    }
    return true;
}

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
    int movePossible;
    int canAddPiece = 0;
    // Use of do while allows for movement of more than 1 square. 
    do {
        movePossible = 0;
        for (int i = startRow; i >= 0 &&  i < 4; i += rowStep) {
            for (int j = startCol; j >= 0 &&  j < 4; j += colStep) {
                int nextRow = i + dirRow[direction];
                int nextCol = j + dirCol[direction];
                // cout << i << " " << j << " " << nextRow << " " << nextCol << "\n";
                // If move is possible, add the two slots and set previous to be 0. 
                if(board[i][j] && canDoMove(i, j, nextRow, nextCol)){
                    board[nextRow][nextCol] += board[i][j];
                    board[i][j] = 0;
                    movePossible = 1;
                    canAddPiece = 1;
                }
            }
        } 
        printUI();
    } while (movePossible); 
    // Add a piece if the game isn't over. 
    if(canAddPiece) {
        addPiece();
    }
}

int main() {
    // Generates a random empty position.
    srand(time(0));
    // Mapping of all ASCII characters. 
    char commandToDir[128];
    commandToDir['s'] = 0; // Down
    commandToDir['d'] = 1; // Right
    commandToDir['w'] = 2; // Up
    commandToDir['a'] = 3; // Left
    commandToDir['B'] = 0; // Down arrow
    commandToDir['C'] = 1; // Right arrow
    commandToDir['A'] = 2; // Up arrow
    commandToDir['D'] = 3; // Left arrow
    newGame();

    while (true) {
        printUI();
        char command;
        cin >> command;
        // Initialization. 
        if (command == 'n') {
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