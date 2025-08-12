# 8-Puzzle Problem Solution (Best-First Search)

---

## AIM

To solve the 8-puzzle problem using:
- **Best-First Search** with a simple heuristic function.

The objective is to transform an initial configuration of the 8-puzzle into a target (goal) configuration by sliding tiles, using only legal moves, while also reconstructing the sequence of moves (path).

---

## Algorithm

### State Representation

Each board state is represented using a class:
- `vector<int> value`: Flattened 3x3 matrix (0 represents the blank tile).
- `state* parent`: Pointer to the previous state for path reconstruction.
- `int heuristic_value`: Estimated cost to reach the goal.

---

### Move Generation

- Legal moves are calculated based on the position of `0` (blank tile).
- Valid moves include:
  - **Left** (if `index % 3 > 0`)
  - **Right** (if `index % 3 < 2`)
  - **Up** (if `index / 3 > 0`)
  - **Down** (if `index / 3 < 2`)
- For each legal move:
  - Swap blank with the target tile.
  - Create a new `state` with updated configuration.
  - Set `parent` pointer to the current state.

---

### Best-First Search

1. **Initialization**
   - Insert the initial state into a **priority queue** (min-heap by heuristic value).
   - Maintain a `closed` list to store visited states.

2. **Loop**
   - Pop the state with the **lowest heuristic value**.
   - If it matches the goal state → reconstruct and return the path.
   - Generate all valid child states.
   - If a child has not been visited, push it into the priority queue.

3. **Heuristic Function**
   - Counts the number of misplaced tiles.

---

## Complexity

Let:
- `b` = branching factor (~2–4 for 8-puzzle)
- `d` = depth of the optimal solution
- `n` = total possible states (9! = 362,880)

### Time Complexity
- **Worst-case:** \(O(b^d)\) .
- **Best-case:** Significantly fewer states expanded when heuristic is good.

### Space Complexity
- **Priority queue:** Up to \(O(b^d)\) states.
- **Closed list:** Up to \(O(n)\) visited states.
- **Per-state memory:** \(O(1)\) (stores 9 integers + 1 pointer).

---