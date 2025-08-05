#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct state
{
    state* parent;
    vector<int> value;
};

bool is_goal_state(const state curr_state, const state goal_state)
{
    return curr_state.value == goal_state.value;
}

vector<int> generate_moves(int index)
{
    vector<int> moves;

    if (index % 3 > 0) moves.push_back(index - 1);  
    if (index % 3 < 2) moves.push_back(index + 1);

    if (index / 3 > 0) moves.push_back(index - 3);
    if (index / 3 < 2) moves.push_back(index + 3);

    return moves;
}

vector<state> generate_states(state curr_state)
{
    vector<state> result;
    int blank_index = -1;

    for (int i = 0; i < curr_state.value.size(); i++)
    {
        if (curr_state.value[i] == 0)
        {
            blank_index = i;
            break;
        }
    }

    vector<int> moves = generate_moves(blank_index);

    for (int move : moves)
    {
        state new_state;
        new_state.value = curr_state.value;

        int temp = new_state.value[blank_index];
        new_state.value[blank_index] = new_state.value[move];
        new_state.value[move] = temp;

        new_state.parent = new state(curr_state);
        result.push_back(new_state);
    }

    return result;
}

bool is_visited(const vector<vector<int>>& closed, const vector<int> value)
{
    for (const auto v : closed)
    {
        if (v == value) return true;
    }
    return false;
}

vector<state> solve_puzzle(state init_state, state goal_state)
{
    vector<state> result;
    stack<state> S;
    vector<vector<int>> closed;

    S.push(init_state);

    while (!S.empty())
    {
        state curr_state = S.top();
        S.pop();

        if (is_visited(closed, curr_state.value)) 
        {   
            continue;
        }
        closed.push_back(curr_state.value);

        if (is_goal_state(curr_state, goal_state))
        {
            state* ptr = &curr_state;
            while (ptr != nullptr)
            {
                result.push_back(*ptr);
                ptr = ptr->parent;
            }
            return result;
        }

        vector<state> next_states = generate_states(curr_state);
        for (state next : next_states)
        {
            if (!is_visited(closed, next.value))
                S.push(next);
        }
    }

    return result;
}

void print_path(vector<state>& path)
{
    cout << "Solution Path:\n";
    for (int i = path.size() - 1; i >= 0; i--)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << path[i].value[j] << " ";
            if ((j + 1) % 3 == 0) cout << "\n";
        }
        cout << "------\n";
    }
}


int main()
{
    state initial{nullptr, {1, 2, 3, 4, 5, 6, 7, 0, 8}};
    state goal{nullptr, {1, 2, 3, 4, 5, 6, 7, 8, 0}};

    vector<state> solution = solve_puzzle(initial, goal);

    if (!solution.empty())
    {
        cout << "Solution found! Moves: " << solution.size() - 1 << "\n";
        print_path(solution);
    }
    else
    {
        cout << "No solution found.\n";
    }

    return 0;
}
