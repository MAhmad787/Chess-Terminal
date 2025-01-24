#include <iostream>
using namespace std;
// Fixed size for the chessboard
const int ROWS = 8;
const int COLUMNS = 8;

// Declare the Chessboard
string chessboard[ROWS][COLUMNS];

// Positons of the chessboard pieces on the board
// White Pieces
int w_king_position[1][2] = {{7, 4}};           // E1
int w_queen_position[1][2] = {{7, 3}};          // D1
int w_bishop_position[2][2] = {{7, 2}, {7, 5}}; // C1, F1
int w_rook_position[2][2] = {{7, 0}, {7, 7}};   // A1, H1
int w_knight_position[2][2] = {{7, 1}, {7, 6}}; // B1, G1
int w_pawn_positions[8][2] = {                  // A2-H2
    {6, 0},
    {6, 1},
    {6, 2},
    {6, 3},
    {6, 4},
    {6, 5},
    {6, 6},
    {6, 7}};

// Black Pieces
int b_king_position[1][2] = {{0, 4}};           // E8
int b_queen_position[1][2] = {{0, 3}};          // D8
int b_bishop_position[2][2] = {{0, 2}, {0, 5}}; // C8, F8
int b_rook_position[2][2] = {{0, 0}, {0, 7}};   // A8, H8
int b_knight_position[2][2] = {{0, 1}, {0, 6}}; // B8, G8
int b_pawn_positions[8][2] = {                  // A7-H7
    {1, 0},
    {1, 1},
    {1, 2},
    {1, 3},
    {1, 4},
    {1, 5},
    {1, 6},
    {1, 7}};

struct chessPiece
{
    /* data */
    string name;
    char color;
    int row;
    int column;
    bool isAlive;
    int movesCounter = 0;
    bool isKing = false;
    void showPath();
    void move();
    void capture();
};
// Declaring the chess pieces
// White Pieces
chessPiece w_king;
chessPiece w_queen;
chessPiece w_bishop[2];
chessPiece w_rook[2];
chessPiece w_knight[2];
chessPiece w_pawn[8];

// Black Pieces
chessPiece b_king;
chessPiece b_queen;
chessPiece b_bishop[2];
chessPiece b_rook[2];
chessPiece b_knight[2];
chessPiece b_pawn[8];

// Initialize the chess pieces
void initializePieces(chessPiece &w_king, chessPiece &w_queen, chessPiece w_bishop[], chessPiece w_rook[], chessPiece w_knight[], chessPiece w_pawn[], chessPiece &b_king, chessPiece &b_queen, chessPiece b_bishop[], chessPiece b_rook[], chessPiece b_knight[], chessPiece b_pawn[])
{
    // White Pieces
    w_king = {"king", 'w', w_king_position[0][0], w_king_position[0][1], true, 0, true};
    w_queen = {"queen", 'w', w_queen_position[0][0], w_queen_position[0][1], true, 0};

    for (int i = 0; i < 2; i++)
    {
        w_bishop[i] = {"bishop", 'w', w_bishop_position[i][0], w_bishop_position[i][1], true, 0};
        w_rook[i] = {"rook", 'w', w_rook_position[i][0], w_rook_position[i][1], true, 0};
        w_knight[i] = {"knight", 'w', w_knight_position[i][0], w_knight_position[i][1], true, 0};
    };

    // Black Pieces
    b_king = {"king", 'b', b_king_position[0][0], b_king_position[0][1], true, 0, true};
    b_queen = {"queen", 'b', b_queen_position[0][0], b_queen_position[0][1], true, 0};
    for(int i = 0; i < 2; i++){
        b_bishop[i] = {"bishop", 'b', b_bishop_position[i][0], b_bishop_position[i][1], true, 0};
        b_rook[i] = {"rook", 'b', b_rook_position[i][0], b_rook_position[i][1], true, 0};
        b_knight[i] = {"knight", 'b', b_knight_position[i][0], b_knight_position[i][1], true, 0};
    }
}

// Function Prototypes

// Place the pieces on the chessboard
void place_pieces(string chessboard[ROWS][COLUMNS], chessPiece &w_king, chessPiece &w_queen, chessPiece w_bishop[], chessPiece w_rook[], chessPiece w_knight[], chessPiece w_pawn[], chessPiece &b_king, chessPiece &b_queen, chessPiece b_bishop[], chessPiece b_rook[], chessPiece b_knight[], chessPiece b_pawn[]){
    // Place White Pieces
    chessboard[w_king.row][w_king.column] = w_king.color + w_king.name;
    chessboard[w_queen.row][w_queen.column] = w_queen.color + w_queen.name;
    for(int i = 0; i < 2; i++){
        chessboard[w_bishop[i].row][w_bishop[i].column] = w_bishop[i].color + w_bishop[i].name;
        chessboard[w_rook[i].row][w_rook[i].column] = w_rook[i].color + w_rook[i].name;
        chessboard[w_knight[i].row][w_knight[i].column] = w_knight[i].color + w_knight[i].name;
    }
    for(int i = 0; i < 8; i++){
        chessboard[w_pawn[i].row][w_pawn[i].column] = w_pawn[i].color + w_pawn[i].name;
    }

    // Place Black Pieces
    chessboard[b_king.row][b_king.column] = b_king.name;
    chessboard[b_queen.row][b_queen.column] = b_queen.name;
    for(int i = 0; i < 2; i++){
        chessboard[b_bishop[i].row][b_bishop[i].column] = b_bishop[i].color + b_bishop[i].name;
        chessboard[b_rook[i].row][b_rook[i].column] = b_rook[i].color + b_rook[i].name;
        chessboard[b_knight[i].row][b_knight[i].column] = b_knight[i].color + b_knight[i].name;
    }
    for(int i = 0; i < 8; i++){
        chessboard[b_pawn[i].row][b_pawn[i].column] = b_pawn[i].color + b_pawn[i].name;
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

int main()
{
    // Generate the Empty Chessboard
    generate_chessboard(ROWS, COLUMNS, chessboard);

    // Initialize the chess pieces
    initializePieces(w_king, w_queen, w_bishop, w_rook, w_knight, w_pawn, b_king, b_queen, b_bishop, b_rook, b_knight, b_pawn);


    // Place the pieces on the chessboard
    place_pieces(chessboard, w_king, w_queen, w_bishop, w_rook, w_knight, w_pawn, b_king, b_queen, b_bishop, b_rook, b_knight, b_pawn);

    // Display the Chessboard
    display_chessboard(ROWS, COLUMNS, chessboard);


    cout << "White King: " << w_king.row << " " << w_king.column << endl;
    return 0;
}