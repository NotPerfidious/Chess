# Chess Game (C++ OOP Project)

## Overview
This is a **console-based Chess game** written in **C++** as a personal project to practice:
- Object-Oriented Programming (OOP)
- Problem-solving
- Multi-file project organization
- Using a custom data structure in gameplay logic

The game follows **real chess rules** and uses a **hidden stack** for behind-the-scenes move validation. Players enter moves in standard algebraic coordinate notation (e.g., `e2 e4`) and play entirely in the console.

---

## Features
- **Standard chess movement** for King (`Kg`), Queen (`Qn`), Rook (`Rk`), Bishop (`Bp`), Knight (`Kn`), and Pawn (`Pn`).
- **Special rules**:
  - Castling
  - Pawn promotion
- **Game ending conditions**:
  - Check
  - Checkmate
  - Stalemate
  - Draw (two kings left)
- **Hidden stack system** to:
  - Simulate moves for legality checks
  - Roll back board state without affecting gameplay
- **Colored output** to distinguish White and Black pieces.

---

## 🛠 How It Works
- **Board Representation**:  
  `Pieces*** board` — a dynamic 8×8 array of `Pieces*`.

- **Piece Classes**:  
  All chess pieces inherit from a base `Pieces` class (`SubPieces.h`).

- **Stack**:  
  Stores move history internally for simulations:
  - Pushes when testing a move
  - Pops to restore the board if the move would leave the king in check
  - Used in checkmate and stalemate detection

- **Move Translation**:  
  `translate_move()` converts moves like `e2 e4` into coordinates and validates format.

- **Main Game Loop** (`ChessMainFunction.cpp`):
  - Alternates turns between White and Black
  - Displays board state
  - Prompts player for moves until game ends

---

## Project Structure
```

Chess/
├── Board.h / Board.cpp         # Board class and game logic
├── SubPieces.h                 # All chess piece classes and movement rules
├── Stack.h                     # Hidden stack for move simulation
├── ChessMainFunction.cpp       # Main game loop

````

---

## How to Play
### 1. Compile
With g++:
```bash
g++ Board.cpp SubPieces.cpp Stack.cpp ChessMainFunction.cpp -o chess
````

Or open the `.sln` in Visual Studio and build.

### 2. Run

```bash
./chess
```

### 3. Enter moves

Format:

```
e2 e4
```

* First coordinate = piece to move
* Second coordinate = destination square

---

## Example Board Output

This is what the board looks like in your console (piece codes: `Rk`, `Kn`, `Bp`, `Qn`, `Kg`, `Pn`):

```
   a  b  c  d  e  f  g  h
8 |Rk|Kn|Bp|Qn|Kg|Bp|Kn|Rk|  8
  -------------------------
7 |Pn|Pn|Pn|Pn|Pn|Pn|Pn|Pn|  7
  -------------------------
6 |  |  |  |  |  |  |  |  |  6
  -------------------------
5 |  |  |  |  |  |  |  |  |  5
  -------------------------
4 |  |  |  |  |  |  |  |  |  4
  -------------------------
3 |  |  |  |  |  |  |  |  |  3
  -------------------------
2 |Pn|Pn|Pn|Pn|Pn|Pn|Pn|Pn|  2
  -------------------------
1 |Rk|Kn|Bp|Qn|Kg|Bp|Kn|Rk|  1
   a  b  c  d  e  f  g  h
```

---

##  Notes

* Uses `system("cls")` for clearing the console on Windows; change to `system("clear")` for Linux/macOS.
* The board constructor in `Board.cpp` currently has a **test setup** (few pieces only).
  Uncomment the full setup code for a standard chess starting position.
* The stack is **internal only** — not for player undo.

---

## 👤 Author

**Muhammad Basim Irfan**
Made to practice:

* C++ OOP design
* Game logic implementation
* Data structure usage in game rules
* Multi-file project structure

```
