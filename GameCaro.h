#pragma once
/*******************************************************************************
* LIBRARY
******************************************************************************/
#include <iostream>
#include <fstream>
#include "BotPlayer.h"
#include "Player.h"
#include <iomanip>
using namespace std;

/*******************************************************************************
* Definitions
******************************************************************************/

/*******************************************************************************
* Variables
******************************************************************************/

/*******************************************************************************
* Class Game
******************************************************************************/
class Game {
private:
    BOARD* pBoard; /**< Pointer to the game board */
    vector<Player*> players; /**< Vector containing player information */
    Player* player1; /**< Pointer to Player 1 */
    Player* player2; /**< Pointer to Player 2 */
    BotPlayer* bot; /**< Pointer to the Bot player */
    bool gameover; /**< Variable to determine game over */

public:
    /** @brief Constructor */
    Game();

    /** @brief Destructor */
    ~Game();

    /**
     * @brief Get pointer to the game board
     * @return Pointer to the game board
     */
    BOARD* getBoardPtr();

    /**
     * @brief Get pointer to the Bot player
     * @return Pointer to the Bot player
     */
    BotPlayer* getBotPtr();

    /** @brief Set up for Player vs Player */
    void SetUpPvP();

    /** @brief Set up for Player vs Bot */
    void SetUpPvB();

    /** @brief Exit the game */
    void exitGame();

    /**
     * @brief Check if the player wants to continue
     * @return True if the player wants to continue, false otherwise
     */
    bool isContinue();
    /**
     * @brief Check if the game is over
     * @return True if the game is over, false otherwise
     */
    bool isGameOver();

    /** @brief Play Player vs Player */
    void playPvP();

    /** @brief Play Player vs Bot */
    void playPvB();

    /** @brief Display the main menu */
    void DisplayMainMenu();

    /** @brief Display the Player vs Bot screen */
    void DisplayPvB();

    /**
     * @brief Save player information to the game.txt file
     * @param filename The name of the file to save to
     */
    void saveInfoPlayers(const string& filename);

    /**
     * @brief Print player information
     * @param filename The name of the file containing player information
     */
    void printInfoPlayer(const string& filename);

    /**
     * @brief Print the moves of the game
     * @param filename The name of the file containing the moves
     */
    void WatchPlay(const string& filename);

    /**
     * @brief Load player data
     * @param filename The name of the file containing player data
     */
    void loadFilePlayer(const string& filename);

    /**
     * @brief Load moves of both players
     * @param filename The name of the file containing the moves
     */
    void loadFileMove(const string& filename);

    /**
     * @brief Read moves from file
     * @param filename The name of the file containing the moves
     * @param allMoves Vector to store all moves
     * @param allSymbols Vector to store all symbols
     */
    void readFileMove(const string& filename, vector<vector<pair<int, int>>>& allMoves, vector<vector<char>>& allSymbols);

    void searchPlayerByName(const string& fileName, const string& playerName);

};
