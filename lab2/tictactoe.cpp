#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const char HUMAN = 'O';
const char AI = 'X';
const char EMPTY = '-';

void print_board(vector<char>& board) {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        cout << board[i] << " ";
        if (i % 3 == 2) cout << "\n";
    }
    cout << "\n";
}

int wins[8][3] = {
    {0,1,2},{3,4,5},{6,7,8},
    {0,3,6},{1,4,7},{2,5,8},
    {0,4,8},{2,4,6}
};

bool is_winner(vector<char>& board, char player) {
    for (int* w : wins) {
        if (board[w[0]] == player && board[w[1]] == player && board[w[2]] == player)
            return true;
    }
    return false;
}

bool is_cell_left(vector<char>& board) {
    return count(board.begin(), board.end(), EMPTY) > 0;
}

int evaluate(vector<char>& board) {
    int score = 0;
    for (int* w : wins) {
        bool ai_possible = true, human_possible = true;
        for (int i = 0; i < 3; i++) {
            if (board[w[i]] == HUMAN) ai_possible = false;
            if (board[w[i]] == AI) human_possible = false;
        }
        if (ai_possible) score++;
        if (human_possible) score--;
    }
    return score;
}

int minimax(vector<char>& board, int depth, bool is_max, int max_depth) {
    if (is_winner(board, AI)) return 100 - depth;
    if (is_winner(board, HUMAN)) return depth - 100;
    if (!is_cell_left(board) || depth == max_depth) 
        return evaluate(board);

    if (is_max) {
        int best = -1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] == EMPTY) {
                board[i] = AI;
                best = max(best, minimax(board, depth+1, false, max_depth));
                board[i] = EMPTY;
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] == EMPTY) {
                board[i] = HUMAN;
                best = min(best, minimax(board, depth+1, true, max_depth));
                board[i] = EMPTY;
            }
        }
        return best;
    }
}

int find_best_move(vector<char>& board, int max_depth=4) {
    int best_val = -1000;
    int best_move = -1;

    for (int i = 0; i < 9; i++) {
        if (board[i] == EMPTY) {
            board[i] = AI;
            int move_val = minimax(board, 0, false, max_depth);
            board[i] = EMPTY;

            if (move_val > best_val) {
                best_move = i;
                best_val = move_val;
            }
        }
    }
    return best_move;
}

int main() {
    vector<char> board(9, EMPTY);

    cout << "Tic Tac Toe Game (You = O, AI = X)\n";
    print_board(board);

    while (true) {
        int move;
        cout << "Enter your move (1-9): ";
        cin >> move;
        if (move-1 < 0 || move-1 >= 9 || board[move-1] != EMPTY) {
            cout << "Invalid move, try again.\n";
            continue;
        }
        board[move-1] = HUMAN;
        print_board(board);

        if (is_winner(board, HUMAN)) { cout << "You win!\n"; break; }
        if (!is_cell_left(board)) { cout << "Draw!\n"; break; }

        int best_move = find_best_move(board, 4);
        board[best_move] = AI;
        cout << "AI chooses: " << best_move+1 << "\n";
        print_board(board);

        if (is_winner(board, AI)) { cout << "AI wins!\n"; break; }
        if (!is_cell_left(board)) { cout << "Draw!\n"; break; }
    }
    return 0;
}
