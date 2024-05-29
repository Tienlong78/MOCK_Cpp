/*******************************************************************************
* LIBRARY
*******************************************************************************/
#include "Board.h"
using namespace std;

/*******************************************************************************
* Getter of class CaroBoard
*******************************************************************************/
/**
 * @brief Get the symbol at the specified coordinates.
 * @param row The row index.
 * @param col The column index.
 * @return The symbol at the specified coordinates.
 */
char BOARD::getMove(vector<vector<char>> board, int row, int col) {
    return board[row][col];
}

/*******************************************************************************
* Setter of class CaroBoard
*******************************************************************************/
/**
 * @brief Set the symbol at the specified coordinates.
 * @param row The row index.
 * @param col The column index.
 * @param symbol The symbol to set.
 */
void BOARD::setMove(vector<vector<char>>& board, int row, int col, char symbol) {
    if (row >= 0 && row < BOARD_MAXSIZE && col >= 0 && col < BOARD_MAXSIZE) {
        board[row][col] = symbol;
    }
}

/*******************************************************************************
* Methods of class CaroBoard
*******************************************************************************/
/**
 * @brief Check if the specified cell is empty.
 * @param row The row index.
 * @param col The column index.
 * @return True if the cell is empty, false otherwise.
 */
bool BOARD::isCellEmpty(vector<vector<char>> board, int row, int col) {
    if (board[row][col] != ' ') {
        return false;
    }
    return true;
}

/**
 * @brief Check if the board is full.
 * @return True if the board is full, false otherwise.
 */
bool BOARD::isBoardFull(vector<vector<char>> board) {
    for (int i = 0; i < BOARD_MAXSIZE; ++i) {
        for (int j = 0; j < BOARD_MAXSIZE; ++j) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Reset the board to its initial state.
 */
void BOARD::resetBoard(vector<vector<char>>& board) {
    for (int i = 0; i < BOARD_MAXSIZE; ++i) {
        for (int j = 0; j < BOARD_MAXSIZE; ++j) {
            board[i][j] = ' ';
        }
    }
}

/**
 * @brief Reset the specified cell to empty.
 * @param row The row index.
 * @param col The column index.
 */
void BOARD::resetCell(vector<vector<char>> board, int row, int col) {
    board[row][col] = ' ';
}

/**
 * @brief Display the current state of the board.
 */
void BOARD::showBoard(vector<vector<char>>& board) {
    system("cls");
    cout << "   ";
    for (int i = 0; i < BOARD_MAXSIZE; ++i) {
        cout << " " << i << "  ";
    }
    cout << "\n";
    for (int i = 0; i < BOARD_MAXSIZE; ++i) {
        cout << "  ";
        for (int k = 0; k < BOARD_MAXSIZE; ++k) {
            cout << "|---";
        }
        cout << "|\n";
        cout << i << " ";
        for (int j = 0; j < BOARD_MAXSIZE; ++j) {
            cout << "| " << getMove(board, i, j) << " ";
        }
        cout << "|\n";
    }
    cout << "  ";
    for (int k = 0; k < BOARD_MAXSIZE; ++k) {
        cout << "|---";
    }
    cout << "|\n";
}

void BOARD::setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/**
 * @brief Draw the board.
 */
void BOARD::drawBoard(vector<vector<char>> board) {
    setColor(ORANGE);
    cout << "   ";
    for (int i = 0; i < BOARD_MAXSIZE; ++i) {
        setColor(PINK);
        cout << " " << i << "  ";
    }
    cout << "\n";
    for (int i = 0; i < BOARD_MAXSIZE; ++i) {
        cout << "  ";
        for (int k = 0; k < BOARD_MAXSIZE; ++k) {
            setColor(ORANGE);
            cout << "|---";
        }
        cout << "|\n";
        setColor(PINK);
        cout << i << " ";
        for (int j = 0; j < BOARD_MAXSIZE; ++j) {
            setColor(ORANGE);
            cout << "| ";
            setColor(WHITE);
            cout << board[i][j];
            setColor(ORANGE);
            cout << " ";
        }
        cout << "|\n";
    }
    cout << "  ";
    for (int k = 0; k < BOARD_MAXSIZE; ++k) {
        cout << "|---";
    }
    cout << "|\n";
    setColor(WHITE);
}

/**
 * @brief Check for a winner on the board.
 * @return The winning symbol if there is a winner, otherwise returns ' '.
 */
char BOARD::checkWinner(vector<vector<char>> board) {
    // Check rows
    for (int i = 0; i < BOARD_MAXSIZE; ++i) {
        for (int j = 0; j <= BOARD_MAXSIZE - WIN_CONDITION; ++j) {
            char current = board[i][j];
            if (current != ' ') {
                bool win = true;
                for (int k = 1; k < WIN_CONDITION; ++k) {
                    if (board[i][j + k] != current) {
                        win = false;
                        break;
                    }
                }
                if (win && (j == 0 || board[i][j - 1] != current) &&
                    (j + WIN_CONDITION == BOARD_MAXSIZE || board[i][j + WIN_CONDITION] != current)) {
                    if (j == 0 || j + WIN_CONDITION == BOARD_MAXSIZE ||
                        (j > 0 && board[i][j - 1] == ' ') ||
                        (j + WIN_CONDITION < BOARD_MAXSIZE && board[i][j + WIN_CONDITION] == ' ')) {
                        return current;
                    }
                }
            }
        }
    }

    // Check columns
    for (int i = 0; i <= BOARD_MAXSIZE - WIN_CONDITION; ++i) {
        for (int j = 0; j < BOARD_MAXSIZE; ++j) {
            char current = board[i][j];
            if (current != ' ') {
                bool win = true;
                for (int k = 1; k < WIN_CONDITION; ++k) {
                    if (board[i + k][j] != current) {
                        win = false;
                        break;
                    }
                }
                if (win && (i == 0 || board[i - 1][j] != current) &&
                    (i + WIN_CONDITION == BOARD_MAXSIZE || board[i + WIN_CONDITION][j] != current)) {
                    if (i == 0 || i + WIN_CONDITION == BOARD_MAXSIZE ||
                        (i > 0 && board[i - 1][j] == ' ') ||
                        (i + WIN_CONDITION < BOARD_MAXSIZE && board[i + WIN_CONDITION][j] == ' ')) {
                        return current;
                    }
                }
            }
        }
    }

    // Check diagonal (top-left to bottom-right)
    for (int i = 0; i <= BOARD_MAXSIZE - WIN_CONDITION; ++i) {
        for (int j = 0; j <= BOARD_MAXSIZE - WIN_CONDITION; ++j) {
            char current = board[i][j];
            if (current != ' ') {
                bool win = true;
                for (int k = 1; k < WIN_CONDITION; ++k) {
                    if (board[i + k][j + k] != current) {
                        win = false;
                        break;
                    }
                }
                if (win && (i == 0 || j == 0 || board[i - 1][j - 1] != current) &&
                    (i + WIN_CONDITION == BOARD_MAXSIZE || j + WIN_CONDITION == BOARD_MAXSIZE || board[i + WIN_CONDITION][j + WIN_CONDITION] != current)) {
                    if ((i == 0 || j == 0 || board[i - 1][j - 1] == ' ') ||
                        (i + WIN_CONDITION == BOARD_MAXSIZE || j + WIN_CONDITION == BOARD_MAXSIZE || board[i + WIN_CONDITION][j + WIN_CONDITION] == ' ')) {
                        return current;
                    }
                }
            }
        }
    }

    // Check diagonal (top-right to bottom-left)
    for (int i = WIN_CONDITION - 1; i < BOARD_MAXSIZE; ++i) {
        for (int j = 0; j <= BOARD_MAXSIZE - WIN_CONDITION; ++j) {
            char current = board[i][j];
            if (current != ' ') {
                bool win = true;
                for (int k = 1; k < WIN_CONDITION; ++k) {
                    if (board[i - k][j + k] != current) {
                        win = false;
                        break;
                    }
                }
                if (win && (i == WIN_CONDITION - 1 || j == 0 || board[i + 1][j - 1] != current) &&
                    (i - WIN_CONDITION == -1 || j + WIN_CONDITION == BOARD_MAXSIZE || board[i - WIN_CONDITION][j + WIN_CONDITION] != current)) {
                    if ((i == WIN_CONDITION - 1 || j == 0 || board[i + 1][j - 1] == ' ') ||
                        (i - WIN_CONDITION == -1 || j + WIN_CONDITION == BOARD_MAXSIZE || board[i - WIN_CONDITION][j + WIN_CONDITION] == ' ')) {
                        return current;
                    }
                }
            }
        }
    }

    return ' ';
}

