/*******************************************************************************
Project name : CPP.MockProject01.P001
Session      : Caro Game
Version      : 1.0
Author       : LongNT98
Content      : Create a C++ Console application Caro.
******************************************************************************/
/*******************************************************************************
* LIBRARY
******************************************************************************/
#include "GameCaro.h"
using namespace std;

/*******************************************************************************
* Definitions
******************************************************************************/

/*******************************************************************************
* Variables
******************************************************************************/

/*******************************************************************************
* API
******************************************************************************/

/*******************************************************************************
* MAIN
******************************************************************************/
int main() {
    Game game;
    bool exitProgram = false;                  /* Variable to exit the program */
    int level;
    game.loadFilePlayer("player.txt");
    game.loadFileMove("Move.txt");

    while (!exitProgram) {
        system("cls");
        game.DisplayMainMenu();
        int choice;
        cout << "Press number to choice: ";
        cin >> choice;

        switch (choice) {
            case 1: { /* Play with another player */
                system("cls");
                game.SetUpPvP();                     /* Enter the names of 2 players */
                game.getBoardPtr()->resetBoard(game.getBoardPtr()->board);    /* Reset the board for a new game */

                while (!game.isGameOver()) {
                    game.getBoardPtr()->resetBoard(game.getBoardPtr()->board);
                    game.playPvP();                   /* Main function for Player vs Player */
                    if (game.isContinue()) {          /* Ask if they want to continue */
                        game.saveInfoPlayers("player.txt");   /* if continue, save */
                    }
                    else {
                        game.saveInfoPlayers("player.txt");
                        game.exitGame();
                    }
                }
                break;
            }
            case 2: {  /* Play with BOT */
                system("cls");

                game.SetUpPvB();
                game.DisplayPvB();
                
                cout << "Press number to choice: "; /* Select BOT level */
                cin >> level;

                switch (level) {
                case 1: {  /* Easy */
                    game.getBotPtr()->setLevel(EASY); /* Set level for BOT */

                    while (!game.isGameOver()) {
                        game.playPvB();         /***  ===> Main function to play with BOT ***/
                        game.getBoardPtr()->resetBoard(game.getBoardPtr()->board);
                        /* If they want to play again with BOT easy, choose Y(y), otherwise choose N(n) */
                        if (game.isContinue()) {
                            game.saveInfoPlayers("player.txt");
                        }
                        else {
                            game.saveInfoPlayers("player.txt");
                            game.exitGame();
                        }
                    }
                    break;
                }
                case 2: { /* Medium */
                    game.getBotPtr()->setLevel(MEDIUM); /* Set level for BOT */

                    while (!game.isGameOver()) {
                        game.playPvB();
                        game.getBoardPtr()->resetBoard(game.getBoardPtr()->board);
                        if (game.isContinue()) {
                            game.saveInfoPlayers("player.txt");
                            game.getBoardPtr()->resetBoard(game.getBoardPtr()->board);
                        }
                        else {
                            game.saveInfoPlayers("player.txt");
                            game.exitGame();
                        }
                    }
                    break;
                }
                case 3: { /* Hard */
                    game.getBotPtr()->setLevel(HARD); /* Set level for BOT */

                    while (!game.isGameOver()) {
                        game.playPvB();
                        game.getBoardPtr()->resetBoard(game.getBoardPtr()->board);
                        if (game.isContinue()) {
                            game.saveInfoPlayers("player.txt");
                            game.getBoardPtr()->resetBoard(game.getBoardPtr()->board);
                        }
                        else {
                            game.saveInfoPlayers("player.txt");
                            game.exitGame();
                        }
                    }
                    break;
                }
                case 4: { /* Back to MENU */
                    break;
                }
                default: {
                    cout << "Invalid level choice, please try again." << endl;
                    break;
                }
                }
                break;
            }
            case 3: {  /* Watch play */
                system("cls");
                game.WatchPlay("Move.txt");
                break;
            }
            case 4: {  /* Player's Information */
                system("cls");
                do {
                    cout << "1. Print all players\n";
                    cout << "2. Search player by name\n";
                    cout << "3. Quit\n";
                    cout << "Enter your choice: ";
                    cin >> choice;
                    system("cls");
                    switch (choice) {
                    case 1: { /* Print all players */
                        game.printInfoPlayer("player.txt");
                        break;
                    }
                    case 2: { /* Search player by name */
                        string playerName;
                        cout << "Enter player name: ";
                        cin.ignore();
                        getline(cin, playerName);
                        game.searchPlayerByName("player.txt", playerName);
                        break;
                    }
                    case 3: { /* Quit */
                        cout << "Quitting...\n";
                        break;
                    }
                    default: {
                        cout << "Invalid choice. Please try again.\n";
                        break;
                    }
                    }
                } while (choice != 3);
                break;
            }

            case 5: {  /* Guide */
                system("cls");
                cout << "Welcome to Caro! Here are the rules and winning conditions:\n";
                cout << "1. Caro is a two-player game played on a square grid board.\n";
                cout << "2. Players take turns placing their symbols (X or O) on empty squares.\n";
                cout << "3. The first player to get four of their symbols in a row (horizontally, vertically, or diagonally) wins the game.\n";
                cout << "4. If there are two or more consecutive symbols of the same player with empty cells at both ends, it is not considered a win.\n";
                cout << "5. The game ends in a draw if all cells are filled and no player has won.\n";
                cout << "6. Enjoy the game and good luck!\n\n";
                system("pause");
                break;
            }
            case 6: {  /* Exit Program */
                system("cls");
                exitProgram = true;
                cout << "Exit Program.";
                break;
            }
            default: {
                cout << "Invalid choice, please try again." << endl;
                break;
            }
        }
    }
    return 0;
}
