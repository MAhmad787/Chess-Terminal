#include <iostream>
#include <string>
using namespace std;

// White and Black pieces (prefix w_ for white and b_ for black)
string w_king = "w_K";   // White King
string w_queen = "w_Q";  // White Queen
string w_rook = "w_R";   // White Rook
string w_knight = "w_H"; // White Knight
string w_bishop = "w_B"; // White Bishop
string w_pawn = "w_P";   // White Pawn

string b_king = "b_K";   // Black King
string b_queen = "b_Q";  // Black Queen
string b_rook = "b_R";   // Black Rook
string b_knight = "b_H"; // Black Knight
string b_bishop = "b_B"; // Black Bishop
string b_pawn = "b_P";   // Black Pawn

// White Positions
int w_king_position[2] = {7, 4};                                             // E1
int w_queen_position[2] = {7, 3};                                            // D1
int w_bishop_position[4] = {7, 2, 7, 5};                                     // C1, F1
int w_rook_position[4] = {7, 0, 7, 7};                                       // A1, H1
int w_knight_position[4] = {7, 1, 7, 6};                                     // B1, G1
int w_pawn_positions[16] = {6, 0, 6, 1, 6, 2, 6, 3, 6, 4, 6, 5, 6, 6, 6, 7}; // A2-H2

// Current Positions
int w_king_position_current[2] = {7, 4};                                             // E1
int w_queen_position_current[2] = {7, 3};                                            // D1
int w_bishop_position_current[4] = {7, 2, 7, 5};                                     // C1, F1
int w_rook_position_current[4] = {7, 0, 7, 7};                                       // A1, H1
int w_knight_position_current[4] = {7, 1, 7, 6};                                     // B1, G1
int w_pawn_positions_current[16] = {6, 0, 6, 1, 6, 2, 6, 3, 6, 4, 6, 5, 6, 6, 6, 7}; // A2-H2

// Black Positions
int b_king_position[2] = {0, 4};                                             // E8
int b_queen_position[2] = {0, 3};                                            // D8
int b_bishop_position[4] = {0, 2, 0, 5};                                     // C8, F8
int b_rook_position[4] = {0, 0, 0, 7};                                       // A8, H8
int b_knight_position[4] = {0, 1, 0, 6};                                     // B8, G8
int b_pawn_positions[16] = {1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7}; // A7-H7

// Current Positions
int b_king_position_current[2] = {0, 4};                                             // E8
int b_queen_position_current[2] = {0, 3};                                            // D8
int b_bishop_position_current[4] = {0, 2, 0, 5};                                     // C8, F8
int b_rook_position_current[4] = {0, 0, 0, 7};                                       // A8, H8
int b_knight_position_current[4] = {0, 1, 0, 6};                                     // B8, G8
int b_pawn_positions_current[16] = {1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7}; // A7-H7

void show_w_pawn_path(int w_pawn_initial_move[], int pawn_index, int row, int column, string chessboard[8][8])
{
    row--; // White pawns move upward

    // Check for the initial move (two squares forward allowed)
    if (w_pawn_initial_move[pawn_index] == 0)
    {
        // Check one square forward
        if (chessboard[row][column] == "[ ]")
        {
            chessboard[row][column] = "[*]";
        }
        // Check two squares forward, but only if the first square is empty
        if (row - 1 >= 0 && chessboard[row - 1][column] == "[ ]" && chessboard[row][column] == "[*]")
        {
            chessboard[row - 1][column] = "[*]";
        }
    }
    else
    {
        // Subsequent moves (one square forward only)
        if (chessboard[row][column] == "[ ]")
        {
            chessboard[row][column] = "[*]";
        }
    }
}

void show_b_pawn_path(int b_pawn_initial_move[], int pawn_index, int row, int column, string chessboard[8][8])
{
    row++; // Black pawns move downward

    // Check for the initial move (two squares forward allowed)
    if (b_pawn_initial_move[pawn_index] == 0)
    {
        // Check one square forward
        if (chessboard[row][column] == "[ ]")
        {
            chessboard[row][column] = "[*]";
        }
        // Check two squares forward, but only if the first square is empty
        if (row + 1 < 8 && chessboard[row + 1][column] == "[ ]" && chessboard[row][column] == "[*]")
        {
            chessboard[row + 1][column] = "[*]";
        }
    }
    else
    {
        // Subsequent moves (one square forward only)
        if (chessboard[row][column] == "[ ]")
        {
            chessboard[row][column] = "[*]";
        }
    }
}

void w_move_pawn(int pawn_index, int row, int column, int w_pawn_positions_current[], int old_row, int old_column, string chessboard[8][8])
{
    cout << "Moving white"<< endl;
    cout << "old row: " << old_row;
    cout << " old column:" << old_column;
    cout << endl;

    if (chessboard[row][column] == "[*]")
    {
        chessboard[row][column] = w_pawn;
        // Updating positions and keeping track
        w_pawn_positions_current[pawn_index * 2] = row;
        w_pawn_positions_current[pawn_index * 2 + 1] = column;

        // Resetting the original position
        chessboard[old_row][old_column] = "[-]";

        if (chessboard[old_row - 1][old_column] == "[*]")
        {
            chessboard[old_row - 1][old_column] = "[ ]";
        }
        // Additional clearing move for the pawn if it is its original move  - it will help in future as well when pawn has initial move
        if (chessboard[old_row - 2][old_column] == "[*]")
        {
            chessboard[old_row - 2][old_column] = "[ ]";
        }
    }
    else
    {
        cout << "Invalid move position, Selected Piece cannot move there";
        cout << endl;
    }
}
void b_move_pawn(int pawn_index, int row, int column, int b_pawn_positions_current[], int old_row, int old_column, string chessboard[8][8])
{
    cout << "moving black" << endl;
    if (chessboard[row][column] == "[*]")
    {
        chessboard[row][column] = b_pawn;
        // Updating positions and keeping track
        b_pawn_positions_current[pawn_index * 2] = row;
        b_pawn_positions_current[pawn_index * 2 + 1] = column;

        // Resetting the original position
        chessboard[old_row][old_column] = "[-]";

        if (chessboard[old_row + 1][old_column] == "[*]")
        {
            chessboard[old_row + 1][old_column] = "[ ]";
        }
        // Additional clearing move for the pawn if it is its original move  - it will help in future as well when pawn has initial move
        if (chessboard[old_row + 2][old_column] == "[*]")
        {
            chessboard[old_row + 2][old_column] = "[ ]";
        }
    }
    else
    {
        cout << "Invalid move position!";
    }
}

int main()
{
    // int b_pawn_initial_move[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    // int w_pawn_initial_move[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    int w_pawn_initial_move[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int b_pawn_initial_move[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    // Chessboard with empty spaces
    string chessboard[8][8] = {
        {"[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]"},
        {"[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]"},
        {"[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]"},
        {"[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]"},
        {"[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]"},
        {"[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]"},
        {"[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]"},
        {"[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]"}};

    // White Positions
    int w_king_position[2] = {7, 4};                                             // E1
    int w_queen_position[2] = {7, 3};                                            // D1
    int w_bishop_position[4] = {7, 2, 7, 5};                                     // C1, F1
    int w_rook_position[4] = {7, 0, 7, 7};                                       // A1, H1
    int w_knight_position[4] = {7, 1, 7, 6};                                     // B1, G1
    int w_pawn_positions[16] = {6, 0, 6, 1, 6, 2, 6, 3, 6, 4, 6, 5, 6, 6, 6, 7}; // A2-H2

    // Black Positions
    int b_king_position[2] = {0, 4};                                             // E8
    int b_queen_position[2] = {0, 3};                                            // D8
    int b_bishop_position[4] = {0, 2, 0, 5};                                     // C8, F8
    int b_rook_position[4] = {0, 0, 0, 7};                                       // A8, H8
    int b_knight_position[4] = {0, 1, 0, 6};                                     // B8, G8
    int b_pawn_positions[16] = {1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7}; // A7-H7

    // Place White Pieces
    chessboard[w_king_position[0]][w_king_position[1]] = w_king;
    chessboard[w_queen_position[0]][w_queen_position[1]] = w_queen;
    for (int i = 0; i < 2; i++)
    {
        chessboard[w_bishop_position[i * 2]][w_bishop_position[i * 2 + 1]] = w_bishop;
        chessboard[w_rook_position[i * 2]][w_rook_position[i * 2 + 1]] = w_rook;
        chessboard[w_knight_position[i * 2]][w_knight_position[i * 2 + 1]] = w_knight;
    }
    for (int i = 0; i < 8; i++)
    {
        chessboard[w_pawn_positions[i * 2]][w_pawn_positions[i * 2 + 1]] = w_pawn;
    }

    // Place Black Pieces
    chessboard[b_king_position[0]][b_king_position[1]] = b_king;
    chessboard[b_queen_position[0]][b_queen_position[1]] = b_queen;
    for (int i = 0; i < 2; i++)
    {
        chessboard[b_bishop_position[i * 2]][b_bishop_position[i * 2 + 1]] = b_bishop;
        chessboard[b_rook_position[i * 2]][b_rook_position[i * 2 + 1]] = b_rook;
        chessboard[b_knight_position[i * 2]][b_knight_position[i * 2 + 1]] = b_knight;
    }
    for (int i = 0; i < 8; i++)
    {
        chessboard[b_pawn_positions[i * 2]][b_pawn_positions[i * 2 + 1]] = b_pawn;
    }

    // Moving the pawn
    string select = "h7";
    // Convert the address to index of chessboard that can be use to iterate the array
    int row = '8' - select[1];
    int column = toupper(select[0]) - 'A';
    int pawn_index; // Subtracting 8 to get 0 for first pawn
    string move = "h5";
    // Convert the address to index of chessboard that can be use to iterate the array
    int Row = '8' - move[1];
    int Column = toupper(move[0]) - 'A';
    for (int i = 0; i < 16; i++)
    {
        if (w_pawn_positions[i * 2] == row && w_pawn_positions[i * 2 + 1] == column)
        {
            cout << "WHIte pawn moving";
            pawn_index = i;
            show_w_pawn_path(w_pawn_initial_move, pawn_index, row, column, chessboard);
            w_move_pawn(pawn_index, Row, Column, w_pawn_positions_current, row, column, chessboard);
            break;
        }
        if (b_pawn_positions[i * 2] == row && b_pawn_positions[i * 2 + 1] == column)
        {
            pawn_index = i;
            cout << "black pawn moving";
            show_b_pawn_path(b_pawn_initial_move, pawn_index, row, column, chessboard);
            b_move_pawn(pawn_index, Row, Column, b_pawn_positions_current, row, column, chessboard);
            break;
        }
    }

    // Printing the chessboard with position labels
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int row = 8 - i;       // Convert index to chess row (1-8)
            char column = 'A' + j; // Convert index to chess column (A-H)

            cout << column << row << ": " << chessboard[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
