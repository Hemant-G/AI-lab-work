# Grid Pathfinding using A* Search Algorithm  


## AIM  

To solve the **pathfinding problem** on a 2D grid using the **A* Search Algorithm**, while avoiding obstacles (water cells).  
The objective is to find the shortest path from a **start point** to a **goal point**, reconstructing the sequence of moves (path) if one exists.  


## Algorithm  

### State Representation  

Each state is represented using a `state` class:  
- `point location`: Current grid cell coordinates `(x, y)`  
- `float g_cost`: Cost from **start** node to current node  
- `float h_cost`: Heuristic estimate from current node to **goal**  
- `float f_cost`: Total cost (`g_cost + h_cost`)  
- `point parent`: Parent node for path reconstruction  

### Move Generation  

- Possible moves: **8 directions** (up, down, left, right, and diagonals).  
- Each neighbor is valid if:  
  - It lies inside the grid boundaries.  
  - It is **not water** (obstacle).  
  - It has not been already expanded (not in closed list).  

- **Move Costs:**  
  - Orthogonal moves (up, down, left, right): cost = `1.0`  
  - Diagonal moves: cost = `1.5`  

### Heuristic Function  

- The **Manhattan distance** is used:  

h(n) = |x(goal) - x(n)| + |y(goal) - y(n)|

This ensures admissibility and guides the search towards the goal.  

### A* Search Algorithm  

1. Initialize:  
   - Insert the start node into the **open list** (priority queue, ordered by `f_cost`).  
   - `closed list` is empty.  

2. While the open list is not empty:  
   - Select node with the **lowest f_cost**.  
   - If it matches the **goal**, stop and reconstruct the path.  
   - Otherwise, generate valid neighbors, compute their costs, and push them into the open list.  
   - Add current node to closed list.  

3. If goal is reached, trace back parents to reconstruct the path.  
4. If open list is empty and goal not found : **no path exists**.  


## Complexity  

Let:  
- `b` = branching factor (max 8 neighbors in grid).  
- `d` = depth of the optimal path (number of steps).  
- `n` = total number of cells (`grid_x * grid_y`).  

### Time Complexity  

- **Worst-case:** `O(b^d)`.  

### Space Complexity  

- **Open list (priority queue):** Up to `O(n)` nodes.  
- **Closed list:** Stores visited states, also up to `O(n)`.  
- **Per-state memory:** Constant, since each state stores only `(x,y)` and costs.  


## Example  

### Input  
- Grid size: `5 x 6`  
- Start: `(1,4)`  
- Goal: `(4,5)`  
- Water (obstacles): `{(3,5), (3,4), (2,3), (2,1), (1,0)}`  

### Output  
Path found:
(1,4) -> (2,4) -> (3,3) -> (4,4) -> (4,5) -> Goal