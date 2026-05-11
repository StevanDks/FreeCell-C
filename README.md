# FreeCell-C

A terminal-based FreeCell card game implemented in C using linked lists and pointers. This project documents the learning journey from a buggy first version to a working, improved implementation.

---

## How It Works

The game generates and shuffles a standard 52-card deck, distributes them across 8 table piles, and allows the player to move cards between piles following FreeCell rules.

**Game areas:**
- **Mesa (0-7):** 8 table piles where cards are distributed
- **Temp (0-3):** 4 free cells to temporarily store single cards
- **Naipe (0-3):** 4 foundation piles, one per suit, built from Ace to King

---

## Features

- Deck generation and shuffling using linked lists
- Card distribution across 8 table piles
- 7 move types:
  - Mesa → Naipe
  - Mesa → Temp
  - Temp → Mesa
  - Naipe → Temp
  - Temp → Naipe
  - Naipe → Mesa
  - Mesa → Mesa (sequence moves)
- Sequence validation for multi-card moves
- Unicode suit symbols (♥ ♦ ♣ ♠)
- Windows MinGW support with UTF-8 console output
- Memory cleanup on exit

---

## Version History

### v1.0 — Initial Version (buggy)
The first version was written as a learning exercise in C pointers and linked lists. It had the following known bugs:

- **Suit display bug:** suits were displayed as raw integer values (`3, 4, 5, 6`) instead of proper symbols, since `char` was used to print them via `%c` — which printed garbage characters on modern MinGW compilers
- **Pointer crash in `moveMesaMesa()`:** when moving card sequences between table piles, the pointer traversal lost track of the correct node, causing a null pointer dereference and crashing the program
- **Missing null check in `moveNaipeMesa()`:** the function assumed `primMesa[posMesa]` was never empty, causing undefined behavior when moving to an empty pile

### v2.0 — Fixed Version
Bugs fixed and improvements made with the help of Claude Code:

- ✅ **Unicode suit symbols:** added `naipeStr()` function returning proper UTF-8 strings (♥ ♦ ♣ ♠) instead of raw `char` values
- ✅ **Windows UTF-8 support:** added `#ifdef _WIN32` with `SetConsoleOutputCP(CP_UTF8)` so symbols render correctly on MinGW/Windows Terminal
- ✅ **Pointer bug in `moveMesaMesa()`:** fixed the node traversal logic to correctly track the predecessor pointer before detaching the sequence
- ✅ **Null check in `moveNaipeMesa()`:** added proper handling for the case where the destination pile is empty

---

## How to Run

**Compile:**
```bash
gcc freecell.c -o freecell
```

**Run:**
```bash
./freecell
```

---

## Tech Stack

- **Language:** C
- **Concepts:** Linked lists, pointers, dynamic memory allocation (`malloc`/`free`), structs, finite state machine (game loop)

---

## License

This project is licensed under the [MIT License](LICENSE).
