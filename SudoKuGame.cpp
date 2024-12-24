#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class SudokuBoard {
private:
    static const int N = 9;
    int board[N][N];

public:
    SudokuBoard(int initialBoard[N][N]) {
        memcpy(board, initialBoard, sizeof(board));
    }

    bool isSafe(int row, int col, int num) {
        for (int i = 0; i < N; i++)
            if (board[row][i] == num || board[i][col] == num)
                return false;

        int boxRowStart = row - row % 3;
        int boxColStart = col - col % 3;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i + boxRowStart][j + boxColStart] == num)
                    return false;

        return true;
    }

    bool solveSudoku(int row = 0, int col = 0) {
        if (row == N - 1 && col == N)
            return true;

        if (col == N) {
            row++;
            col = 0;
        }

        if (board[row][col] != 0)
            return solveSudoku(row, col + 1);

        for (int num = 1; num <= 9; num++) {
            if (isSafe(row, col, num)) {
                board[row][col] = num;
                if (solveSudoku(row, col + 1))
                    return true;
                board[row][col] = 0;
            }
        }
        return false;
    }

    void printBoard() {
        system("cls");
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                if (col == 3 || col == 6)
                    cout << " | ";
                cout << board[row][col] << " ";
            }
            if (row == 2 || row == 5) {
                cout << endl;
                for (int i = 0; i < N; i++)
                    cout << "---";
            }
            cout << endl;
        }
    }

    bool isSolvedCompletely() {
        for (int row = 0; row < N; row++)
            for (int col = 0; col < N; col++)
                if (board[row][col] == 0)
                    return false;
        return true;
    }

    int (*getBoard())[N] { return board; }
};

class SudokuGame {
private:
    static const int N = 9;
    SudokuBoard easyBoard;
    SudokuBoard mediumBoard;
    SudokuBoard hardBoard;

public:
    SudokuGame(int easy[N][N], int medium[N][N], int hard[N][N])
        : easyBoard(easy), mediumBoard(medium), hardBoard(hard) {}

    void playGame(SudokuBoard &board) {
        int row, col, num;
        while (true) {
            board.printBoard();
            cout << "Enter row (-1 to solve): ";
            cin >> row;
            if (row == -1) {
                board.solveSudoku();
                board.printBoard();
                cout << "Solved Sudoku. Better luck next time!" << endl;
                return;
            }
            cout << "Enter column: ";
            cin >> col;
            cout << "Enter number: ";
            cin >> num;

            if (!board.isSafe(row - 1, col - 1, num)) {
                cout << "Invalid move. Try again." << endl;
                continue;
            }
            board.getBoard()[row - 1][col - 1] = num;

            if (board.isSolvedCompletely()) {
                cout << "Congratulations! You solved the puzzle!" << endl;
                board.printBoard();
                return;
            }
        }
    }

    void showMenu() {
        while (true) {
            int choice;
            cout << "[1] Start Game\n[2] View Solved Sudoku\n[3] How to Play\n[4] Exit\n";
            cout << "Select your choice: ";
			cin >> choice;
            if (choice == 4) break;

            switch (choice) {
            case 1: {
                int level;
                cout << "Choose level: [1] Easy, [2] Medium, [3] Hard: ";
                cin >> level;
                if (level == 1) playGame(easyBoard);
                else if (level == 2) playGame(mediumBoard);
                else if (level == 3) playGame(hardBoard);
                break;
            }
            case 2: {
                int level;
                cout << "View solution for: [1] Easy, [2] Medium, [3] Hard: ";
                cin >> level;
                if (level == 1) easyBoard.solveSudoku(), easyBoard.printBoard();
                else if (level == 2) mediumBoard.solveSudoku(), mediumBoard.printBoard();
                else if (level == 3) hardBoard.solveSudoku(), hardBoard.printBoard();
                break;
            }
            case 3:
                cout << "How to Play: Fill the grid with digits 1-9 following the rules of Sudoku..." << endl;
                break;
            }
        }
    }
};

int main() {
    const int N = 9;
    int easy[N][N] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5}, //easy
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    int medium[N][N] = {
        {0, 0, 0, 3, 0, 2, 9, 0, 5},
        {0, 0, 9, 6, 4, 0, 7, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 2},
        {0, 5, 0, 0, 0, 0, 0, 3, 6},
        {2, 0, 3, 8, 6, 5, 0, 7, 9}, //medium
        {9, 6, 1, 2, 0, 7, 0, 4, 8},
        {4, 0, 2, 0, 0, 0, 0, 0, 7},
        {1, 7, 0, 5, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 4, 6, 0, 0}
    };

    int hard[N][N] = {
        {0, 0, 0, 0, 9, 0, 6, 0, 0},
        {3, 0, 0, 0, 0, 0, 0, 8, 0},
        {7, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 7, 0, 8, 0, 0, 0},
        {0, 9, 0, 0, 0, 0, 2, 0, 0}, //hard
        {5, 0, 0, 3, 0, 0, 0, 0, 0},
        {0, 0, 0, 8, 0, 0, 0, 3, 5},
        {4, 0, 0, 0, 0, 0, 0, 0, 7},
        {0, 6, 0, 0, 0, 0, 0, 0, 0}
    };

    SudokuGame game(easy, medium, hard);
    game.showMenu();
    return 0;
}

