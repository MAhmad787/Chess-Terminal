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
string pieceName = "";
char pieceColor = ' ';
int pieceIndex = 0;


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

// Pointer for identifing piece
chessPiece *selectedPiece = nullptr;


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

void chessPiece::showPath()
{
    // Show path for white pieces
    if (name == "king" && color == 'w')
    {
        cout << "Showing Path for King" << endl;
        // Todo >>>>>>>>>>>>>>>>
    }
    else if (name == "queen" && color == 'w')
    {
        cout << "Showing Path for Queen" << endl;
        // Todo >>>>>>>>>>>>>>>>
    }
    else if (name == "bishop" && color == 'w')
    {
        for (int i = 0; i < 2; i++)
        {
            if (w_bishop[i].index == pieceIndex)
            {
                cout << "Showing Path for Bishop" << i + 1 << endl;
                // Todo >>>>>>>>>>>>>

                break;
            }
        }
    }
    else if (name == "rook" && color == 'w')
    {
        for (int i = 0; i < 2; i++)
        {
            if (w_rook[i].index == pieceIndex)
            {
                cout << "Showing Path for Rook" << i + 1 << endl;
                // Todo >>>>>>>>>>>>>

                break;
            }
        }
    }
    else if (name == "knight" && color == 'w')
    {
        for (int i = 0; i < 2; i++)
        {
            if (w_knight[i].index == pieceIndex)
            {
                cout << "Showing Path for Knight" << i + 1 << endl;
                // Todo >>>>>>>>>>>>>

                break;
            }
        }
    }
    else if (name == "pawn" && color == 'w')
    {
        for (int i = 0; i < 8; i++)
        {
            if (w_pawn[i].index == pieceIndex)
            {
                cout << "Showing Path for Pawn" << i + 1 << endl;
                // Todo >>>>>>>>>>>>>

                break;
            }
        }
    }

    // Show path for black pieces
    if (name == "king" && color == 'b')
    {
        cout << "Showing Path for King" << endl;
        // Todo >>>>>>>>>>>>>>>>
    }
    else if (name == "queen" && color == 'b')
    {
        cout << "Showing Path for Queen" << endl;
        // Todo >>>>>>>>>>>>>>>>
    }
    else if (name == "bishop" && color == 'b')
    {
        for (int i = 0; i < 2; i++)
        {
            if (b_bishop[i].index == pieceIndex)
            {
                cout << "Showing Path for Bishop" << i + 1 << endl;
                // Todo >>>>>>>>>>>>>

                break;
            }
        }
    }
    else if (name == "rook" && color == 'b')
    {
        for (int i = 0; i < 2; i++)
        {
            if (b_rook[i].index == pieceIndex)
            {
                cout << "Showing Path for Rook" << i + 1 << endl;
                // Todo >>>>>>>>>>>>>

                break;
            }
        }
    }
    else if (name == "knight" && color == 'b')
    {
        for (int i = 0; i < 2; i++)
        {
            if (b_knight[i].index == pieceIndex)
            {
                cout << "Showing Path for Knight" << i + 1 << endl;
                // Todo >>>>>>>>>>>>>
                break;
            }
        }
    }
    else if (name == "pawn" && color == 'b')
    {
        for (int i = 0; i < 8; i++)
        {
            if (b_pawn[i].index == pieceIndex)
            {
                cout << "Showing Path for Pawn" << i + 1 << endl;
                // Todo >>>>>>>>>>>>>

                break;
            }
        }
    }
}
void chessPiece::move()
{
    // Show path for white pieces
    if (name == "king" && color == 'w')
    {
        cout << "Moving the King to " << rowForMovement << " and " << columnForMovement << endl;
        // Todo >>>>>>>>>>>>>>>>

        // Update the movesCounter
        movesCounter++;

        // Resetting the pieceName, pieceColor and pieceIndex
        pieceName = "";
        pieceColor = ' ';
        pieceIndex = 0;
    }
    else if (name == "queen" && color == 'w')
    {
        cout << "Moving the Queen" << endl;
        // Todo >>>>>>>>>>>>>>>>

        // Update the movesCounter
        movesCounter++;

        // Resetting the pieceName, pieceColor and pieceIndex
        pieceName = "";
        pieceColor = ' ';
        pieceIndex = 0;
    }
    else if (name == "bishop" && color == 'w')
    {
        for (int i = 0; i < 2; i++)
        {
            if (w_bishop[i].index == pieceIndex)
            {
                cout << "Moving the Bishop" << i + 1 << endl;
                // Todo >>>>>>>>>>>>>

                // Update the movesCounter
                movesCounter++;

                // Resetting the pieceName, pieceColor and pieceIndex
                pieceName = "";
                pieceColor = ' ';
                pieceIndex = 0;
                break;
            }
        }
    }
    else if (name == "rook" && color == 'w')
    {
        for (int i = 0; i < 2; i++)
        {
            if (w_rook[i].index == pieceIndex)
            {
                cout << "Moving the Rook" << i + 1 << endl;
                // Todo >>>>>>>>>>>>>

                // Update the movesCounter
                movesCounter++;

                // Resetting the pieceName, pieceColor and pieceIndex
                pieceName = "";
                pieceColor = ' ';
                pieceIndex = 0;
                break;
            }
        }
    }
    else if (name == "knight" && color == 'w')
    {
        for (int i = 0; i < 2; i++)
        {
            if (w_knight[i].index == pieceIndex)
            {
                cout << "Moving the Knight" << i + 1 << endl;
                // Todo >>>>>>>>>>>>>

                // Update the movesCounter
                movesCounter++;

                // Resetting the pieceName, pieceColor and pieceIndex
                pieceName = "";
                pieceColor = ' ';
                pieceIndex = 0;
                break;
            }
        }
    }
    else if (name == "pawn" && color == 'w')
    {
        for (int i = 0; i < 8; i++)
        {
            if (w_pawn[i].index == pieceIndex)
            {
                cout << "Moving the Pawn" << i + 1 << endl;
                // Todo >>>>>>>>>>>>>

                // Update the movesCounter
                movesCounter++;

                // Resetting the pieceName, pieceColor and pieceIndex
                pieceName = "";
                pieceColor = ' ';
                pieceIndex = 0;
                break;
            }
        }
    }

    // Show path for black pieces
    if (name == "king" && color == 'b')
    {
        cout << "Moving the King" << endl;
        // Todo >>>>>>>>>>>>>>>>

        // Update the movesCounter
        movesCounter++;

        // Resetting the pieceName, pieceColor and pieceIndex
        pieceName = "";
        pieceColor = ' ';
        pieceIndex = 0;
    }
    else if (name == "queen" && color == 'b')
    {
        cout << "Moving the Queen" << endl;
        // Todo >>>>>>>>>>>>>>>>

        // Update the movesCounter
        movesCounter++;

        // Resetting the pieceName, pieceColor and pieceIndex
        pieceName = "";
        pieceColor = ' ';
        pieceIndex = 0;
    }
    else if (name == "bishop" && color == 'b')
    {
        for (int i = 0; i < 2; i++)
        {
            if (b_bishop[i].index == pieceIndex)
            {
                cout << "Moving the Bishop" << i + 1 << endl;
                // Todo >>>>>>>>>>>>>

                // Update the movesCounter
                movesCounter++;

                // Resetting the pieceName, pieceColor and pieceIndex
                pieceName = "";
                pieceColor = ' ';
                pieceIndex = 0;
                break;
            }
        }
    }
    else if (name == "rook" && color == 'b')
    {
        for (int i = 0; i < 2; i++)
        {
            if (b_rook[i].index == pieceIndex)
            {
                cout << "Moving the Rook" << i + 1 << endl;
                // Todo >>>>>>>>>>>>>

                // Update the movesCounter
                movesCounter++;

                // Resetting the pieceName, pieceColor and pieceIndex
                pieceName = "";
                pieceColor = ' ';
                pieceIndex = 0;
                break;
            }
        }
    }
    else if (name == "knight" && color == 'b')
    {
        for (int i = 0; i < 2; i++)
        {
            if (b_knight[i].index == pieceIndex)
            {
                cout << "Moving the Knight" << i + 1 << endl;
                // Todo >>>>>>>>>>>>>

                // Update the movesCounter
                movesCounter++;

                // Resetting the pieceName, pieceColor and pieceIndex
                pieceName = "";
                pieceColor = ' ';
                pieceIndex = 0;
                break;
            }
        }
    }
    else if (name == "pawn" && color == 'b')
    {
        for (int i = 0; i < 8; i++)
        {
            if (b_pawn[i].index == pieceIndex)
            {
                cout << "Moving the Pawn" << i + 1 << endl;
                // Todo >>>>>>>>>>>>>

                // Update the movesCounter
                movesCounter++;

                // Resetting the pieceName, pieceColor and pieceIndex
                pieceName = "";
                pieceColor = ' ';
                pieceIndex = 0;
                break;
            }
        }
    }
}

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
    chessboard[b_king.row][b_king.column] = b_king.color + b_king.name;
    chessboard[b_queen.row][b_queen.column] = b_queen.color + b_queen.name;
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

chessPiece *selectPiece(int row, int column, string &pieceName, char &pieceColor, int &pieceIndex)
{
    // Check if the selection is valid
    if (chessboard[row][column] == "[ ]")
    {
        cout << "Invalid Selection, Please select a valid piece" << endl;
        return nullptr;
    }

    if (isWhitePlaying && chessboard[row][column][0] == 'w')
    {
        // If king or queen is selected
        if (w_king.row == row && w_king.column == column)
        {
            // Updating the values
            pieceName = w_king.name;
            pieceColor = w_king.color;
            pieceIndex = w_king.index;
            w_king.showPath();
            return &w_king;
        }
        if (w_queen.row == row && w_queen.column == column)
        {
            // Updating the values
            pieceName = w_queen.name;
            pieceColor = w_queen.color;
            pieceIndex = w_queen.index;
            w_queen.showPath();
            return &w_queen;
        }

        // If a pawn is selected
        for (int i = 0; i < 8; i++)
        {
            if (w_pawn[i].row == row && w_pawn[i].column == column && w_pawn[i].isAlive)
            {
                // Updating the values
                pieceName = w_pawn[i].name;
                pieceColor = w_pawn[i].color;
                pieceIndex = w_pawn[i].index;

                w_pawn[i].showPath();
                return &w_pawn[i];
            }
        }

        // If a rook, bishop, or knight is selected
        for (int i = 0; i < 2; i++)
        {
            if (w_rook[i].row == row && w_rook[i].column == column && w_rook[i].isAlive)
            {
                // Updating the values
                pieceName = w_rook[i].name;
                pieceColor = w_rook[i].color;
                pieceIndex = w_rook[i].index;

                w_rook[i].showPath();
                return &w_rook[i];
            }
            if (w_bishop[i].row == row && w_bishop[i].column == column && w_bishop[i].isAlive)
            {
                // Updating the values
                pieceName = w_bishop[i].name;
                pieceColor = w_bishop[i].color;
                pieceIndex = w_bishop[i].index;

                w_bishop[i].showPath();
                return &w_bishop[i];
            }
            if (w_knight[i].row == row && w_knight[i].column == column && w_knight[i].isAlive)
            {
                // Updating the values
                pieceName = w_knight[i].name;
                pieceColor = w_knight[i].color;
                pieceIndex = w_knight[i].index;

                w_knight[i].showPath();
                return &w_knight[i];
            }
        }
    }
    else if (isBlackPlaying && chessboard[row][column][0] == 'b')
    {
        // If king or queen is selected
        if (b_king.row == row && b_king.column == column)
        {
            // Updating the values
            pieceName = b_king.name;
            pieceColor = b_king.color;
            pieceIndex = b_king.index;

            b_king.showPath();
            return &b_king;
        }
        if (b_queen.row == row && b_queen.column == column && b_queen.isAlive)
        {
            // Updating the values
            pieceName = b_queen.name;
            pieceColor = b_queen.color;
            pieceIndex = b_queen.index;

            b_queen.showPath();
            return &b_queen;
        }

        // If a pawn is selected
        for (int i = 0; i < 8; i++)
        {
            if (b_pawn[i].row == row && b_pawn[i].column == column && b_pawn[i].isAlive)
            {
                // Updating the values
                pieceName = b_pawn[i].name;
                pieceColor = b_pawn[i].color;
                pieceIndex = b_pawn[i].index;

                b_pawn[i].showPath();
                return &b_pawn[i];
            }
        }

        // If a rook, bishop, or knight is selected
        for (int i = 0; i < 2; i++)
        {
            if (b_rook[i].row == row && b_rook[i].column == column && b_rook[i].isAlive)
            {
                // Updating the values
                pieceName = b_rook[i].name;
                pieceColor = b_rook[i].color;
                pieceIndex = b_rook[i].index;
                b_rook[i].showPath();
                return &b_rook[i];
            }
            if (b_bishop[i].row == row && b_bishop[i].column == column && b_bishop[i].isAlive)
            {
                // Updating the values
                pieceName = b_bishop[i].name;
                pieceColor = b_bishop[i].color;
                pieceIndex = b_bishop[i].index;

                b_bishop[i].showPath();
                return &b_bishop[i];
            }
            if (b_knight[i].row == row && b_knight[i].column == column && b_knight[i].isAlive)
            {
                // Updating the values
                pieceName = b_knight[i].name;
                pieceColor = b_knight[i].color;

                b_knight[i].showPath();
                return &b_knight[i];
            }
        }
    }

    cout << "Invalid Selection, Please select a valid piece" << endl;
    return nullptr;
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
                selectedPiece = selectPiece(rowForSelection, columnForSelection, pieceName, pieceColor, pieceIndex);
                if (selectedPiece)
                {
                    // Resetting flag if right piece is selected
                    isWhiteSelected = false;
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
                if (selectedPiece)
                {
                    // Resetting flag if right piece is selected
                    selectedPiece->move();
                }

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
            isBlackSelected = true;
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
                selectedPiece = selectPiece(rowForSelection, columnForSelection, pieceName, pieceColor, pieceIndex);
                if (selectedPiece)
                {
                    // Resetting flag if right piece is selected
                    isBlackSelected = false;
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
                if (selectedPiece)
                {
                    // Calling the move function
                    selectedPiece->move();
                }
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
