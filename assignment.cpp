#include <iostream>
using namespace std;


void create_table(char chess[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            chess[i][j] = '.';
        }
    }
}


void queen_moves(char chess[10][10], int row, int column) {
    for (int i = 0; i < 10; i++) {
        chess[row - 1][i] = 'Q';
        chess[i][column - 1] = 'Q';


        if (row - 1 - i >= 0 && column - 1 - i >= 0) 
            chess[row - 1 - i][column - 1 - i] = 'Q';
        if (row - 1 - i >= 0 && column - 1 + i < 10) 
            chess[row - 1 - i][column - 1 + i] = 'Q';
        if (row - 1 + i < 10 && column - 1 - i >= 0) 
            chess[row - 1 + i][column - 1 - i] = 'Q';
        if (row - 1 + i < 10 && column - 1 + i < 10) 
            chess[row - 1 + i][column - 1 + i] = 'Q';
    }
}


void display_board(char chess[10][10]) {
    cout << "\n____Chessboard____\n";
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << chess[i][j] << "  ";
        }
        cout << endl;
    }
    cout << "----------------------------\n";
}


bool is_valid_move(int row, int column, int new_row, int new_column) {
    return (new_row == row || new_column == column || 
            abs(new_row - row) == abs(new_column - column));
}

int main() {
    char chess[10][10];
    int row = 5, column = 8; 


    create_table(chess);


    queen_moves(chess, row, column);
    chess[row - 1][column - 1] = 'S';


    while (true) {
        cout << "Enter the new position of the Queen (row and column, 0 to exit): ";
        int new_row, new_column;
        cin >> new_row;

        if (new_row == 0) break; 
        cin >> new_column;
        if (new_column == 0) break;


        if (new_row < 1 || new_row > 10 || new_column < 1 || new_column > 10) {
            cout << "Position out of bounds. Try again.\n";
            continue;
        }

        if (is_valid_move(row, column, new_row, new_column)) {
            row = new_row;
            column = new_column;

            create_table(chess);
            queen_moves(chess, row, column);
            
            chess[row - 1][column - 1] = 'S';
            display_board(chess);
        } else {
            cout << "Invalid move. Queen can't move there. Try again.\n";
        }
    }

    cout << "Thanks for playing the game!";
    return 0;
}
