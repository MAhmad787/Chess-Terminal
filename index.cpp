#include <iostream>
#include <string>
using namespace std;

// Fixed size for the chessboard
const int ROWS = 8;
const int COLUMNS = 8;
const int PIECES = 6;

// Declare the Chessboard
string chessboard[ROWS][COLUMNS];

// FLags for moves of both players
bool isPlaying = true;
bool white = true; // White player starts the game
bool black = false;
bool white_select = true;
bool black_select = false;
bool white_move = true;
bool black_move = false;
bool is_valid_selection = false;

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

// Pointer arrays
// For White Pieces
string *white_pieces[PIECES] = {&w_king, &w_queen, &w_rook, &w_knight, &w_bishop, &w_pawn};

// For Black Pieces
string *black_pieces[PIECES] = {&b_king, &b_queen, &b_rook, &b_knight, &b_bishop, &b_pawn};

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
    cout << "Showing path for white pawn" << endl;
    row--; // White pawns move upward

    // Check for the initial move (two squares forward allowed)
    if (w_pawn_initial_move[pawn_index] == 0)
    {
        // Check one square forward
        if (chessboard[row][column] == "[ ]")
        {
            chessboard[row][column] = "[*]";
            // Piece has moved, so the initial move is no longer valid
            w_pawn_initial_move[pawn_index] = 1;
            white_select = false;
        }
        else
        {
            cout << "Invalid move position, Selected Piece cannot even move" << endl;
            white_select = true;
        }

        // Check two squares forward, but only if the first square is empty
        if (row - 1 >= 0 && chessboard[row - 1][column] == "[ ]" && chessboard[row][column] == "[*]")
        {
            chessboard[row - 1][column] = "[*]";
        }
        else
        {
            cout << "Invalid move position, Selected Piece cannot even move" << endl;
            white_select = true;
        }
    }
    else
    {
        // Subsequent moves (one square forward only)
        if (chessboard[row][column] == "[ ]")
        {
            chessboard[row][column] = "[*]";
            white_select = false;
        }
        else
        {
            cout << "Invalid move position, Selected Piece cannot even move" << endl;
            white_select = true;
        }
    }
}

void show_b_pawn_path(int b_pawn_initial_move[], int pawn_index, int row, int column, string chessboard[ROWS][COLUMNS])
{
    cout << "Showing path for black pawn" << endl;
    row++; // Black pawns move downward

    // Check for the initial move (two squares forward allowed)
    if (b_pawn_initial_move[pawn_index] == 0)
    {
        // Check one square forward
        if (chessboard[row][column] == "[ ]")
        {
            chessboard[row][column] = "[*]";
            b_pawn_initial_move[pawn_index] = 1;
            black_select = false;
        }
        else
        {
            cout << "Invalid move position, Selected Piece cannot even move" << endl;
            black_select = true;
        }

        // Check two squares forward, but only if the first square is empty
        if (row + 1 < 8 && chessboard[row + 1][column] == "[ ]" && chessboard[row][column] == "[*]")
        {
            chessboard[row + 1][column] = "[*]";
        }
        else
        {
            cout << "Invalid move position, Selected Piece cannot even move" << endl;
            black_select = true;
        }
    }
    else
    {
        // Subsequent moves (one square forward only)
        if (chessboard[row][column] == "[ ]")
        {
            chessboard[row][column] = "[*]";
            black_select = false;
        }
        else
        {
            cout << "Invalid move position, Selected Piece cannot even move" << endl;
            black_select = true;
        }
    }
}

void w_move_pawn(int pawn_index, int row, int column, int w_pawn_positions_current[], int old_row, int old_column, string chessboard[ROWS][COLUMNS])
{
    cout << "Moving white" << endl;
    if (chessboard[row][column] == "[*]")
    {
        chessboard[row][column] = w_pawn;
        w_pawn_positions_current[pawn_index * 2] = row;
        w_pawn_positions_current[pawn_index * 2 + 1] = column;

        // Reset the previous positions
        chessboard[old_row][old_column] = "[ ]";
        if (chessboard[old_row - 1][old_column] == "[*]")
        {
            chessboard[old_row - 1][old_column] = "[ ]";
        }
        if (chessboard[old_row - 2][old_column] == "[*]")
        {
            chessboard[old_row - 2][old_column] = "[ ]";
        }
        white_move = false;
    }
    else
    {
        cout << "Invalid move position, Selected Piece cannot move there" << endl;
        white_move = true;
    }
}

void b_move_pawn(int pawn_index, int row, int column, int b_pawn_positions_current[], int old_row, int old_column, string chessboard[ROWS][COLUMNS])
{
    if (chessboard[row][column] == "[*]")
    {
        chessboard[row][column] = b_pawn;
        b_pawn_positions_current[pawn_index * 2] = row;
        b_pawn_positions_current[pawn_index * 2 + 1] = column;

        // Reset the previous positions
        chessboard[old_row][old_column] = "[ ]";
        if (chessboard[old_row + 1][old_column] == "[*]")
        {
            chessboard[old_row + 1][old_column] = "[ ]";
        }
        if (chessboard[old_row + 2][old_column] == "[*]")
        {
            chessboard[old_row + 2][old_column] = "[ ]";
        }
        black_move = false;
    }
    else
    {
        cout << "Invalid move position, Selected Piece cannot move there" << endl;
        black_move = true;
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
    // else if (chessboard[row][column] == "[ ]")
    // {
    //     cout << "No piece selected" << endl;
    //     return false;
    // }
    return true;
}

// Capture pieces
void capture_piece_pawn(string chessboard[ROWS][COLUMNS], char color, int row, int column)
{
    string king;
    char operation;
    switch (color)
    {
    case 'w':
        king = w_king;
        operation = '-';
        break;
    case 'b':
        king = b_king;
        operation = '+';
        break;

    default:
        break;
    }

    // Left diagonal
    if(operation == '-'){ row--; }
    else if(operation == '+'){ row++; }
    for (int i = 0; i < PIECES; i++)
    {
        if (chessboard[row][column - 1] == *black_pieces[i] && chessboard[row - 1][column - 1] != king && chessboard[row][column - 1] != "[ ]") 
        {
            cout << color << "Can capture in the left diagonal" << endl;
            break;
        }
    }
        // Right diagonal
    for (int i = 0; i < PIECES; i++)
    {
        if (chessboard[row][column + 1] == *black_pieces[i] && chessboard[row - 1][column + 1] != king)
        {
            cout << color << "Can capture in the right diagonal" << endl;
            break;
        }
    }
}
// Capture pieces
void checkmate_pawn(string chessboard[ROWS][COLUMNS], int row, int column)
{
    if (chessboard[row][column] == w_king)
    {
        cout << "Black wins" << endl;
        isPlaying = false;
    }
    else if (chessboard[row][column] == b_king)
    {
        cout << "White wins" << endl;
        isPlaying = false;
    }
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
            is_valid_selection = false;
            // Selecting the pawn
            do
            {
                string select;
                do
                {
                    cout << "Enter the position of the piece you want to move: ";
                    cin >> select;

                    // Convert the address to the index of the chessboard that can be used to iterate the array
                    row = '8' - select[1];
                    column = toupper(select[0]) - 'A';

                } while (!validate_position(select, row, column));

                cout << "Selected Piece: " << select << endl;

                for (int i = 0; i < 16; i++)
                {
                    if (w_pawn_positions_current[i * 2] == row && w_pawn_positions_current[i * 2 + 1] == column)
                    {
                        pawn_index = i;
                        // Showing the path for the selected white pawn
                        is_valid_selection = true;
                        show_w_pawn_path(w_pawn_initial_move, pawn_index, row, column, chessboard);
                        capture_piece_pawn(chessboard, 'w', row, column);
                        break;
                    }
                }
                if (!is_valid_selection)
                {
                    cout << "Please select white pawn" << endl;
                    white_select = true;
                }

            } while (white_select);
            // Display the updated chessboard
            display_chessboard(ROWS, COLUMNS, chessboard);

            // Moving the white pawn
            do
            {
                string move;
                do
                {
                    cout << "Enter the position you want to move to: ";
                    cin >> move;

                    // Convert the address to the index of the chessboard
                    Row = '8' - move[1];
                    Column = toupper(move[0]) - 'A';

                } while (!validate_position(move, Row, Column));

                // Move the selected white pawn
                w_move_pawn(pawn_index, Row, Column, w_pawn_positions_current, row, column, chessboard);

            } while (white_move);

            // Display the updated chessboard
            display_chessboard(ROWS, COLUMNS, chessboard);

            // Switch to black's turn
            white = false;
            black = true;
        }
        else if (black)
        {
            cout << "Black's Turn" << endl;
            is_valid_selection = false;
            // Selecting the pawn
            do
            {

                string select;
                do
                {
                    cout << "Enter the position of the piece you want to move: ";
                    cin >> select;

                    // Convert the address to the index of the chessboard
                    row = '8' - select[1];
                    column = toupper(select[0]) - 'A';

                } while (!validate_position(select, row, column));

                cout << "Selected Piece: " << select << endl;

                for (int i = 0; i < 16; i++)
                {
                    if (b_pawn_positions_current[i * 2] == row && b_pawn_positions_current[i * 2 + 1] == column)
                    {
                        pawn_index = i;
                        is_valid_selection = true;
                        // Showing the path for the selected black pawn
                        show_b_pawn_path(b_pawn_initial_move, pawn_index, row, column, chessboard);
                        capture_piece_pawn(chessboard, 'b', row, column);
                        break;
                    }
                }
                if (!is_valid_selection)
                {
                    cout << "Please select black pawn" << endl;
                    black_select = true;
                }

            } while (black_select);

            // Display the updated chessboard
            display_chessboard(ROWS, COLUMNS, chessboard);

            // Moving the black pawn
            do
            {
                string move;
                do
                {
                    cout << "Enter the position you want to move to: ";
                    cin >> move;

                    // Convert the address to the index of the chessboard
                    Row = '8' - move[1];
                    Column = toupper(move[0]) - 'A';

                } while (!validate_position(move, Row, Column));

                // Move the selected black pawn
                b_move_pawn(pawn_index, Row, Column, b_pawn_positions_current, row, column, chessboard);

            } while (black_move);

            // Display the updated chessboard
            display_chessboard(ROWS, COLUMNS, chessboard);

            // Switch to white's turn
            black = false;
            white = true;
        }
        else
        {
            cout << "Game is not being played" << endl;
            return 1;
        }
    }

    // if (!isPlaying)
    // {
    //     cout << "Game Over" << endl;
    // }
}