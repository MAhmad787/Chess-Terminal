#include <iostream>
using namespace std;

// Fixed size for the chessboard
const int ROWS = 8;
const int COLUMNS = 8;

// Flags
bool isPlaying = true;
bool isWhitePlaying = true;
bool isBlackPlaying = false;
bool isValidSelection;
bool isWhiteSelected;
bool isBlackSelected;
bool isWhiteMoving;
bool isBlackMoving;

// Variables for indentifing
string pieceName;
char pieceColor;
int pieceIndex;

// Coodinates
int rowForSelection;
int columnForSelection;
int rowForMovement;
int columnForMovement;

// Declare the Chessboard
string chessboard[ROWS][COLUMNS];

// Positons of the chessboard pieces on the board
// White Pieces
int w_king_position[1][2] = {{7, 4}};           // E1
int w_queen_position[1][2] = {{7, 3}};          // D1
int w_bishop_position[2][2] = {{7, 2}, {7, 5}}; // C1, F1
int w_rook_position[2][2] = {{7, 0}, {7, 7}};   // A1, H1
int w_knight_position[2][2] = {{7, 1}, {7, 6}}; // B1, G1
int w_pawn_position[8][2] = {                   // A2-H2
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
int b_pawn_position[8][2] = {                   // A7-H7
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
    bool isAlive = true;
    int index;
    int movesCounter = 0;
    bool isKing = false;
    void showPath();
    void move();
    void canCapture();
};

void chessPiece::showPath()
{
    cout << "hello " << name;
}

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
    w_king = {"king", 'w', w_king_position[0][0], w_king_position[0][1], true, 1, 0, true};
    w_queen = {"queen", 'w', w_queen_position[0][0], w_queen_position[0][1], true, 1, 0};

    for (int i = 0; i < 2; i++)
    {
        w_bishop[i] = {"bishop", 'w', w_bishop_position[i][0], w_bishop_position[i][1], true, i + 1, 0};
        w_rook[i] = {"rook", 'w', w_rook_position[i][0], w_rook_position[i][1], true, i + 1, 0};
        w_knight[i] = {"knight", 'w', w_knight_position[i][0], w_knight_position[i][1], true, i + 1, 0};
    };

    for (int i = 0; i < 8; i++)
    {
        w_pawn[i] = {"pawn", 'w', w_pawn_position[i][0], w_pawn_position[i][1], true, i + 1, 0};
    }

    // Black Pieces
    b_king = {"king", 'b', b_king_position[0][0], b_king_position[0][1], true, 1, 0, true};
    b_queen = {"queen", 'b', b_queen_position[0][0], b_queen_position[0][1], true, 1, 0};
    for (int i = 0; i < 2; i++)
    {
        b_bishop[i] = {"bishop", 'b', b_bishop_position[i][0], b_bishop_position[i][1], true, i + 1, 0};
        b_rook[i] = {"rook", 'b', b_rook_position[i][0], b_rook_position[i][1], true, i + 1, 0};
        b_knight[i] = {"knight", 'b', b_knight_position[i][0], b_knight_position[i][1], true, i + 1, 0};
    }
    for (int i = 0; i < 8; i++)
    {
        b_pawn[i] = {"pawn", 'b', b_pawn_position[i][0], b_pawn_position[i][1], true, i + 1, 0};
    }
}

// Function Prototypes

// Place the pieces on the chessboard
void place_pieces(string chessboard[ROWS][COLUMNS], chessPiece &w_king, chessPiece &w_queen, chessPiece w_bishop[], chessPiece w_rook[], chessPiece w_knight[], chessPiece w_pawn[], chessPiece &b_king, chessPiece &b_queen, chessPiece b_bishop[], chessPiece b_rook[], chessPiece b_knight[], chessPiece b_pawn[])
{
    // Place White Pieces
    chessboard[w_king.row][w_king.column] = w_king.color + w_king.name;
    chessboard[w_queen.row][w_queen.column] = w_queen.color + w_queen.name;
    for (int i = 0; i < 2; i++)
    {
        chessboard[w_bishop[i].row][w_bishop[i].column] = w_bishop[i].color + w_bishop[i].name;
        chessboard[w_rook[i].row][w_rook[i].column] = w_rook[i].color + w_rook[i].name;
        chessboard[w_knight[i].row][w_knight[i].column] = w_knight[i].color + w_knight[i].name;
    }
    for (int i = 0; i < 8; i++)
    {
        chessboard[w_pawn[i].row][w_pawn[i].column] = w_pawn[i].color + w_pawn[i].name;
    }

    // Place Black Pieces
    chessboard[b_king.row][b_king.column] = b_king.name;
    chessboard[b_queen.row][b_queen.column] = b_queen.name;
    for (int i = 0; i < 2; i++)
    {
        chessboard[b_bishop[i].row][b_bishop[i].column] = b_bishop[i].color + b_bishop[i].name;
        chessboard[b_rook[i].row][b_rook[i].column] = b_rook[i].color + b_rook[i].name;
        chessboard[b_knight[i].row][b_knight[i].column] = b_knight[i].color + b_knight[i].name;
    }
    for (int i = 0; i < 8; i++)
    {
        chessboard[b_pawn[i].row][b_pawn[i].column] = b_pawn[i].color + b_pawn[i].name;
    }
}

void generate_chessboard(string chessboard[ROWS][COLUMNS])
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

// Validate Search
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
    return true;
}
void selectPiece(int row, int column, string &pieceName, char &pieceColor, int &pieceIndex)
{
    // Selecting White Pieces

    if (chessboard[row][column] != "[ ]" && chessboard[row][column][0] == 'w' && isWhitePlaying)
    {

        // If king or Queen is being selected
        if (w_king.row == row && w_king.column == column)
        {
            pieceName = w_king.name;
            pieceColor = w_king.color;
            pieceIndex = w_king.index;
        }
        else if (w_queen.row == row && w_queen.column == column)
        {
            pieceName = w_queen.name;
            pieceColor = w_queen.color;
            pieceIndex = w_queen.index;
        }

        // If pawn is being selected
        for (int i = 0; i < 8; i++)
        {
            if (w_pawn[i].row == row && w_pawn[i].column == column)
            {
                if (w_pawn[i].isAlive)
                {
                    pieceName = w_pawn[i].name;
                    pieceColor = w_pawn[i].color;
                    pieceIndex = w_pawn[i].index;
                }
            }
        }
        // For rook, bishop or knight is being selected
        for (int i = 0; i < 2; i++)
        {
            if (w_rook[i].row == row && w_rook[i].column == column)
            {
                if (w_rook[i].isAlive)
                {
                    pieceName = w_rook[i].name;
                    pieceColor = w_rook[i].color;
                    pieceIndex = w_rook[i].index;
                }
            }
            if (w_bishop[i].row == row && w_bishop[i].column == column)
            {
                if (w_bishop[i].isAlive)
                {
                    pieceName = w_bishop[i].name;
                    pieceColor = w_bishop[i].color;
                    pieceIndex = w_bishop[i].index;
                }
            }
            if (w_knight[i].row == row && w_knight[i].column == column)
            {
                if (w_knight[i].isAlive)
                {
                    pieceName = w_knight[i].name;
                    pieceColor = w_knight[i].color;
                    pieceIndex = w_knight[i].index;
                }
            }
        }
    }

    // Selecting Black Pieces
    else if (chessboard[row][column] != "[ ]" && chessboard[row][column][0] == 'b' && isBlackPlaying)
    {
        // If king or Queen is being selected
        if (b_king.row == row && b_king.column == column)
        {
            pieceName = b_king.name;
            pieceColor = b_king.color;
            pieceIndex = b_king.index;
        }
        else if (b_queen.row == row && b_queen.column == column)
        {
            if (b_queen.isAlive)
            {
                pieceName = b_queen.name;
                pieceColor = b_queen.color;
                pieceIndex = b_queen.index;
            }
        }

        // If pawn is being selected
        for (int i = 0; i < 8; i++)
        {

            if (b_pawn[i].row == row && b_pawn[i].column == column)
            {
                if (b_pawn[i].isAlive)
                {
                    pieceName = b_pawn[i].name;
                    pieceColor = b_pawn[i].color;
                    pieceIndex = b_pawn[i].index;
                }
            }
        }
        // For rook, bishop or knight is being selected
        for (int i = 0; i < 2; i++)
        {
            if (b_rook[i].row == row && b_rook[i].column == column)
            {
                if (b_rook[i].isAlive)
                {
                    pieceName = b_rook[i].name;
                    pieceColor = b_rook[i].color;
                    pieceIndex = b_rook[i].index;
                }
            }
            if (b_bishop[i].row == row && b_bishop[i].column == column)
            {
                if (b_bishop[i].isAlive)
                {
                    pieceName = b_bishop[i].name;
                    pieceColor = b_bishop[i].color;
                    pieceIndex = b_bishop[i].index;
                }
            }
            if (b_knight[i].row == row && b_knight[i].column == column)
            {
                if (b_knight[i].isAlive)
                {
                    pieceName = b_knight[i].name;
                    pieceColor = b_knight[i].color;
                    pieceIndex = b_knight[i].index;
                }
            }
        }
    }
}
int main()
{
    // Generate the Empty Chessboard
    generate_chessboard(chessboard);

    // Initialize the chess pieces
    initializePieces(w_king, w_queen, w_bishop, w_rook, w_knight, w_pawn, b_king, b_queen, b_bishop, b_rook, b_knight, b_pawn);

    // Place the pieces on the chessboard
    place_pieces(chessboard, w_king, w_queen, w_bishop, w_rook, w_knight, w_pawn, b_king, b_queen, b_bishop, b_rook, b_knight, b_pawn);

    // Display the Chessboard
    // display_chessboard(ROWS, COLUMNS, chessboard);

    // Run the game until it is being played
    while (isPlaying)
    {
        // Determining which player's turn it is
        if (isWhitePlaying)
        {
            cout << "White's Turn" << endl;
            isWhiteSelected = true;
            // Selecting the pawn
            do
            {
                string select;
                do
                {
                    cout << "Enter the position of the piece you want to move: ";
                    cin >> select;

                    // Convert the address to the index of the chessboard that can be used to iterate the array
                    rowForSelection = '8' - select[1];
                    columnForSelection = toupper(select[0]) - 'A';

                } while (!validate_position(select, rowForSelection, columnForSelection));

                cout << "Selected Piece: " << select << endl;

                // Select the piece ..  Todo >>>>>>>
                selectPiece(rowForSelection, columnForSelection, pieceName, pieceColor, pieceIndex);
                if (pieceIndex != 0)
                {
                    cout << "Piece Name: " << pieceName << endl;
                    cout << "Piece Color: " << pieceColor << endl;
                    cout << "Piece Index: " << pieceIndex << endl;
                    // Ending the loop cuz element is selected
                    isWhiteSelected = false;
                }
                else
                {
                    cout << "Invalid Selection" << endl;
                }

            } while (isWhiteSelected);
            // Display the updated chessboard
            // display_chessboard(ROWS, COLUMNS, chessboard);

            // Moving the white pawn
            do
            {
                string move;
                do
                {
                    cout << "Enter the position you want to move to: ";
                    cin >> move;

                    // Convert the address to the index of the chessboard
                    rowForMovement = '8' - move[1];
                    columnForMovement = toupper(move[0]) - 'A';

                } while (!validate_position(move, rowForMovement, columnForMovement));

                // Move the selected white pawn .. Todo >>>>>>>>>>>>..

            } while (isWhiteMoving);

            // Display the updated chessboard
            // display_chessboard(ROWS, COLUMNS, chessboard);

            // Switch to black's turn
            isWhitePlaying = false;
            isBlackPlaying = true;
        }
        else if (isBlackPlaying)
        {
            cout << "Black's Turn" << endl;
            isBlackSelected = false;
            // Selecting the pawn
            do
            {

                string select;
                do
                {
                    cout << "Enter the position of the piece you want to move: ";
                    cin >> select;

                    // Convert the address to the index of the chessboard
                    rowForSelection = '8' - select[1];
                    columnForSelection = toupper(select[0]) - 'A';

                } while (!validate_position(select, rowForSelection, columnForSelection));

                // Select the piece ..  Todo >>>>>>>
                selectPiece(rowForSelection, columnForSelection, pieceName, pieceColor, pieceIndex);
                if (pieceIndex != 0)
                {
                    cout << "Piece Name: " << pieceName << endl;
                    cout << "Piece Color: " << pieceColor << endl;
                    cout << "Piece Index: " << pieceIndex << endl;
                    // Ending the loop cuz element is selected
                    isBlackSelected = false;
                }
                else
                {
                    cout << "Invalid Selection" << endl;
                }

            } while (isBlackSelected);

            // Display the updated chessboard
            // display_chessboard(ROWS, COLUMNS, chessboard);

            // Moving the black pawn
            do
            {
                string move;
                do
                {
                    cout << "Enter the position you want to move to: ";
                    cin >> move;

                    // Convert the address to the index of the chessboard
                    rowForMovement = '8' - move[1];
                    columnForMovement = toupper(move[0]) - 'A';

                } while (!validate_position(move, rowForMovement, columnForMovement));

                // Move the selected black pawn.. Todo >.>>>>>>

            } while (isBlackMoving);

            // Display the updated chessboard
            // display_chessboard(ROWS, COLUMNS, chessboard);

            // Switch to white's turn
            isBlackPlaying = false;
            isWhitePlaying = true;
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
    // cout << selectPiece(7, 4);
    // b_rook[0].showPath();
    // cout << w_king.index;
    return 0;
}
