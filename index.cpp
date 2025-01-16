#include <iostream>
#include <string>
using namespace std;

int main()
{
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
    int w_king_position[2] = {7, 4};   // E1
    int w_queen_position[2] = {7, 3};  // D1
    int w_bishop_position[4] = {7, 2, 7, 5}; // C1, F1
    int w_rook_position[4] = {7, 0, 7, 7};  // A1, H1
    int w_knight_position[4] = {7, 1, 7, 6}; // B1, G1
    int w_pawn_positions[16] = {6, 0, 6, 1, 6, 2, 6, 3, 6, 4, 6, 5, 6, 6, 6, 7};  // A2-H2

    // Black Positions
    int b_king_position[2] = {0, 4};   // E8
    int b_queen_position[2] = {0, 3};  // D8
    int b_bishop_position[4] = {0, 2, 0, 5}; // C8, F8
    int b_rook_position[4] = {0, 0, 0, 7};  // A8, H8
    int b_knight_position[4] = {0, 1, 0, 6}; // B8, G8
    int b_pawn_positions[16] = {1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7};  // A7-H7

    // Place White Pieces
    chessboard[w_king_position[0]][w_king_position[1]] = w_king;
    chessboard[w_queen_position[0]][w_queen_position[1]] = w_queen;
    for (int i = 0; i < 2; i++) {
        chessboard[w_bishop_position[i * 2]][w_bishop_position[i * 2 + 1]] = w_bishop;
        chessboard[w_rook_position[i * 2]][w_rook_position[i * 2 + 1]] = w_rook;
        chessboard[w_knight_position[i * 2]][w_knight_position[i * 2 + 1]] = w_knight;
    }
    for (int i = 0; i < 8; i++) {
        chessboard[w_pawn_positions[i * 2]][w_pawn_positions[i * 2 + 1]] = w_pawn;
    }

    // Place Black Pieces
    chessboard[b_king_position[0]][b_king_position[1]] = b_king;
    chessboard[b_queen_position[0]][b_queen_position[1]] = b_queen;
    for (int i = 0; i < 2; i++) {
        chessboard[b_bishop_position[i * 2]][b_bishop_position[i * 2 + 1]] = b_bishop;
        chessboard[b_rook_position[i * 2]][b_rook_position[i * 2 + 1]] = b_rook;
        chessboard[b_knight_position[i * 2]][b_knight_position[i * 2 + 1]] = b_knight;
    }
    for (int i = 0; i < 8; i++) {
        chessboard[b_pawn_positions[i * 2]][b_pawn_positions[i * 2 + 1]] = b_pawn;
    }

    // Printing the chessboard with position labels
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int row = 8 - i;       // Convert index to chess row (1-8)
            char column = 'A' + j; // Convert index to chess column (A-H)

            cout << column << row << ": " << chessboard[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
