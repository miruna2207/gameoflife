# Game of Life – C Programming Project

## What This Project Does
This is an extended, interactive version of John Conway's Game of Life, a classic simulation where cells evolve based on their neighbours. In this version, the game is explored through four tasks, each showcasing a new data structure or computational strategy. This is a personal and academic project that blends structure, logic and memory usage. Built entirely in C, this simulation explores cellular automata and key computer science concepts like stacks, trees, and graphs 

For more details:  
https://site-pa.netlify.app/proiecte/game_of_life/

---

## Task 1 – Classic Game of Life
Simulate the matrix evolution over k generations on an N x M grid. Each cell is either: Alive or Dead  

Cells evolve using Conway’s rules:

1. **Underpopulation** – Alive cell with <2 neighbours dies  
2. **Survival** – Alive cell with 2–3 neighbours survives  
3. **Overpopulation** – Alive cell with >3 neighbours dies  
4. **Reproduction** – Dead cell with exactly 3 neighbours becomes alive  

---

## Task 2 – Stack-Based track of changes
Track changes between generations using a stack:  
- Stores heads of linked lists representing modified cells per generation  
- Allows reversal: given the final state and the stack, reconstruct the original matrix  

---

## Task 3 – Binary Tree of Rule Variants
Add a twist by generating a binary tree of generations:

- **Right child**: follows Conway's classic rules  
- **Left child**: applies Rule B : Any cell with exactly 2 live neighbours becomes alive  

To keep memory usage low, each node stores only change lists, not full matrices.  

---

## Task 4 – Hamiltonian Path Check (Graph)
Transform the current matrix into a graph, and check for a Hamiltonian path (a path that visits every node (cell) in a connected component exactly once):

- If found, output: Path length & Path sequence  
- If not, return -1  

This is performed on each node in the rule tree created in Task 3.  

---

## How to Build & Run

### Requirements
- A working C compiler (e.g., gcc)  
- Unix-like OS recommended (Linux/macOS)  

### Build
```bash
make build
```

### Run
```bash
./game input output
```

Input file contains:  
1. On the first line – the task  
2. On the second – the matrix's dimensions (N M)  
3. On the third – the number of generations (k)  
4. On the next line – the initial matrix  

---

### For bonus.c:
**Build**
```bash
gcc bonus.c gamelib.c
```

**Run**
```bash
./a.out input output
```

The input file contains the stack built in task2 and the final matrix.  

---

## File Structure
- `game.c` → Entry point – menu and interaction  
- `gamelib.c/.h` → Library for tasks 1–3  
- `graph.c/.h` → Library with graph based functions (Task 4)  
- `makefile` → Build script  
- `bonus.c` → The reverse of task2  
