# first-til-30-game

A multiplayer number-picking game where the first player to reach 30 points wins, written in C.

---

## About

Written in C, this project contains two versions of the same game. Each round, all players simultaneously pick a number between 1 and 10. A player only scores their chosen number if it is unique among all picks that round. The first player to reach or exceed 30 points wins. Version 2 adds a computer player ("Dator") that always picks 10 in the first round. The game uses Swedish-language prompts.

## Gameplay

1. Enter the number of players (max 8).
2. Enter all player names separated by spaces (max 6 characters each).
3. Each round, enter all players' number picks separated by spaces.
4. Duplicate picks score nothing; unique picks add to the player's score.
5. The game ends when at least one player reaches 30 points.

## Getting Started

### Prerequisites

- A C compiler (gcc or equivalent)

### Building

Version 1 (players only):

**Unix**
```
gcc -o first-til-30-game src/first-til-30-game-1.c
```

**Windows**
```
gcc -o first-til-30-game.exe src\first-til-30-game-1.c
```

Version 2 (with computer player):

**Unix**
```
gcc -o first-til-30-game-2 src/first-til-30-game-2.c
```

**Windows**
```
gcc -o first-til-30-game-2.exe src\first-til-30-game-2.c
```

### Running

**Unix**
```
./first-til-30-game
```

**Windows**
```
first-til-30-game.exe
```

## Configuration

| Constant | Default | Description |
|----------|---------|-------------|
| `MAX_PLAYER_COUNT` | 8 | Maximum number of human players |
| `MAX_PLAYER_NAME_LENGTH` | 7 | Maximum characters in a player name (including null terminator) |
| `LOWER_SCORE_BOUND` | 1 | Minimum pick value per round |
| `UPPER_SCORE_BOUND` | 10 | Maximum pick value per round |
| `GAME_WINNING_SCORE` | 30 | Score required to win |
| `COMPUTER_FIRST_POINT_CHOICE` | 10 | Computer's pick in round 1 (version 2 only) |

---

MIT License - see [LICENSE](LICENSE)
