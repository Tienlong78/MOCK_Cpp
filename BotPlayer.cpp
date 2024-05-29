/*******************************************************************************
* LIBRARY
*******************************************************************************/
#include "BotPlayer.h"

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
 * @brief Default constructor for BotPlayer. Initializes the bot's symbol to 'O', creates a new BOARD instance, and sets the difficulty level to EASY.
 */
BotPlayer::BotPlayer() : mBotSymbol(PLAYER_O), pBoard(new BOARD()), level(EASY) { }

/**
 * @brief Parameterized constructor for BotPlayer. Initializes the bot's symbol and difficulty level based on input parameters.
 * @param symbol The character symbol representing the bot (e.g., 'X' or 'O').
 * @param level The difficulty level of the bot (e.g., EASY, MEDIUM, HARD).
 */
BotPlayer::BotPlayer(BOARD* pBoard, char symbol, BOT_Level level)
    : pBoard(new BOARD()), mBotSymbol(PLAYER_O), level(level) { }

/**
 * @brief Destructor for BotPlayer. Deletes the dynamically allocated BOARD instance.
 */
BotPlayer::~BotPlayer() {
    delete pBoard;
}

/**
 * @brief Getter for the bot's symbol.
 * @return The character symbol representing the bot.
 */
char BotPlayer::getBotSymbol() {
    return mBotSymbol;
}

/**
 * @brief Getter for the bot's difficulty level.
 * @return The difficulty level of the bot.
 */
BOT_Level BotPlayer::getLevel() {
    return level;
}

/**
 * @brief Getter for the pointer to the BOARD instance.
 * @return Pointer to the BOARD instance used by the bot.
 */
BOARD* BotPlayer::getBoardPtr() {
    return pBoard;
}

/**
 * @brief Setter for the bot's difficulty level.
 * @param level The difficulty level to set for the bot.
 */
void BotPlayer::setLevel(BOT_Level level) {
    this->level = level;
}

/**
 * @brief Calculates the score based on the count of symbols in a potential winning line.
 *
 * @param botCount The count of the bot's symbols in a potential winning line.
 * @param c_botCount The count of the bot's consecutive symbols in a potential winning line.
 * @param playerCount The count of the player's symbols in a potential winning line.
 * @param c_playerCount The count of the player's consecutive symbols in a potential winning line.
 * @return The calculated score based on the given counts.
 */
int BotPlayer::scoreCalculate(int c_botCount, int c_playerCount, bool isBotBlocked, bool isPlayerBlocked) {
    int score = 0;

    // Ưu tiên chiến thắng
    if (c_botCount == WIN_CONDITION) {
        score += WIN_POINT;
    }
    else if (c_playerCount == WIN_CONDITION) {
        score += LOSE_POINT;
    }
    // 3 nước đi liên tiếp không bị chặn 2 đầu
    else if (c_botCount == WIN_CONDITION - 1 && !isBotBlocked) {
        score += BOT_THREE_OPEN_POINT;
    }
    else if (c_playerCount == WIN_CONDITION - 1 && !isPlayerBlocked) {
        score += PLAYER_THREE_OPEN_POINT; // Ưu tiên chặn nước đi 3 của đối thủ không bị chặn
    }
    // 3 nước đi liên tiếp bị chặn 1 đầu
    else if (c_botCount == WIN_CONDITION - 1 && isBotBlocked) {
        score += BOT_THREE_BLOCKED_POINT;
    }
    else if (c_playerCount == WIN_CONDITION - 1 && isPlayerBlocked) {
        score += PLAYER_THREE_BLOCKED_POINT; // Ưu tiên chặn nước đi 3 của đối thủ bị chặn một đầu
    }
    // 2 nước đi không bị chặn 2 đầu
    else if (c_botCount == WIN_CONDITION - 2 && !isBotBlocked) {
        score += BOT_TWO_POINT;
    }
    else if (c_playerCount == WIN_CONDITION - 2 && !isPlayerBlocked) {
        score += PLAYER_TWO_POINT; // Ưu tiên chặn nước đi 2 của đối thủ không bị chặn
    }
    // 2 nước đi bị chặn 1 đầu
    else if (c_botCount == WIN_CONDITION - 2 && isBotBlocked) {
        score += BOT_TWO_BLOCKED_POINT; // Ít điểm hơn so với không bị chặn
    }
    else if (c_playerCount == WIN_CONDITION - 2 && isPlayerBlocked) {
        score += PLAYER_TWO_BLOCKED_POINT; // Ưu tiên chặn nước đi 2 của đối thủ bị chặn một đầu
    }
    return score;
}


/**
 * @brief Evaluates the board state for a given symbol and depth.
 *
 * @param board The current game board as a 2D vector of characters.
 * @param symbol The symbol ('X' or 'O') for which to evaluate the board.
 * @param depth The current depth in the game tree.
 * @return The evaluation score of the board state.
 */
int BotPlayer::evaluate(vector<vector<char>> board, char symbol, int depth) {
    int score = 0;
    char opponentSymbol = (symbol == PLAYER_X) ? PLAYER_O : PLAYER_X;

    // Kiểm tra các hàng ngang
    for (int i = 0; i < BOARD_MAXSIZE; i++) {
        for (int j = 0; j <= BOARD_MAXSIZE - WIN_CONDITION; j++) {
            int c_botCount = 0;
            int c_playerCount = 0;
            bool isBotBlocked = false;
            bool isPlayerBlocked = false;

            for (int k = 0; k < WIN_CONDITION; k++) {
                if (board[i][j + k] == symbol) {
                    c_botCount++;
                }
                else if (board[i][j + k] != EMPTY) {
                    c_playerCount++;
                }
            }
            isBotBlocked = (j > 0 && board[i][j - 1] != EMPTY) || (j + WIN_CONDITION < BOARD_MAXSIZE && board[i][j + WIN_CONDITION] != EMPTY);
            isPlayerBlocked = isBotBlocked;

            score += scoreCalculate(c_botCount, c_playerCount, isBotBlocked, isPlayerBlocked);
        }
    }

    // Kiểm tra các cột dọc
    for (int j = 0; j < BOARD_MAXSIZE; j++) {
        for (int i = 0; i <= BOARD_MAXSIZE - WIN_CONDITION; i++) {
            int c_botCount = 0;
            int c_playerCount = 0;
            bool isBotBlocked = false;
            bool isPlayerBlocked = false;

            for (int k = 0; k < WIN_CONDITION; k++) {
                if (board[i + k][j] == symbol) {
                    c_botCount++;
                }
                else if (board[i + k][j] != EMPTY) {
                    c_playerCount++;
                }
            }
            isBotBlocked = (i > 0 && board[i - 1][j] != EMPTY) || (i + WIN_CONDITION < BOARD_MAXSIZE && board[i + WIN_CONDITION][j] != EMPTY);
            isPlayerBlocked = isBotBlocked;

            score += scoreCalculate(c_botCount, c_playerCount, isBotBlocked, isPlayerBlocked);
        }
    }

    // Kiểm tra các đường chéo chính (trái trên xuống phải dưới)
    for (int i = 0; i <= BOARD_MAXSIZE - WIN_CONDITION; i++) {
        for (int j = 0; j <= BOARD_MAXSIZE - WIN_CONDITION; j++) {
            int c_botCount = 0;
            int c_playerCount = 0;
            bool isBotBlocked = false;
            bool isPlayerBlocked = false;

            for (int k = 0; k < WIN_CONDITION; k++) {
                if (board[i + k][j + k] == symbol) {
                    c_botCount++;
                }
                else if (board[i + k][j + k] != EMPTY) {
                    c_playerCount++;
                }
            }
            isBotBlocked = (i > 0 && j > 0 && board[i - 1][j - 1] != EMPTY) || (i + WIN_CONDITION < BOARD_MAXSIZE && j + WIN_CONDITION < BOARD_MAXSIZE && board[i + WIN_CONDITION][j + WIN_CONDITION] != EMPTY);
            isPlayerBlocked = isBotBlocked;

            score += scoreCalculate(c_botCount, c_playerCount, isBotBlocked, isPlayerBlocked);
        }
    }

    // Kiểm tra các đường chéo phụ (phải trên xuống trái dưới)
    for (int i = 0; i <= BOARD_MAXSIZE - WIN_CONDITION; i++) {
        for (int j = WIN_CONDITION - 1; j < BOARD_MAXSIZE; j++) {
            int c_botCount = 0;
            int c_playerCount = 0;
            bool isBotBlocked = false;
            bool isPlayerBlocked = false;

            for (int k = 0; k < WIN_CONDITION; k++) {
                if (board[i + k][j - k] == symbol) {
                    c_botCount++;
                }
                else if (board[i + k][j - k] != EMPTY) {
                    c_playerCount++;
                }
            }
            isBotBlocked = (i > 0 && j < BOARD_MAXSIZE - 1 && board[i - 1][j + 1] != EMPTY) || (i + WIN_CONDITION < BOARD_MAXSIZE && j >= WIN_CONDITION && board[i + WIN_CONDITION][j - WIN_CONDITION] != EMPTY);
            isPlayerBlocked = isBotBlocked;

            score += scoreCalculate(c_botCount, c_playerCount, isBotBlocked, isPlayerBlocked);
        }
    }

    return score * (depth + 1);
}

/**
 * @brief MiniMax function with alpha-beta pruning to find the best move.
 *
 * @param board The current game board as a 2D vector of characters.
 * @param depth The current depth in the game tree.
 * @param maximizingPlayer A boolean indicating whether the current move is maximizing or minimizing.
 * @param alpha The alpha value for alpha-beta pruning.
 * @param beta The beta value for alpha-beta pruning.
 * @param symbol The symbol ('X' or 'O') for which to run the MiniMax algorithm.
 * @return The best score for the current player.
 */
int BotPlayer::miniMax(vector<vector<char>> board, int depth, bool maximizingPlayer, int alpha, int beta, char symbol) {
    char opponentSymbol = (PLAYER_X == symbol) ? PLAYER_O : PLAYER_X;

    /* Check if we reached a leaf node or the maximum depth */
    if (depth == 0 || checkWinner(board)) {
        return evaluate(board, symbol, depth);
    }
    if (isBoardFull(board))
        return 0;

    if (maximizingPlayer) {  /*  BOT đang là MAX */
        int bestVal = INT_MIN;

        /* Recurse for all child nodes */
        for (int i = 0; i < BOARD_MAXSIZE; i++) {
            for (int j = 0; j < BOARD_MAXSIZE; j++) {
                if (isCellEmpty(board, i, j)) {
                    board[i][j] = symbol;
                    int value = miniMax(board, depth - 1, false, alpha, beta, symbol);
                    board[i][j] = EMPTY;
                    bestVal = max(bestVal, value);
                    alpha = max(alpha, value);
                    if (beta <= alpha)  /* cắt tỉa alpha - belta */
                        break;
                }
            }
        }
        return bestVal;
    }
    else {   /* BOT đang là MIN */
        int bestVal = INT_MAX;

        /* Recurse for all child nodes */
        for (int i = 0; i < BOARD_MAXSIZE; i++) {
            for (int j = 0; j < BOARD_MAXSIZE; j++) {
                if (isCellEmpty(board, i, j)) {
                    board[i][j] = opponentSymbol;
                    int value = miniMax(board, depth - 1, true, alpha, beta, symbol);
                    board[i][j] = EMPTY;
                    bestVal = min(bestVal, value);
                    beta = min(beta, value);
                    if (beta <= alpha)
                        break;
                }
            }
        }
        return bestVal;
    }
}

/**
 * @brief Finds the best move for the current player using the MiniMax algorithm.
 *
 * @param board The current game board as a 2D vector of characters.
 * @param symbol The symbol ('X' or 'O') for which to find the best move.
 * @return A pair of integers representing the row and column of the best move.
 */
bool BotPlayer::isAroundOpponentMove(const vector<vector<char>>& board, int row, int col, char symbol) {
    // Duyệt qua vùng lân cận 3x3 của ô đó
    for (int i = row - 1; i <= row + 1; ++i) {
        for (int j = col - 1; j <= col + 1; ++j) {
            // Kiểm tra xem ô có hợp lệ trên bàn cờ không
            if (i >= 0 && i < BOARD_MAXSIZE && j >= 0 && j < BOARD_MAXSIZE) {
                // Kiểm tra xem ô đó có phải là ô của đối thủ không và không phải là ô trống
                if (board[i][j] != EMPTY && board[i][j] != symbol) {
                    return true; // Nếu có, trả về true
                }
            }
        }
    }
    return false; // Nếu không có ô nào trong vùng lân cận là ô của đối thủ, trả về false
}


pair<int, int> BotPlayer::findBestMove(vector<vector<char>> board, char symbol) {
    int bestVal = INT_MIN;              // đại diện cho giá trị tốt nhất mà MAX có thể đạt được từ tất cả các lựa chọn nước đi.
    pair<int, int> bestMove{ -1, -1 };  // Khởi tạo nước đi tốt nhất

    // Duyệt qua tất cả các ô trên bàn cờ
    for (int i = 0; i < BOARD_MAXSIZE; ++i) {
        for (int j = 0; j < BOARD_MAXSIZE; ++j) {
            // Kiểm tra ô có trống không và là ô xung quanh nước đi của đối thủ không
            if (isCellEmpty(board, i, j) && isAroundOpponentMove(board, i, j, symbol)) {
                // Thử đánh vào ô này
                board[i][j] = symbol;

                // Đánh giá nước đi sử dụng MiniMax
                int moveVal = miniMax(board, level, false, INT_MIN, INT_MAX, symbol);

                // Đặt lại ô
                board[i][j] = EMPTY;

                // Nếu điểm của nước đi này tốt hơn điểm tốt nhất đã thấy, cập nhật
                if (moveVal > bestVal) {
                    bestVal = moveVal;
                    bestMove = { i, j };
                }
            }
        }
    }
    return bestMove;
}
