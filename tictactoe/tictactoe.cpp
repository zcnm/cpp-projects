/* 
Title: Tic Tac Toe
Author: Edmund Chow
Date: 28/02/22
Description: tictactoe game
*/

#include <iostream>
#include <vector>

using namespace std;

// Constants
const int BOARD_SIZE = 3;
const char PLAYER_ONE = 'X';
const char PLAYER_TWO = 'O';
const char BLANK_SPACE = '_';

// Function prototypes
vector<vector<char>> initialiseBoard();
void printBoard(vector<vector<char>> board);
vector<vector<char>> makeTurn(int row, int col, vector<vector<char>> board, char symbol);
vector<vector<char>> playerTurn(char symbol, vector<vector<char>> board);
bool checkBoard(vector<vector<char>> board);
bool checkMove(int row, int col, vector<vector<char>> board);
bool allEqual(vector<char> row);
vector<vector<char>> transposeVector(vector<vector<char>> originalVector);

int main()
{
    vector<vector<char>> board = initialiseBoard();
    printBoard(board);
    // game loop
    while (true)
    {
        board = playerTurn(PLAYER_ONE, board);
        printBoard(board);
        if (checkBoard(board))
        {
            break;
        }

        board = playerTurn(PLAYER_TWO, board);
        printBoard(board);
        if (checkBoard(board))
        {
            break;
        }
    }
    return 0;
}

/** 
 * @brief Check for gameover state (if a player has won or if game is a draw).
 * Function will print winner/draw before return
 * 
 * @param board 2d vector of board state
 * @return bool true if game is over, otherwise false
 */
bool checkBoard(vector<vector<char>> board)
{
    // check rows
    for (vector<char> row : board)
    {
        if (*row.begin() != BLANK_SPACE)
        {
            if (allEqual(row))
            {
                cout << "Player " << *row.begin() << " Wins!\n";
                return true;
            }
        }
    }
    // check cols
    vector<vector<char>> transposedBoard = transposeVector(board);
    for (vector<char> row : transposedBoard)
    {
        if (*row.begin() != BLANK_SPACE)
        {
            if (allEqual(row))
            {
                cout << "Player " << *row.begin() << " Wins!\n";
                return true;
            }
        }
    }
    // check diagonals
    vector<char> topLeftDiagonal;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        topLeftDiagonal.push_back(board[i][i]);
    }

    if (*topLeftDiagonal.begin() != BLANK_SPACE)
    {
        if (allEqual(topLeftDiagonal))
        {
            cout << "Player " << *topLeftDiagonal.begin() << " Wins!\n";
            return true;
        }
    }

    vector<char> bottomLeftDiagonal;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        bottomLeftDiagonal.push_back(board[i][BOARD_SIZE - 1 - i]);
    }

    if (*bottomLeftDiagonal.begin() != BLANK_SPACE)
    {
        if (allEqual(bottomLeftDiagonal))
        {
            cout << "Player " << *bottomLeftDiagonal.begin() << " Wins!\n";
            return true;
        }
    }

    // check draw
    for (vector<char> row : board)
    {
        for (char elem : row)
        {
            // draw occurs when all spaces are filled (no blanks)
            if (elem == BLANK_SPACE)
            {
                return false;
            }
        }
    }
    cout << "The game is a draw!\n";
    return true;
}
/**
 * @brief returns a copy of a 2d vector with rows and columns swapped
 * 
 * @param originalVector 2d vector to transpose
 * @return vector<vector<char>> transposed vector
 */
vector<vector<char>> transposeVector(vector<vector<char>> originalVector)
{
    int rowLen = originalVector.size();
    int colLen = originalVector[0].size();

    vector<vector<char>> tVector(colLen, vector<char>());

    for (int i = 0; i < rowLen; i++)
    {
        for (int j = 0; j < colLen; j++)
        {
            tVector[j].push_back(originalVector[i][j]);
        }
    }
    return tVector;
}
/**
 * @brief checks if all elements in a vector are equal
 * 
 * @param row 1d vector
 * @return true if all elements are equal
 * @return false otherwise
 */
bool allEqual(vector<char> row)
{
    for (char elem : row)
    {
        if (elem != *row.begin())
        {
            return false;
        }
    }
    return true;
}
/**
 * @brief initialises an empty tictactoe board
 * 
 * @return vector<vector<char>> 2d vector of blank spaces
 */
vector<vector<char>> initialiseBoard()
{
    vector<vector<char>> board(BOARD_SIZE, vector<char>(BOARD_SIZE, BLANK_SPACE));
    return board;
}

void printBoard(vector<vector<char>> board)
{
    for (vector<char> row : board)
    {
        for (char pos : row)
        {
            cout << pos << " ";
        }
        cout << '\n';
    }
}
/**
 * @brief handles logic for each player turn
 * 
 * @param symbol the character the current player is representing (X or O)
 * @param board 2d vector denoting board state
 * @return vector<vector<char>> updated board state after play
 */
vector<vector<char>> playerTurn(char symbol, vector<vector<char>> board)
{
    while (true)
    {
        cout << "Player " << symbol << "'s turn.\n Please enter a row col to place your tile: ";
        int row, col;
        cin >> row;
        cin >> col;
        cout << "You chose to place a " << symbol << " onto tile (" << row << ", " << col << ").\n";
        //validate move
        if (checkMove(row, col, board))
        {
            board = makeTurn(row, col, board, symbol);
            return board;
        }
        //if move invalid, let player try again to make valid move
        printBoard(board);
    }
}
/**
 * @brief updates board state after valid move is made
 * 
 * @param row 
 * @param col 
 * @param board 
 * @param symbol 
 * @return vector<vector<char>> 
 */
vector<vector<char>> makeTurn(int row, int col, vector<vector<char>> board, char symbol)
{
    board[row][col] = symbol;
    return board;
}

/**
 * @brief check if move made is valid
 * 
 * @param row 
 * @param col 
 * @param board 
 * @return true for valid move
 * @return false if move is invalid
 */
bool checkMove(int row, int col, vector<vector<char>> board)
{
    //check that row and col are within bounds of bord
    if (row < 0 or row >= BOARD_SIZE)
    {
        cout << "Invalid move. Row needs to be between 0 and " << BOARD_SIZE - 1 << " Please try again.\n";
        return false;
    }
    if (col < 0 or col >= BOARD_SIZE)
    {
        cout << "Invalid move. Col needs to be between 0 and " << BOARD_SIZE - 1 << " Please try again.\n";
        return false;
    }

    //check that position has not already been taken
    if (board[row][col] != BLANK_SPACE)
    {
        cout << "Invalid move. Position already taken."
             << " Please try again.\n";
        return false;
    }
    return true;
}
