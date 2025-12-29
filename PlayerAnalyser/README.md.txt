# ICC Player Analysis System
C Mini Project – Team & Player Performance Analysis

This project is a **menu-driven C program** that lets users analyze ICC teams and players using a structured dataset of 50 realistic international players. Each player has a role, team name, and performance index (PI).

## Files Included
- `main.c` – Program logic with menu, search, filter, sort, and display functions
- `players_data.h` – Player structure and dataset of 50 ICC players
- `README.md` – Project documentation

## Features
1. **Display Players of a Team** – Shows all players in a specific ICC team.
2. **Average Strike Rate of Batters** – Uses PI as a strike-rate substitute (Batter, All-Rounder, WK-Batter).
3. **Top-K Players of a Team (By Role)** – Sorts players by PI in descending order.
4. **Display All Players of a Role Across Teams** – Globally sorted list by PI for each role.

## Data Structure
```c
typedef struct {
    char name[50];
    char role[20];
    char teamName[20];
    int performanceIndex;
} Player;
```

## Compilation
Use GCC to compile:
```bash
gcc main.c -o icc_analyzer
```

## Running the Program
```bash
./icc_analyzer
```

## Program Menu
1. Display Players of a Team  
2. Display Average Strike Rate of Batters in a Team  
3. Display Top-K Players of a Team (by Role)  
4. Display All Players of a Role Across Teams (Global Sort)  
5. Exit  

### Input Examples
- **Team Names:** India, Australia, England, South Africa  
- **Roles:** Batter, Bowler, All-Rounder, WK-Batter  
- **K Value:** 3  

## Why This Project Meets Requirements
- Uses **structs and arrays** correctly  
- Includes **50 realistic ICC players**  
- Fully **menu-driven** and user-friendly  
- Implements **sorting & filtering**  
- All functionalities match the problem statement  
- Players stored outside `main.c` (good modular design)