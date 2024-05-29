/*******************************************************************************
* LIBRARY
*******************************************************************************/
#include "Player.h"
using namespace std;

/*******************************************************************************
* Definitions
******************************************************************************/

/*******************************************************************************
* Variables
******************************************************************************/

/*******************************************************************************
* Code
******************************************************************************/
/**
 * @brief Default constructor for Player class
 */
Player::Player() : mWinNums(WIN_NUMS_DEFALT), mLoseNums(LOSE_NUMS_DEFALT), mDrawNums(DRAW_NUMS_DEFALT), mPlayerSymbol('X') { }

/**
 * @brief Parameterized constructor for Player class with full information
 * @param name The name of the player
 * @param winNums Number of wins for the player
 * @param loseNums Number of losses for the player
 * @param drawNums Number of draws for the player
 * @param symbol The symbol representing the player on the game board
 */
Player::Player(const string& name, int winNums, int loseNums, int drawNums, char symbol)
    : mName(name), mWinNums(winNums), mLoseNums(loseNums), mDrawNums(drawNums), mPlayerSymbol(symbol) {}

///**
// * @brief Parameterized constructor for Player class with partial information
// * @param name The name of the player
// * @param winNums Number of wins for the player
// * @param loseNums Number of losses for the player
// * @param drawNums Number of draws for the player
// */
//Player::Player(const string& name, int winNums, int loseNums, int drawNums)
//    : mName(name), mWinNums(winNums), mLoseNums(loseNums), mDrawNums(drawNums) {}

/**
 * @brief Get the name of the player
 * @return The name of the player
 */
string Player::getName() const {
    return mName;
}

/**
 * @brief Set the name of the player
 * @param name The name of the player
 */
void Player::setName(const string& name) {
    this->mName = name;
}

/**
 * @brief Set the number of losses for the player
 * @param loseNums Number of losses for the player
 */
void Player::setLoseNums(int loseNums) {
    this->mLoseNums = loseNums;
}

/**
 * @brief Set the number of draws for the player
 * @param draw Number of draws for the player
 */
void Player::setDrawNums(int draw) {
    this->mDrawNums = draw;
}

/**
 * @brief Get the symbol representing the player on the game board
 * @return The symbol representing the player
 */
char Player::getPlayerSymbol() const {
    return mPlayerSymbol;
}

/**
 * @brief Set the symbol representing the player on the game board
 * @param symbol The symbol representing the player
 */
void Player::setPlayerSymbol(char symbol) {
    this->mPlayerSymbol = symbol;
}

/**
 * @brief Set the number of wins for the player
 * @param winNums Number of wins for the player
 */
void Player::setWinNums(int winNums) {
    this->mWinNums = winNums;
}

/**
 * @brief Get the number of wins for the player
 * @return The number of wins for the player
 */
int Player::getWinNums() const {
    return mWinNums;
}

/**
 * @brief Get the number of losses for the player
 * @return The number of losses for the player
 */
int Player::getLoseNums() const {
    return mLoseNums;
}

/**
 * @brief Get the number of draws for the player
 * @return The number of draws for the player
 */
int Player::getDrawNums() const {
    return mDrawNums;
}
