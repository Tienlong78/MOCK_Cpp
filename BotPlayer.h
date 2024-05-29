#pragma once
/*******************************************************************************
* LIBRARY
*******************************************************************************/
#include <iostream>
#include "Board.h"
using namespace std;

/*******************************************************************************
* Definition
*******************************************************************************/
#define WIN_POINT                   (1000000)
#define LOSE_POINT                  (-1000000)
#define BOT_THREE_OPEN_POINT        (10000)
#define PLAYER_THREE_OPEN_POINT     (-10000)
#define BOT_THREE_BLOCKED_POINT     (1000)
#define PLAYER_THREE_BLOCKED_POINT  (-1000)
#define BOT_TWO_POINT               (100)
#define PLAYER_TWO_POINT            (-100)
#define BOT_TWO_BLOCKED_POINT       (10)
#define PLAYER_TWO_BLOCKED_POINT    (-10)

/**< Enum representing different levels of the bot */
enum BOT_Level {
    EASY = 1,
    MEDIUM = 2,
    HARD = 3,
};

/*******************************************************************************
* Class BotPlayer
*******************************************************************************/
class BotPlayer : public BOARD {
private:
    char mBotSymbol; /*The symbol of the bot ('X' or 'O')*/
    BOARD* pBoard;   /*Pointer to caro board use methods of the board class*/
    BOT_Level level; /*The level of the bot*/
public:
    /**
     * @brief Default constructor.
     */
    BotPlayer();

    /**
     * @brief Constructor to initialize BotPlayer with a symbol and level.
     *
     * @param symbol The symbol ('X' or 'O') representing the bot.
     * @param level The level of the bot (EASY, MEDIUM, or HARD).
     */
    BotPlayer(BOARD* pBoard, char symbol, BOT_Level level);

    /**
     * @brief Destructor.
     */
    ~BotPlayer();

    /**
     * @brief Calculate the score based on the counts of symbols.
     *
     * @param c_botCount The count of symbols belonging to the bot.
     * @param c_playerCount The count of symbols belonging to the player.
     * @return The calculated score.
     */
    int scoreCalculate(int c_botCount, int c_playerCount, bool isBotBlocked, bool isPlayerBlocked);

    bool isAroundOpponentMove(const vector<vector<char>>& board, int row, int col, char symbol);

    /**
     * @brief Evaluates the board state for a given symbol.
     *
     * @param board The current game board as a 2D vector of characters.
     * @param symbol The symbol ('X' or 'O') for which to evaluate the board.
     * @param depth The current depth in the game tree.
     * @return The evaluation score of the board state.
     */
    int evaluate(vector<vector<char>> board, char symbol, int depth);

    /**
     * @brief Implements the MiniMax algorithm with alpha-beta pruning.
     *
     * @param board The current game board as a 2D vector of characters.
     * @param depth The current depth in the game tree.
     * @param isMaximizing A boolean indicating whether the current move is maximizing or minimizing.
     * @param alpha The alpha value for alpha-beta pruning.
     * @param beta The beta value for alpha-beta pruning.
     * @param symbol The symbol ('X' or 'O') for which to run the MiniMax algorithm.
     * @return The best score for the current player.
     */
    int miniMax(vector<vector<char>> board, int depth, bool isMaximizing, int alpha, int beta, char symbol);

    /**
     * @brief Finds the best move for the current player.
     *
     * @param board The current game board as a 2D vector of characters.
     * @param symbol The symbol ('X' or 'O') for which to find the best move.
     * @return A pair of integers representing the row and column of the best move.
     */
    pair<int, int> findBestMove(vector<vector<char>> board, char symbol);

    /**
     * @brief Get the symbol of the bot.
     *
     * @return The symbol of the bot ('X' or 'O').
     */
    char getBotSymbol();

    /**
     * @brief Get the level of the bot.
     *
     * @return The level of the bot (EASY, MEDIUM, or HARD).
     */
    BOT_Level getLevel();

    /**
     * @brief Get the pointer to the board.
     *
     * @return A pointer to the board.
     */
    BOARD* getBoardPtr();

    /**
     * @brief Set the level of the bot.
     *
     * @param level The level of the bot (EASY, MEDIUM, or HARD).
     */
    void setLevel(BOT_Level level);
};
