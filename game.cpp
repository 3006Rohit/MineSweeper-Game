#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

// Global variables
int ROWS, COLS, MINES;
std::vector<std::vector<char>> mineBoard;
std::vector<std::vector<char>> playerBoard;
bool gameOver;
int movesLeft;

// Function to check if coordinates are within the board
bool isValid(int r, int c) {
    return (r >= 0) && (r < ROWS) && (c >= 0) && (c < COLS);
}

// Function to calculate adjacent mines for each cell
void calculateAdjacentMines() {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (mineBoard[r][c] == '*') continue;

            int mineCount = 0;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) continue;
                    int nr = r + dr;
                    int nc = c + dc;
                    if (isValid(nr, nc) && mineBoard[nr][nc] == '*') {
                        mineCount++;
                    }
                }
            }
            mineBoard[r][c] = mineCount + '0';
        }
    }
}

// Function to set up the game boards and variables
void setupGame() {
    // Customizable grid (5x5 to 20x20)
    do {
        std::cout << "Enter number of rows (5-20): ";
        std::cin >> ROWS;
    } while (ROWS < 5 || ROWS > 20);

    do {
        std::cout << "Enter number of columns (5-20): ";
        std::cin >> COLS;
    } while (COLS < 5 || COLS > 20);

    int maxMines = ROWS * COLS / 4; // Max 25% mines
    do {
        std::cout << "Enter number of mines (1-" << maxMines << "): ";
        std::cin >> MINES;
    } while (MINES < 1 || MINES > maxMines);


    mineBoard.assign(ROWS, std::vector<char>(COLS, '0'));
    playerBoard.assign(ROWS, std::vector<char>(COLS, '.'));
    gameOver = false;
    movesLeft = ROWS * COLS - MINES;

    // Place mines randomly
    srand(time(0));
    int minesPlaced = 0;
    while (minesPlaced < MINES) {
        int r = rand() % ROWS;
        int c = rand() % COLS;
        if (mineBoard[r][c] != '*') {
            mineBoard[r][c] = '*';
            minesPlaced++;
        }
    }

    // Calculate the numbers for non-mine cells
    calculateAdjacentMines();
}

// Function to print the player's board
void printBoard() {
    system("cls"); // For Windows, use "clear" for Linux/Mac
    std::cout << "   ";
    for (int c = 0; c < COLS; ++c) std::cout << c << (c < 10 ? "  " : " ");
    std::cout << "\n";

    for (int r = 0; r < ROWS; ++r) {
        std::cout << r << (r < 10 ? "  " : " ");
        for (int c = 0; c < COLS; ++c) {
            std::cout << playerBoard[r][c] << "  ";
        }
        std::cout << "\n";
    }
    std::cout << "\nMines left: " << MINES << "\n";
}

// Recursive function to uncover cells
void uncoverCell(int r, int c) {
    if (!isValid(r, c) || playerBoard[r][c] != '.') return;
    
    // Uncover the cell
    char actualValue = mineBoard[r][c];
    playerBoard[r][c] = actualValue;
    
    if (actualValue != '*') {
         movesLeft--;
    }

    // If it's an empty cell ('0'), uncover its neighbors
    if (actualValue == '0') {
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr == 0 && dc == 0) continue;
                uncoverCell(r + dr, c + dc);
            }
        }
    }
}

// Main function to handle user input and the game loop
void playGame() {
    setupGame();

    while (!gameOver) {
        printBoard();
        std::cout << "Enter your move (e.g., 'p 2 3' to play, 'f 2 3' to flag): ";
        char action;
        int r, c;
        std::cin >> action >> r >> c;

        if (!isValid(r, c)) {
            std::cout << "Invalid coordinates! Try again.\n";
            continue;
        }

        if (action == 'p' || action == 'P') { // Play a move
            if (mineBoard[r][c] == '*') {
                gameOver = true;
                // Reveal all mines
                for(int i=0; i<ROWS; ++i) {
                    for(int j=0; j<COLS; ++j) {
                        if(mineBoard[i][j] == '*') playerBoard[i][j] = '*';
                    }
                }
                printBoard();
                std::cout << "\nBOOM! You hit a mine. GAME OVER!\n";
            } else {
                uncoverCell(r, c);
            }
        } else if (action == 'f' || action == 'F') { // Flag a cell
            if (playerBoard[r][c] == '.') {
                playerBoard[r][c] = 'F';
            } else if (playerBoard[r][c] == 'F') {
                playerBoard[r][c] = '.'; // Unflag
            }
        } else {
            std::cout << "Invalid action! Use 'p' to play or 'f' to flag.\n";
        }
        
        // Check for win condition
        if (movesLeft == 0 && !gameOver) {
            gameOver = true;
            printBoard();
            std::cout << "\nCongratulations! You have cleared the minefield! YOU WIN!\n";
        }
    }
}

int main() {
    playGame();
    return 0;
}
