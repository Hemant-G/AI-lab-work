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

# Water Jug Problem Solution (BFS)

---

## AIM

To solve the classic Water Jug problem using Breadth-First Search (BFS) for state-space search, where the objective is to measure an exact amount of water using two jugs of given capacities.

---

## Problem Description

Given two jugs with capacities `capacity_1` and `capacity_2`, and a target amount `target`, the goal is to find a sequence of steps to get exactly `target` liters of water in either of the jugs. The allowed operations are:
- Fill a jug completely.
- Empty a jug.
- Pour water from one jug to the other until either the first jug is empty or the second jug is full.

---

## Algorithm

### State Representation

- Each state is represented by:
  - `jug1`: current amount of water in jug 1.
  - `jug2`: current amount of water in jug 2.
  - `parent`: pointer to the previous state, for reconstructing the solution path.

### State Generation

From a current state, generate all possible next states by performing one of the allowed operations:
1. Fill Jug 1 to capacity.
2. Fill Jug 2 to capacity.
3. Empty Jug 1.
4. Empty Jug 2.
5. Pour water from Jug 1 to Jug 2.
6. Pour water from Jug 2 to Jug 1.

### Breadth-First Search (BFS)

- Use a queue to explore states level-by-level.
- Use a set to keep track of visited states to avoid repetition.
- Continue until a state with the target amount in either jug is found or all states are exhausted.

---

## Complexity

Let:
- `C1`, `C2`: capacities of the two jugs.
- `V = (C1 + 1) * (C2 + 1)`: total possible states (all combinations of water levels).

### Time Complexity

- BFS explores each state once:  
  **O(V)  or  O(C1*C2)**

### Space Complexity

- Stores visited states and queue contents:  
  **O(V)  or  O(C1*C2)**

---
