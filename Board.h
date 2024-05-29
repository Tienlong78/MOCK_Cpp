#pragma once
/*******************************************************************************
*  LIBRARY
*******************************************************************************/
#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

/*******************************************************************************
*  Definition
*******************************************************************************/
#define WIN_CONDITION (4)   /**< Number of symbols in a row required to win */
#define BOARD_MAXSIZE (10)  /**< Maximum size of the game board */
#define PLAYER_X      (88)  /**< Player symbol X */
#define PLAYER_O      (79)  /**< Player symbol O */
#define EMPTY         (32)  /**< Cell is empty */
#define ORANGE        (6)
#define PINK          (13)
#define WHITE         (15)
#define RED           (12)

/*******************************************************************************
*  Class CaroBoard
*******************************************************************************/
class BOARD {
public:
    int mSize;
    vector<vector<char>> board; /**< Collection of board points */

    /*******************************************************************************
    * Constructor
    *******************************************************************************/
    /**
     * @brief Constructor to initialize the board with empty cells.
     *
     * Initializes the board with a size of 10x10 and fills it with empty cells.
     */
    BOARD() : mSize(10), board(mSize, vector<char>(mSize, ' ')) {}

    /*******************************************************************************
    *  Setter, Getter of CaroBoard
    *******************************************************************************/
    /**
     * @brief Get the symbol at the specified coordinates (row, col) on the board.
     *
     * @param row The row index of the position.
     * @param col The column index of the position.
     * @return The symbol (X or O) at the specified coordinates.
     */
    char getMove(vector<vector<char>> board, int row, int col);

    /**
     * @brief Create a move X or O: player (X) -- symbol = 'X', player (O) -- symbol = 'O'.
     *
     * @param row The row index of the position to place the move.
     * @param col The column index of the position to place the move.
     * @param symbol The symbol of the move (X or O).
     */
    void setMove(vector<vector<char>>& board, int row, int col, char symbol);

    /*******************************************************************************
    *  Methods of CaroBoard
    *******************************************************************************/
    /**
     * @brief Check if the position (row, col) on the board is empty.
     *
     * @param row The row index of the position.
     * @param col The column index of the position.
     * @return True if the position is empty, otherwise false.
     */
    bool isCellEmpty(vector<vector<char>> board, int row, int col);

    /**
     * @brief Check if the board is full.
     *
     * @return True if the board is full, otherwise false.
     */
    bool isBoardFull(vector<vector<char>> board);


    /**
     * @brief Draw the board, displaying all the chess pieces and the grid.
     */
    void drawBoard(vector<vector<char>> board);

    void setColor(int color);

    /**
     * @brief Reset a cell at position (row, col) on the board to empty.
     *
     * @param row The row index of the cell to reset.
     * @param col The column index of the cell to reset.
     */
    void resetCell(vector<vector<char>> board, int row, int col);

    /**
     * @brief Clear the board, resetting all cells to empty to start a new game.
     */
    void resetBoard(vector<vector<char>>& board);

    /**
     * @brief Display the current state of the board, showing all the chess pieces and the grid.
     */
    void showBoard(vector<vector<char>>& board);

    /**
     * @brief Check for a winner on the board.
     *
     * @return The symbol (X or O) of the winner if there is one, otherwise returns ' ' (space).
     */
    char checkWinner(vector<vector<char>> board);
};
