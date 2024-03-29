# Tic-Tac-Toe 

The program can be run in the command line from a settings file for an arbitrary number of rows, columns and win condition length. The game is run as Player 1 vs Player 2.

The program was initially created for my major assignment in COMP1000 Unix and C Programming at Curtin University, however I endeavored to go back and refactor the code with better programming practices.

## Usage 
```
git clone https://github.com/LDRyan0/Tic-Tac-Toe.git
cd Tic-Tac-Toe/
make
./TicTacToe settings.txt
```
## Compilation Flags
Compilation adhears to `-ansi`, `-pedantic`, `-Wall` and `-Werror` standards.

## Settings
The program can load settings from the `settings.txt` file, or the settings can be changed through the main menu after the program has loaded. The user can change `<m>` `<n>` and `<k>` - the amount of rows, columns as well as the amount of tokens in a row to win.

**settings.txt**
```
m=4
n=4
k=3
```
## Limitiations
`m`, `n` and `k` must be 1-26

## Logging
The program is able to generate log files to record the results of games. Log files are stamped with the number of rows, columns, win condition, time and date (e.g., `log/MNK_4_4_3_02:26_16-02.log`).
```
SETTINGS:
        M: 4
        N: 4
        K: 3

GAME 1:
        Turn: 1
        Player: X
        Location: 0,0

        Turn: 2
        Player: O
        Location: 1,0

        Turn: 3
        Player: X
        Location: 0,1

        Turn: 4
        Player: O
        Location: 1,1

        Turn: 5
        Player: X
        Location: 0,2

```

