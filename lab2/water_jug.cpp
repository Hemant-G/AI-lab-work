#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

class state
{
public:
    state* parent;
    int jug1;
    int jug2;

    state(state* p, int j1, int j2) : parent(p), jug1(j1), jug2(j2) {}
};

bool is_goal_state(const state* curr_state, int target)
{
    return curr_state->jug1 == target || curr_state->jug2 == target;
}

vector<state*> generate_states(state* curr_state, int capacity_1, int capacity_2)
{
    vector<state*> result;
    int j1 = curr_state->jug1;
    int j2 = curr_state->jug2;

    // 1. Fill Jug1
    result.push_back(new state(curr_state, capacity_1, j2));
    // 2. Fill Jug2
    result.push_back(new state(curr_state, j1, capacity_2));
    // 3. Empty Jug1
    result.push_back(new state(curr_state, 0, j2));
    // 4. Empty Jug2
    result.push_back(new state(curr_state, j1, 0));
    // 5. Jug1 -> Jug2
    {
        int pour = min(j1, capacity_2 - j2);
        result.push_back(new state(curr_state, j1 - pour, j2 + pour));
    }
    // 6. Jug2 -> Jug1
    {
        int pour = min(j2, capacity_1 - j1);
        result.push_back(new state(curr_state, j1 + pour, j2 - pour));
    }

    return result;
}

vector<state*> solve_water_jug(int capacity_1, int capacity_2, int target)
{
    vector<state*> path;
    queue<state*> Q;
    set<pair<int, int>> visited;

    state* init = new state(nullptr, 0, 0);
    Q.push(init);

    while (!Q.empty())
    {
        state* curr_state = Q.front();
        Q.pop();

        if (visited.count({curr_state->jug1, curr_state->jug2}))
            continue;

        visited.insert({curr_state->jug1, curr_state->jug2});

        if (is_goal_state(curr_state, target))
        {
            state* ptr = curr_state;
            while (ptr != nullptr)
            {
                path.push_back(ptr);
                ptr = ptr->parent;
            }
            return path;
        }

        vector<state*> next_states = generate_states(curr_state, capacity_1, capacity_2);
        for (auto next : next_states)
        {
            if (!visited.count({next->jug1, next->jug2}))
                Q.push(next);
        }
    }

    return path;
}

void print_path(const vector<state*>& path)
{
    cout << "Solution Path:\n";
    for (int i = path.size() - 1; i >= 0; i--)
    {
        cout << "(" << path[i]->jug1 << ", " << path[i]->jug2 << ")\n";
    }
}

int main()
{
    int capacity_1 = 101, capacity_2 = 97, target = 5;

    vector<state*> solution = solve_water_jug(capacity_1, capacity_2, target);

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
