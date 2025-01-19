#include <iostream>
#include <string>
using namespace std;

// Fixed size for the chessboard
const int ROWS = 8;
const int COLUMNS = 8;

// Declare the Chessboard
string chessboard[ROWS][COLUMNS];

// FLags for moves of both players
bool isPlaying = true;
bool white = true; // White player starts the game
bool black = false;

// Variables to store the position of the selected piece
int row;
int column;

// Variables to store the new position of the selected piece
int Row;
int Column;

// Variables to store the index of the selected pieces
int pawn_index;
int rook_index;
int knight_index;
int bishop_index;

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

// int b_pawn_initial_move[8] = {1, 1, 1, 1, 1, 1, 1, 1};
// int w_pawn_initial_move[8] = {1, 1, 1, 1, 1, 1, 1, 1};
int w_pawn_initial_move[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int b_pawn_initial_move[8] = {0, 0, 0, 0, 0, 0, 0, 0};

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

void show_w_pawn_path(int w_pawn_initial_move[], int pawn_index, int row, int column, string chessboard[ROWS][COLUMNS])
{
    // cout << "Showing path for white pawn" << endl;
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

void show_b_pawn_path(int b_pawn_initial_move[], int pawn_index, int row, int column, string chessboard[ROWS][COLUMNS])
{
    // cout << "Black pawn path" << endl;
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

void w_move_pawn(int pawn_index, int row, int column, int w_pawn_positions_current[], int old_row, int old_column, string chessboard[ROWS][COLUMNS])
{

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
void b_move_pawn(int pawn_index, int row, int column, int b_pawn_positions_current[], int old_row, int old_column, string chessboard[ROWS][COLUMNS])
{
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

void generate_chessboard(int rows, int columns, string chessboard[ROWS][COLUMNS])
{
    // Chessboard with empty spaces
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            chessboard[i][j] = "[ ]";
        }
    }
}
void display_chessboard(int row, int column, string chessboard[ROWS][COLUMNS])
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            int row = ROWS - i;    // Convert index to chess row (1-8)
            char column = 'A' + j; // Convert index to chess column (A-H)

            cout << column << row << ": " << chessboard[i][j] << " ";
        }
        cout << endl;
    }
}

void place_pieces(string chessboard[ROWS][COLUMNS], char color, int king_position[], int queen_position[], int bishop_position[], int rook_position[], int knight_position[], int pawn_positions[])
{
    string king;
    string queen;
    string bishop;
    string rook;
    string knight;
    string pawn;

    switch (color)
    {
    case 'w':
        king = w_king;
        queen = w_queen;
        bishop = w_bishop;
        rook = w_rook;
        knight = w_knight;
        pawn = w_pawn;
        break;
    case 'b':
        king = b_king;
        queen = b_queen;
        bishop = b_bishop;
        rook = b_rook;
        knight = b_knight;
        pawn = b_pawn;
        break;

    default:
        break;
    }
    // Place White Pieces
    chessboard[king_position[0]][king_position[1]] = king;
    chessboard[queen_position[0]][queen_position[1]] = queen;
    for (int i = 0; i < 2; i++)
    {
        chessboard[bishop_position[i * 2]][bishop_position[i * 2 + 1]] = bishop;
        chessboard[rook_position[i * 2]][rook_position[i * 2 + 1]] = w_rook;
        chessboard[knight_position[i * 2]][knight_position[i * 2 + 1]] = knight;
    }
    for (int i = 0; i < 8; i++)
    {
        chessboard[pawn_positions[i * 2]][pawn_positions[i * 2 + 1]] = pawn;
    }
}

bool validate_position(string position, int row, int column)
{
    position[0] = toupper(position[0]);
    if (position.length() != 2)
    {
        cout << "Invalid Position" << endl;
        return false;
    }

    else if (position[0] < 'A' || position[0] > 'H' || position[1] < '1' || position[1] > '8')
    {
        cout << "Invalid Position" << endl;
        return false;
    }
    else if (chessboard[row][column] == "[ ]")
    {
        cout << "No piece selected" << endl;
        return false;
    }
    return true;
}

int main()
{

    // Generate the Empty Chessboard
    generate_chessboard(ROWS, COLUMNS, chessboard);

    // Place White Pieces
    place_pieces(chessboard, 'w', w_king_position, w_queen_position, w_bishop_position, w_rook_position, w_knight_position, w_pawn_positions);
    // Place Black pieces
    place_pieces(chessboard, 'b', b_king_position, b_queen_position, b_bishop_position, b_rook_position, b_knight_position, b_pawn_positions);

    // Run the game until it is being played
    while (isPlaying)
    {

        // Determining which player's turn it is
        if (white)
        {

            cout << "White's Turn" << endl;
            // Moving the pawn
            string select;
            do
            {
                cout << "Enter the position of the piece you want to move: ";
                cin >> select;
                // Convert the address to index of chessboard that can be use to iterate the array
                row = '8' - select[1];
                column = toupper(select[0]) - 'A';

            } while (!validate_position(select, row, column));

            // display_chessboard(ROWS, COLUMNS, chessboard);
            cout << "Selected Piece: " << select << endl;
            display_chessboard(ROWS, COLUMNS, chessboard);

            do
            {
                string move;
                cout << "Enter the position you want to move to: ";
                cin >> move;
                // Convert the address to index of chessboard that can be use to iterate the array
                Row = '8' - move[1];
                Column = toupper(move[0]) - 'A';

            } while (!validate_position);

            for (int i = 0; i < 16; i++)
            {
                if (w_pawn_positions[i * 2] == row && w_pawn_positions[i * 2 + 1] == column)
                {
                    pawn_index = i;
                    show_w_pawn_path(w_pawn_initial_move, pawn_index, row, column, chessboard);
                    w_move_pawn(pawn_index, Row, Column, w_pawn_positions_current, row, column, chessboard);
                    break;
                }
                if (b_pawn_positions[i * 2] == row && b_pawn_positions[i * 2 + 1] == column)
                {
                    pawn_index = i;
                    show_b_pawn_path(b_pawn_initial_move, pawn_index, row, column, chessboard);
                    b_move_pawn(pawn_index, Row, Column, b_pawn_positions_current, row, column, chessboard);
                    break;
                }
            }
            // Printing the chessboard with position labels
            display_chessboard(ROWS, COLUMNS, chessboard);

            // Setting the flag for the next player
            white = false;
            black = true;
        }
        else if (black)
        {
            cout << "Black's Turn" << endl;

            // Moving the pawn
            string select;
            do
            {
                cout << "Enter the position of the piece you want to move: ";
                cin >> select;
                // Convert the address to index of chessboard that can be use to iterate the array
                row = '8' - select[1];
                column = toupper(select[0]) - 'A';

            } while (!validate_position(select, row, column));

            display_chessboard(ROWS, COLUMNS, chessboard);
            cout << "Selected Piece: " << select << endl;

            do
            {
                string move;
                cout << "Enter the position you want to move to: ";
                cin >> move;
                // Convert the address to index of chessboard that can be use to iterate the array
                Row = '8' - move[1];
                Column = toupper(move[0]) - 'A';

            } while (!validate_position);
            // Printing the chessboard with position labels
            display_chessboard(ROWS, COLUMNS, chessboard);
            for (int i = 0; i < 16; i++)
            {
                if (w_pawn_positions[i * 2] == row && w_pawn_positions[i * 2 + 1] == column)
                {
                    pawn_index = i;
                    show_w_pawn_path(w_pawn_initial_move, pawn_index, row, column, chessboard);
                    w_move_pawn(pawn_index, Row, Column, w_pawn_positions_current, row, column, chessboard);
                    break;
                }
                if (b_pawn_positions[i * 2] == row && b_pawn_positions[i * 2 + 1] == column)
                {
                    pawn_index = i;
                    show_b_pawn_path(b_pawn_initial_move, pawn_index, row, column, chessboard);
                    b_move_pawn(pawn_index, Row, Column, b_pawn_positions_current, row, column, chessboard);
                    break;
                }
            }
            display_chessboard(ROWS, COLUMNS, chessboard);

            // Seting the flag for the next player
            black = false;
            white = true;
        }

        else
        {
            cout << "Game is not being played" << endl;
            return 1;
        }
    }
    if (!isPlaying)
    {
        cout << "Game Over" << endl;
    }
}