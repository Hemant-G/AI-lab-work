#include <iostream>
#include <vector>

using namespace std;

class state {
public:
    vector<vector<char>> board;
    char player;
    state(vector<vector<char>> b, char p) : board(b), player(p){}
};

state move_gen(char player, state curr, int row, int col) {
    vector<vector<char>> new_board = curr.board;
    new_board[row][col] = player;
    char next_player = (player == 'X') ? 'O' : 'X';
    state new_state(new_board, next_player);
    return new_state;
}

int evaluate(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != '-' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return (board[i][0] == 'X') ? 1 : -1;
        if (board[0][i] != '-' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return (board[0][i] == 'X') ? 1 : -1;
    }

    if (board[0][0] != '-' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return (board[0][0] == 'X') ? 1 : -1;
    if (board[0][2] != '-' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return (board[0][2] == 'X') ? 1 : -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '-') {
                return 2;
            }
        }
    }

    return 0;
}

int mini_max(state curr, char player) {
    int eval = evaluate(curr.board);
    if (eval == 1 || eval == -1 || eval == 0)
        return eval;

    if (player == 'X') {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (curr.board[i][j] == '-') {
                    state next = move_gen('X', curr, i, j);
                    best = max(best, mini_max(next, 'O'));
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (curr.board[i][j] == '-') {
                    state next = move_gen('O', curr, i, j);
                    best = min(best, mini_max(next, 'X'));
                }
            }
        }
        return best;
    }
}

void print_board(const vector<vector<char>>& board) {
    cout << "\n";
    for (const auto& row : board) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

pair<int, int> find_best_move(state curr, char player) {
    int bestVal = (player == 'X') ? -1000 : 1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (curr.board[i][j] == '-') {
                state next = move_gen(player, curr, i, j);
                int moveVal = mini_max(next, (player == 'X') ? 'O' : 'X');
                if ((player == 'X' && moveVal > bestVal) || (player == 'O' && moveVal < bestVal)) {
                    bestVal = moveVal;
                    bestMove = {i, j};
                }
            }
        }
    }
    return bestMove;
}

int main() {
    vector<vector<char>> board(3, vector<char>(3, '-'));
    char human = 'X', ai = 'O'; 
    char turn;

    cout << "Tic-Tac-Toe (You are X, AI is O)\n";
    cout << "Do you want to go first? (y/n): ";
    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y')
        turn = human;
    else
        turn = ai;

    print_board(board);

    while (evaluate(board) == 2) {
        if (turn == human) {
            int move;
            cout << "Enter your move (1-9): ";
            cin >> move;
            if (move < 1 || move > 9) {
                cout << "Invalid move. Try again.\n";
                continue;
            }
            int row = (move - 1) / 3;
            int col = (move - 1) % 3;
            if (board[row][col] != '-') {
                cout << "Cell already taken. Try again.\n";
                continue;
            }
            board[row][col] = human;
        } else {
            cout << "AI's turn...\n";
            state curr(board, ai);
            pair<int, int> move = find_best_move(curr, ai);
            board[move.first][move.second] = ai;
        }
        print_board(board);
        turn = (turn == 'X') ? 'O' : 'X';
    }

    int result = evaluate(board);
    if (result == 1)
        cout << "X wins!\n";
    else if (result == -1)
        cout << "O wins!\n";
    else
        cout << "It's a draw!\n";
}
