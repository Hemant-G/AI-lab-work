# AI-lab-work
# 8-Puzzle Problem Solution (DFS & BFS)

---

## AIM

To solve the 8-puzzle problem using :
- Depth-First Search (DFS)
- Breadth-First Search (BFS)

The objective is to transform an initial configuration of the 8-puzzle into a target (goal) configuration by sliding tiles, using only legal moves, while also reconstructing the sequence of moves (path).

---

## Algorithm

### State Representation

Each board state is represented using a structure:
- `vector<int> value`: Flattened 3x3 matrix (0 represents the blank tile).
- `state* parent`: Pointer to the previous state for path reconstruction.

### Move Generation

- Legal moves are calculated based on the position of `0`.
- Valid directions include up, down, left, and right, depending on boundary conditions.
- Each valid move results in a new `state`.

### Depth-First Search (DFS)

- Explores as deep as possible along each path before backtracking.
- Implemented using a **stack** (LIFO).

### Breadth-First Search (BFS)

- Explores all neighbors at the current depth before moving to the next level.
- Implemented using a **queue** (FIFO).

---

## Complexity

Let:
- `b`: branching factor (number of possible moves per state, typically 2–4 for 8-puzzle).
- `d`: depth (number of moves to reach the goal)
- `n`: total number of possible states (8-puzzle has 9! = 362,880 permutations).
- `m` = maximum depth of the DFS search tree or longest path explored in DFS.

### Time Complexity

#### Depth-First Search (DFS):
- **Worst-case time complexity:** `O(b^d)`
- In the worst case, it may need to explore nearly all nodes in a deeply nested path before backtracking.

#### Breadth-First Search (BFS):
- **Worst-case time complexity:** `O(b^d)`
- Unlike DFS, BFS explores all possible moves at depth 1, then depth 2, and so on.

### Space Complexity

#### Depth-First Search (DFS)
- **Stack size:**  
  - Holds states along the current search path.
  - Maximum depth \(m\) corresponds to the length of the deepest path explored.
- **Closed list:**  
  - Stores all visited states, up to \(O(n)\), where \(n\) is the number of unique states visited (max \(9!\)).
- **Per-state memory:**  
  - Each state requires \(O(1)\) space (9 ints + 1 pointer).

---
#### Breadth-First Search (BFS)
- **Queue size:**  
  - Stores all states at the current search depth.
  - Can grow as large as \(O(b^d)\), where \(b\) is the branching factor (~2–4) and \(d\) is the solution depth.
- **Closed list:**  
  - Same as DFS, stores visited states \(O(n)\).
- **Per-state memory:**  
  - Each state requires \(O(1)\) space.
