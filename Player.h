#pragma once
/*******************************************************************************
* LIBRARY
******************************************************************************/
#include <iostream>
#include <string>
using namespace std;

/*******************************************************************************
* Definitions
******************************************************************************/
#define WIN_NUMS_DEFALT      (0) /**< Default number of wins */
#define LOSE_NUMS_DEFALT     (0) /**< Default number of losses */
#define DRAW_NUMS_DEFALT     (0) /**< Default number of draws */

/*******************************************************************************
* Variables
******************************************************************************/

/*******************************************************************************
* Class Game
******************************************************************************/
class Player {
private:
    string mName; /**< Player's name */
    int mWinNums; /**< Number of wins */
    int mLoseNums; /**< Number of losses */
    int mDrawNums; /**< Number of draws */
    char mPlayerSymbol; /**< Symbol of the player */

public:
    /** @brief Default constructor */
    Player();

    /**
     * @brief Constructor with parameters
     * @param name Player's name
     * @param winNums Number of wins
     * @param loseNums Number of losses
     * @param drawNums Number of draws
     * @param symbol Player's symbol
     */
    Player(const string& name, int winNums, int loseNums, int drawNums, char symbol);



    /* Getter, Setter */
    /** @brief Get the player's name */
    string getName() const;

    /** @brief Get the number of wins */
    int getWinNums() const;

    /** @brief Get the number of losses */
    int getLoseNums() const;

    /** @brief Get the number of draws */
    int getDrawNums() const;

    /** @brief Get the player's symbol */
    char getPlayerSymbol() const;

    /** @brief Set the player's name */
    void setName(const string& name);

    /** @brief Set the number of wins */
    void setWinNums(int winNums);

    /** @brief Set the number of losses */
    void setLoseNums(int loseNums);

    /** @brief Set the number of draws */
    void setDrawNums(int draw);

    /** @brief Set the player's symbol */
    void setPlayerSymbol(char symbol);
};
