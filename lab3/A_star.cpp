#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;

class point {
public:
    int x, y;
    point(int x = 0, int y = 0) : x(x), y(y) {}
};

class state {
public:
    point location;
    float g_cost, h_cost, f_cost;
    point parent;
    state(point loc = {}, float g = 0, float h = 0, point p = {})
        : location(loc), g_cost(g), h_cost(h), f_cost(g + h), parent(p) {}
    bool operator<(const state& other) const {
        return f_cost > other.f_cost;
    }
};

bool is_water(point curr, vector<point>& water) {
    for (auto p : water) if (curr.x == p.x && curr.y == p.y) return true;
    return false;
}

bool is_closed(point p, vector<point>& closed) {
    for (auto v : closed) if (p.x == v.x && p.y == v.y) return true;
    return false;
}

float manhattan_dist(point a, point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

vector<state> move_gen(int n_x, int n_y, state curr, point goal,
                       vector<point>& water, vector<point>& closed) {
    vector<state> neighbors;
    int dx[] = {-1, 1, 0, 0, -1, 1, -1, 1};
    int dy[] = {0, 0, -1, 1, -1, -1, 1, 1};
    for (int i = 0; i < 8; i++) {
        point neighbor_loc(curr.location.x + dx[i], curr.location.y + dy[i]);
        if (neighbor_loc.x >= 0 && neighbor_loc.x < n_x && neighbor_loc.y >= 0 && neighbor_loc.y < n_y 
            && !is_water(neighbor_loc, water) && !is_closed(neighbor_loc, closed)) {
            float move_cost = (abs(dx[i]) == 1 && abs(dy[i]) == 1) ? 1.5 : 1.0;
            float new_g = manhattan_dist(neighbor_loc, goal);
            float new_h = curr.h_cost + move_cost;
            state nb(neighbor_loc, new_g, new_h, curr.location);
            neighbors.push_back(nb);
        }
    }
    return neighbors;
}

point get_parent(point p, vector<pair<point, point>>& parent_list) {
    for (auto& pr : parent_list)
        if (pr.first.x == p.x && pr.first.y == p.y)
            return pr.second;
    return point(-1, -1);
}

vector<point> solve(int n_x, int n_y, point start, point goal, vector<point> water) {
    priority_queue<state> open;
    vector<point> closed;
    vector<pair<point, point>> parent_list;

    float g0 = manhattan_dist(start, goal);
    float h0 = 0.0f;
    open.emplace(start, g0, h0, point(-1,-1));

    while (!open.empty()) {
        state current = open.top();
        open.pop();

        if (is_closed(current.location, closed)) continue;
        closed.push_back(current.location);
        parent_list.push_back({current.location, current.parent});

        if (current.location.x == goal.x && current.location.y == goal.y) {
            vector<point> path;
            for (point p = goal; p.x != -1; p = get_parent(p, parent_list)) {
                path.push_back(p);
                if (p.x == start.x && p.y == start.y) break;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        vector<state> neighbors = move_gen(n_x, n_y, current, goal, water, closed);
        for (auto nb : neighbors) open.push(nb);
    }
    return {};
}

void print_path(vector<point>& path) {
    if (path.empty()) {
        cout << "No path found!\n";
    } else {
        cout << "Path found:\n";
        for (auto p : path) cout << "(" << p.x << "," << p.y << ") -> ";
        cout << "Goal\n";
    }
}

int main() {
    vector<point> water = {{3,5}, {3,4}, {2,3}, {2,1}, {1,0}};
    point start(1,4), goal(4,5);
    int grid_x = 5, grid_y = 6;

    vector<point> path = solve(grid_x, grid_y, start, goal, water);
    print_path(path);
}