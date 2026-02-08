#  Battleship Game

A classic **Battleship** game implementation in C++ with colorful console graphics for Windows. Challenge the computer in an exciting naval warfare strategy game!

##  Features

- **Player vs Computer Mode** - Strategic gameplay against AI opponent
- **Colorful Console Interface** - Enhanced visual experience with colored ships and hit/miss markers
- **Multiple Ship Placement Options**:
  - Manual placement (horizontal/vertical)
  - Random placement for quick setup
- **5 Different Ship Types**:
  - Aircraft Carrier (5 cells)
  - Battleship (4 cells)
  - Destroyer (3 cells)
  - Submarine (3 cells)
  - Patrol Boat (2 cells)
- **Dynamic Turn System** - Lose turns when ships are destroyed
- **Score Tracking** - Points awarded for hits, deducted for misses
- **Game Instructions** - Built-in help menu

##  Technologies Used

- **Language**: C++
- **Platform**: Windows (uses `windows.h` and `conio.h`)
- **Graphics**: Console-based with ANSI color codes

##  Prerequisites

- Windows Operating System
- C++ Compiler (MinGW, MSVC, or similar)
- Windows Console with color support

##  How to Play

1. **Start New Game** - Choose from the main menu
2. **Select Ship Color** - Customize your fleet's appearance (8 colors available)
3. **Place Your Ships** - Position all 5 ships on your board
   - Choose manual or random placement
   - For manual: select position and orientation
4. **Take Turns Attacking** - Enter coordinates to fire at enemy ships
5. **Win Condition** - Destroy all enemy ships before they destroy yours!

### Game Controls
- **Hit**: Marked with red `X`
- **Miss**: Marked with gray `O`
- **Water**: Displayed as blue `~`
- **Your Ships**: Displayed as colored `S`

##  Scoring System

- **Hit**: +10 points
- **Miss**: -1 point
- **Ship Destroyed**: Enemy loses 1 turn

##  Project Structure

```
battleship/
├── battleship.cpp          # Main game file
└── README.md              # Project documentation
```

##  Academic Project

This project was developed as a **Programming Fundamentals (PF) Final Project** to demonstrate:
- Object-oriented programming concepts
- Game logic implementation
- Input validation and error handling
- Console-based UI design
- Algorithm development (ship placement, attack validation)

##  Known Issues

- Player vs Player mode is currently under development
- Leaderboard feature not yet implemented

##  Future Enhancements

- [ ] Player vs Player mode
- [ ] Leaderboard system with persistent storage
- [ ] Difficulty levels for AI
- [ ] Sound effects
- [ ] Network multiplayer support
- [ ] Cross-platform compatibility

##  Author

Created as a university project for Programming Fundamentals course.
