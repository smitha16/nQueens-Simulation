# N-Queens Simulation

An interactive visualization of the N-Queens problem built with C and OpenGL (GLUT). Watch the backtracking algorithm solve the classic puzzle in real time on an N×N chessboard.

![Platform](https://img.shields.io/badge/platform-Windows-blue) ![Language](https://img.shields.io/badge/language-C-orange) ![API](https://img.shields.io/badge/API-OpenGL%20%2F%20GLUT-green)

---

## What is the N-Queens Problem?

Place N chess queens on an N×N chessboard so that no two queens threaten each other, meaning no two queens share the same row, column, or diagonal. This project visualizes every step of finding all solutions using a **recursive backtracking** algorithm.

---

## Features

- Interactive OpenGL rendering of the chessboard and queens
- **Full Simulation mode** — watch the algorithm try positions in real time (conflicts highlighted in red, valid placements in green)
- **Possible Solutions mode** — skip straight to viewing all valid solutions
- Choose board size N from **4 to 8** via right-click menu
- Live solution counter displayed on screen

---

## Demo

| Screen 1 — Select N | Screen 2 — Chessboard | Full Simulation |
|---|---|---|
| Right-click to pick N (4–8) | N×N board is drawn | Algorithm backtracks live |

---

## Getting Started

### Prerequisites

- Windows OS
- Visual Studio 2019 (or later)
- OpenGL + GLUT libraries (freeglut recommended)

### Setup

1. **Clone the repository**
   ```bash
   git clone https://github.com/your-username/n-queens-simulation.git
   cd n-queens-simulation
   ```

2. **Open in Visual Studio**
   - Open `CG_Projexct_part2.vcxproj`

3. **Configure OpenGL/GLUT**
   - Place `freeglut` headers in your include path
   - Link against `opengl32.lib`, `glu32.lib`, and `freeglut.lib`
   - Copy `freeglut.dll` to the project output directory

4. **Build and Run**
   - Set build configuration to `Release` or `Debug` (x86)
   - Press `Ctrl+F5` to run

---

## How to Use

1. **Launch** the application — an intro screen explains the problem
2. **Right-click** to open the menu and select a value of N (4 through 8)
3. The N×N chessboard appears — **right-click again** to choose a mode:
   - **Full Simulation** — animated step-by-step backtracking
   - **Possible Solutions** — displays only the final valid arrangements
4. Watch the solution counter increment as each valid placement is found

### Color Guide

| Color | Meaning |
|-------|---------|
| 🟩 Green | Queen placed successfully (no conflicts) |
| 🟥 Red | Conflict detected — queen cannot be placed here |

---

## Project Structure

```
n-queens-simulation/
├── Source.c                          # Main source file
├── CG_Projexct_part2.vcxproj        # Visual Studio project file
├── CG_Projexct_part2.vcxproj.filters
├── CG_Projexct_part2.vcxproj.user
└── README.md
```

---

## Algorithm

The solver uses **recursive backtracking with depth-first search**:

- One row is processed at a time
- For each column in the current row, `place()` checks for column and diagonal conflicts
- If valid, the queen is placed and the algorithm recurses to the next row
- If a conflict is found, it backtracks and tries the next column
- Time complexity: **O(N!)**

---
