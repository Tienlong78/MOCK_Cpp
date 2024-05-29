/*******************************************************************************
* LIBRARY
*******************************************************************************/
#include "GameCaro.h"
#include <string>
#include <sstream>
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
 * @brief Constructor initializes the game
 */
Game::Game() {
    pBoard = new BOARD();
    player1 = nullptr;
    player2 = nullptr;
    bot = nullptr;
    gameover = false;
}

/**
 * @brief Destructor to clean up dynamically allocated memory
 */
Game::~Game() {
    delete pBoard;
    delete player1;
    delete player2;
    delete bot;
}

/**
 * @brief Save player information to a file
 * @param filename The name of the file to save player information
 */
void Game::saveInfoPlayers(const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Cannot open file for writing!" << endl;
        return;
    }

    /** Iterate over the vector of players and save their information **/
    for (const auto& player : players) {
        outFile << player->getName() << " " << player->getWinNums() << " "
            << player->getLoseNums() << " " << player->getDrawNums() << " " << endl;
    }

    /** Close file **/
    outFile.close();
    cout << "Player information saved to " << filename << endl;
}

/**
 * @brief Print player information from a file
 * @param filename The name of the file to read player information
 */
void Game::printInfoPlayer(const string& filename) {
    string playerName;
    int wins, losses, draws;
    ifstream playerFile(filename);

    if (!playerFile) {
        cout << "Cannot open game file." << endl;
        return;
    }

    cout << "Player's Information" << endl;
    cout << "---------------------" << endl;
    cout << setw(15) << "Name" << setw(15) << "Wins" << setw(15)
        << "Loses" << setw(15) << "Draws" << endl;

    /** Read and display player information **/
    while (playerFile >> playerName >> wins >> losses >> draws) {
        cout << setw(15) << playerName << setw(15) << wins << setw(15)
            << losses << setw(15) << draws << endl;
    }

    /** Close file **/
    playerFile.close();
    system("pause");
}
void Game::searchPlayerByName(const string& fileName, const string& playerName) {
    string line;
    bool playerFound = false;
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Unable to open file " << fileName << endl;
        return;
    }

    while (getline(file, line)) {
        // Tìm vị trí của dấu cách đầu tiên
        size_t pos = line.find(' ');
        if (pos == string::npos) {
            // Dòng không có dấu cách, bỏ qua
            continue;
        }

        // Tách tên người chơi từ dòng
        string playerNameFromFile = line.substr(0, pos);
        if (playerNameFromFile == playerName) {
            system("cls");
            // Nếu tên người chơi trùng khớp, in thông tin và kết thúc vòng lặp
            cout << "Player information:" << endl;
            cout << "Name: " << playerNameFromFile << endl;
            cout << "Win numbers : " << line.substr(pos + 1, line.find(' ', pos + 1) - pos - 1) << endl;
            cout << "Lose numbers : " << line.substr(line.find(' ', pos + 1) + 1, line.find(' ', line.find(' ', pos + 1) + 1) - line.find(' ', pos + 1) - 1) << endl;
            cout << "Draw numbers : " << line.substr(line.find(' ', line.find(' ', pos + 1) + 1) + 1) << endl;
            cout << "\n" << endl;
            playerFound = true;
            break;
        }
    }

    if (!playerFound) {
        cout << "Player with name '" << playerName << "' not found.\n";
    }

    file.close();
}



/**
 * @brief Read moves from a file and store them in vectors
 * @param filename The name of the file to read moves from
 * @param allMoves A reference to a vector of vectors to store all moves
 * @param allSymbols A reference to a vector of vectors to store all symbols
 */
void Game::readFileMove(const string& filename, vector<vector<pair<int, int>>>& allMoves, vector<vector<char>>& allSymbols) {
    string line;
    int row, col;
    char playerSymbol;
    int gameNumber = 0;
    vector<pair<int, int>> moves;
    vector<char> symbols;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return;
    }

    /** Read data from the file **/
    while (getline(file, line)) {
        if (line.rfind("Game", 0) == 0) {
            gameNumber++;
            cout << "Game " << gameNumber << endl;
            if (!moves.empty()) {
                allMoves.push_back(moves);
                allSymbols.push_back(symbols);
                moves.clear();
                symbols.clear();
            }
        }
        else {
            istringstream iss(line);
            if (iss >> row >> col >> playerSymbol) {
                moves.push_back({ row, col });
                symbols.push_back(playerSymbol);
            }
        }
    }

    /** Push the last game if not empty **/
    if (!moves.empty()) {
        allMoves.push_back(moves);
        allSymbols.push_back(symbols);
    }
    file.close();
}

/**
 * @brief Watch the play of a specific game from the saved moves
 * @param filename The name of the file to read moves from
 */
void Game::WatchPlay(const string& filename) {
    vector<vector<pair<int, int>>> allMoves;
    vector<vector<char>> allSymbols;
    int gameNumber = 0;
    char command;

    readFileMove(filename, allMoves, allSymbols);

    if (allMoves.empty()) {
        cout << "No moves found in the file." << endl;
        return;
    }

    cout << "Enter the game number to watch (1 to " << allMoves.size() << "): ";
    cin >> gameNumber;

    if (gameNumber < 1 || gameNumber > allMoves.size()) {
        cout << "Invalid game number." << endl;
        return;
    }

    vector<pair<int, int>>& moves = allMoves[gameNumber - 1];
    vector<char>& symbols = allSymbols[gameNumber - 1];

    int moveIndex = 0;
    while (true) {
        system("cls");
        pBoard->resetBoard(pBoard->board);

        /** Display moves up to the current move index **/
        for (int i = 0; i <= moveIndex; ++i) {
            if (moves[i].first != -1) {
                int row = moves[i].first;
                int col = moves[i].second;
                pBoard->board[row][col] = symbols[i];
            }
        }

        pBoard->drawBoard(pBoard->board);

        cout << "Game " << gameNumber << " - Step " << moveIndex + 1 << "/" << moves.size() << endl;
        cout << "Use 'n' for next, 'p' for previous, 'q' to quit: " << endl;
        cout << "Press your choice: ";
        cin >> command;

        if (command == 'n' && moveIndex < moves.size() - 1) {
            moveIndex++;
        }
        else if (command == 'p' && moveIndex > 0) {
            moveIndex--;
        }
        else if (command == 'q') {
            break;
        }
    }
}

/**
 * @brief Load player information from a file
 * @param filename The name of the file to read player information
 */
void Game::loadFilePlayer(const string& filename) {
    string playerName;
    int wins, losses, draws;
    char symbol;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return;
    }

    /** Read data from file and create player objects **/
    while (file >> playerName >> wins >> losses >> draws >> symbol) {
        Player* player = new Player(playerName, wins, losses, draws, symbol);
        players.push_back(player);
    }
    file.close();
}

/**
 * @brief Load moves from a file and update the board
 * @param filename The name of the file to read moves from
 */
void Game::loadFileMove(const string& filename) {
    string line;
    int row, col;
    char playerSymbol;
    istringstream iss(line);
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return;
    }

    /** Read moves from file and update the board **/
    while (getline(file, line)) {
        if (line.rfind("Game", 0) == 0) {
            continue;
        }

        if (iss >> row >> col >> playerSymbol) {
            if (row >= 0 && row < pBoard->mSize && col >= 0 && col < pBoard->mSize) {
                pBoard->board[row][col] = playerSymbol;
            }
        }
    }
    file.close();
}

/**
 * @brief Set up player vs player game
 */
void Game::SetUpPvP() {
    gameover = false;
    string name1, name2;
    cout << "Player 1's name: ";
    cin.ignore();
    getline(cin, name1);
    cout << "Player 2's name: ";
    getline(cin, name2);

    player1 = new Player(name1, 0, 0, 0, PLAYER_X);
    player2 = new Player(name2, 0, 0, 0, PLAYER_O);

    players.push_back(player1);
    players.push_back(player2);
}

/**
 * @brief Set up player vs bot game
 */
void Game::SetUpPvB() {
    string name;

    cout << "Player's name: ";
    cin >> name;

    bot = new BotPlayer();
    player1 = new Player(name, WIN_NUMS_DEFALT, LOSE_NUMS_DEFALT, DRAW_NUMS_DEFALT, PLAYER_X);
    players.push_back(player1);
}


/**
 * @brief Exit the game
 */
void Game::exitGame() {
    gameover = true;
}

/**
 * @brief Check if the player wants to continue the game
 * @return True if the player wants to continue, false otherwise
 */
bool Game::isContinue() {
    char choice;
    cout << "Do you want to continue playing? (Y/N): ";
    cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        return true;
    }
    else if (choice == 'N' || choice == 'n') {
        return false;
    }
    return true;
}

/**
 * @brief Check if the game is over
 * @return True if the game is over, false otherwise
 */
bool Game::isGameOver() {
    return gameover;
}


/**
 * @brief Display the main menu options
 */
void Game::DisplayMainMenu() {
    cout << "*-------MAIN MENU-------*\n";
    cout << "1. Player with Other Player\n";
    cout << "2. Player with BOT\n";
    cout << "3. Watch play\n";
    cout << "4. Player's Infomation\n";
    cout << "5. Guild\n";
    cout << "6. Exit\n";
}

/**
 * @brief Display the player vs bot menu options
 */
void Game::DisplayPvB() {
    cout << "*-------PLAY with BOT-------*\n";
    cout << "1. Easy Mode\n";
    cout << "2. Normal Mode\n";
    cout << "3. Hard Mode\n";
    cout << "4. Back to MAIN MENU\n";
}

/**
 * @brief Get the pointer to the game board
 * @return Pointer to the BOARD object
 */
BOARD* Game::getBoardPtr() {
    return pBoard;
}

/**
 * @brief Get the pointer to the bot player
 * @return Pointer to the BotPlayer object
 */
BotPlayer* Game::getBotPtr() {
    return bot;
}

/**
 * @brief Play the game against the bot using Alpha-Beta pruning
 */
void Game::playPvB() {
    static int gameNumber = 0; /* Initialize the game number */

    /* Open the file to append moves */
    ofstream moveFile("Move.txt", ios::app);
    if (!moveFile.is_open()) {
        cout << "Cannot open file for writing!" << endl;
        return;
    }

    moveFile << "Game" << gameNumber++ << endl;         /* Write the game header */
    char curPlayerSymbol = player1->getPlayerSymbol();  /* Player 1 starts */
    int row, col;

    while (true) {
        system("cls");
        cout << "Player " << player1->getName() << " = X, Bot = O:\n\n";
        pBoard->drawBoard(pBoard->board);
        cout << (curPlayerSymbol == PLAYER_X ? player1->getName() : "Bot") << "'s turn: ";

        /******************* Player Turn *********************/
        if (curPlayerSymbol == player1->getPlayerSymbol()) {
            cin >> row >> col; /* Input move coordinates */

            /* Check if the move is valid */
            if (row < 0 || row >= BOARD_MAXSIZE || col < 0 || col >= BOARD_MAXSIZE || !pBoard->isCellEmpty(pBoard->board, row, col)) {
                cout << "Move is invalid" << endl;
                continue;
            }
            /* Write the move to the file */
            moveFile << row << " " << col << " " << curPlayerSymbol << endl;
            pBoard->setMove(pBoard->board, row, col, curPlayerSymbol); /* Set the move on the board */
        }
        else { /********************* BOT turn ****************************/
            /* BOT finds the best move */
            pair<int, int> bestMove = bot->findBestMove(pBoard->board, bot->getBotSymbol());
            /* Set the move on the board */
            pBoard->setMove(pBoard->board, bestMove.first, bestMove.second, bot->getBotSymbol());

            /* Write the move to the file */
            moveFile << bestMove.first << " " << bestMove.second << " " << bot->getBotSymbol() << endl;
        }

        char winner = pBoard->checkWinner(pBoard->board); /* Check for winner */
        if (winner != ' ') {
            system("cls");
            pBoard->drawBoard(pBoard->board);
            if (winner == player1->getPlayerSymbol()) { /* Player 1 wins */
                cout << "Player " << player1->getName() << " wins! Congratulations!" << endl;
                player1->setWinNums(player1->getWinNums() + 1);
            }
            else {  /* Bot wins */
                cout << "Bot wins!" << endl;
                player1->setLoseNums(player1->getLoseNums() + 1);
            }
            moveFile.close(); /* Close the file */
            break;
        }
        else if (pBoard->isBoardFull(pBoard->board)) { /*  Draw */
            system("cls");
            pBoard->drawBoard(pBoard->board);
            cout << "The game ended in a draw." << endl;
            player1->setDrawNums(player1->getDrawNums() + 1);
            moveFile.close(); /* Close the file */
            break;
        }
        curPlayerSymbol = (curPlayerSymbol == PLAYER_X) ? PLAYER_O : PLAYER_X; /* Switch turns */
    }
}

/**
 * @brief Play the game player vs player with move saving
 */
void Game::playPvP() {
    static int gameNumber = 0; /* Initialize the game number */

    /* Open the file to append moves */
    ofstream moveFile("Move.txt", ios::app);
    if (!moveFile.is_open()) {
        cout << "Cannot open file for writing!" << endl;
        return;
    }

    moveFile << "Game" << gameNumber++ << endl; /* Write the game header */
    char curPlayerSymbol = player1->getPlayerSymbol();  /* Player 1 starts */
    int row, col;

    while (true) {
        system("cls");
        cout << "Player " << player1->getName() << " = X, Player " << player2->getName() << " = O:\n\n";
        pBoard->drawBoard(pBoard->board);
        cout << "Player " << (curPlayerSymbol == PLAYER_X ? player1->getName() : player2->getName()) << "'s turn: ";
        cin >> row >> col;

        /* Check if the move is valid and write to the file */
        if (row >= 0 && row < BOARD_MAXSIZE && col >= 0 && col < BOARD_MAXSIZE && pBoard->isCellEmpty(pBoard->board, row, col)) {
            moveFile << row << " " << col << " " << curPlayerSymbol << endl;
            pBoard->setMove(pBoard->board, row, col, curPlayerSymbol); /* Set the move on the board */

            /* Check for winner */
            char winner = pBoard->checkWinner(pBoard->board);
            if (winner != ' ') {
                system("cls");
                pBoard->drawBoard(pBoard->board);

                /* Player 1 wins */
                if (winner == player1->getPlayerSymbol()) {
                    cout << "Player " << player1->getName() << " wins! Congratulations!" << endl;
                    player1->setWinNums(player1->getWinNums() + 1);
                    player2->setLoseNums(player2->getLoseNums() + 1);
                }
                /* Player 2 wins */
                else {
                    cout << "Player " << player2->getName() << " wins! Congratulations!" << endl;
                    player2->setWinNums(player2->getWinNums() + 1);
                    player1->setLoseNums(player1->getLoseNums() + 1);
                }

                moveFile.close(); /* Close the file */
                break;
            }
            else if (pBoard->isBoardFull(pBoard->board)) {  /* Draw */
                system("cls");
                pBoard->drawBoard(pBoard->board);
                cout << "The game ended in a draw." << endl;
                player1->setDrawNums(player1->getDrawNums() + 1);
                player2->setDrawNums(player2->getDrawNums() + 1);

                moveFile.close(); /* Close the file */
                break;
            }
            /* Switch turns */
            curPlayerSymbol = (curPlayerSymbol == PLAYER_X) ? PLAYER_O : PLAYER_X;
        }
        else {
            cout << "Move is invalid" << endl;
        }
    }
}