#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define GAME_DONE 0

#define MAX_PLAYER_COUNT 8
#define MAX_PLAYER_NAME_LENGTH 7
#define INPUT_STRING_LIMITATION 100
#define LOWER_SCORE_BOUND 1
#define UPPER_SCORE_BOUND 10
#define GAME_WINNING_SCORE 30

struct Player {
    char name[MAX_PLAYER_NAME_LENGTH];
    int score;
};

void printNewLine() {
    printf("\n");
}

void clearScanner() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clearArray(int array[], int arraySize) {
    for (int index = 0; index < arraySize; index++) {
        array[index] = 0;
    }
}

// output expected -> [x1, x2, x3, ...]
void printArray(int array[], int arraySize) {
    printf("[");

    for (int index = 0; index < arraySize; index++) {
        if (index == arraySize - 1) {
            printf("%d", array[index]);
        } else {
            printf("%d, ", array[index]);
        }
    }
    
    printf("]\n");
}

int getPlayerCountFromUserInput() {
    int playerCount = 0;

    printf("Antal spelare (max %d): ", MAX_PLAYER_COUNT);
    scanf("%d", &playerCount);

    return playerCount;
}

int isPlayerCountValid(int playerCount) {
    if (playerCount > MAX_PLAYER_COUNT) {
        printf("Antalet spelare kan inte vara mer än %d, antal spelare lagt %d\n", MAX_PLAYER_COUNT, playerCount);
        return FALSE;
    }

    return TRUE;
}

void getPlayersNameFromUser(char userStringInput[]) {
    printf("Ange allas namn: ");
    scanf("%100[^\r^\n]*c", userStringInput);
}

int processValidPlayersName(char userStringInput[], struct Player gamePlayers[], int playerCount) {
    int inputIndex = 0;

    for (int playerNr = 0; playerNr < playerCount; playerNr++) {
        struct Player playerInfomation = {"name", 0};

        int inputPlayerNameCounter = 0;

        while (inputIndex < INPUT_STRING_LIMITATION &&
            userStringInput[inputIndex] != '\0' &&
            userStringInput[inputIndex] != ' ') {

            inputIndex++;
            inputPlayerNameCounter++;
        }
        
        for (int indexinputPlayerNameCounter = 0; indexinputPlayerNameCounter < inputPlayerNameCounter; indexinputPlayerNameCounter++) {
            playerInfomation.name[indexinputPlayerNameCounter] = userStringInput[inputIndex - inputPlayerNameCounter + indexinputPlayerNameCounter];
        }

        if (inputPlayerNameCounter > MAX_PLAYER_NAME_LENGTH - 1) {
            printf("Namn är längre än max %d tecken, namnet inlagt: %s\n", MAX_PLAYER_NAME_LENGTH, playerInfomation.name);
            return FALSE;
        }

        gamePlayers[playerNr] = playerInfomation;
        inputIndex++;
    }

    return TRUE;
}

void printPlayersInfomation(struct Player gamePlayers[], int playerCount) {
    for (int playerNr = 0; playerNr < playerCount; playerNr++) {
        printf("%s %dp ", gamePlayers[playerNr].name, gamePlayers[playerNr].score);
    }

    printNewLine();
    printNewLine();
}

void getPlayersPointFromUser(char userStringInput[]) {
    printf("Ange allas val i korrekt ordning: ");
    scanf("%100[^\r^\n]*c", userStringInput);
}

int processValidPlayersPoint(char userStringInput[], int inputScore[], int playerCount) {
    int inputIndex = 0;

    for (int playerNr = 0; playerNr < playerCount; playerNr++) {
        char scoreString[3] = {0};
        int tempScore = 0;
        int inputPlayerNameCounter = 0;

        while (inputIndex < INPUT_STRING_LIMITATION &&
            userStringInput[inputIndex] != '\0' &&
            userStringInput[inputIndex] != ' ') {

            inputIndex++;
            inputPlayerNameCounter++;
        }
        
        for (int indexinputPlayerNameCounter = 0; indexinputPlayerNameCounter < inputPlayerNameCounter; indexinputPlayerNameCounter++) {
            scoreString[indexinputPlayerNameCounter] = userStringInput[inputIndex - inputPlayerNameCounter + indexinputPlayerNameCounter];
        }

        tempScore = atoi(scoreString);

        if (!(tempScore >= LOWER_SCORE_BOUND && tempScore <= UPPER_SCORE_BOUND)) {
            printf("Poäng skulle vara mellan [%d, %d], poängen inlagt: %d\n", 
                LOWER_SCORE_BOUND, 
                UPPER_SCORE_BOUND, 
                tempScore);

            return FALSE;
        }

        inputScore[playerNr] = tempScore;
        inputIndex++;
    }

    return TRUE;
}

void distributePointsBasedOnUniqueness(struct Player gamePlayers[], int inputScore[], int playerCount) {
    for (int scoreOuterIndex = 0; scoreOuterIndex < playerCount; scoreOuterIndex++) {
        int isUnique = 1;

        for (int scoreInnerIndex = 0; scoreInnerIndex < playerCount; scoreInnerIndex++) {
            if (scoreOuterIndex == scoreInnerIndex) {
                continue;
            }
            
            if (inputScore[scoreOuterIndex] == inputScore[scoreInnerIndex]) {
                isUnique = 0;
                break;
            }
        }

        if (isUnique == 1) {
            gamePlayers[scoreOuterIndex].score = gamePlayers[scoreOuterIndex].score + inputScore[scoreOuterIndex];
        }
    }
}

int checkWinningPlayers(struct Player gamePlayers[], int winningPlayers[], int playerCount) {
    int isEndGame = FALSE;

    for (int playerNr = 0; playerNr < playerCount; playerNr++) {
        
        if(gamePlayers[playerNr].score >= GAME_WINNING_SCORE) {
            isEndGame = TRUE;
            winningPlayers[playerNr] = 1;
        }

    }
    
    return isEndGame;
}
 
void printWinnerPlayers(struct Player gamePlayers[], int winningPlayers[], int playerCount) {
    printf("Vinnare: ");

    for (int playerNr = 0; playerNr < playerCount; playerNr++) {
        
        if (winningPlayers[playerNr] == 1) {
            printf("%s ", gamePlayers[playerNr].name);
        }

    }

    printNewLine();
}

int main() {
    int playerCount = 0;
    char userStringInput[INPUT_STRING_LIMITATION] = {0};
    struct Player gamePlayers[MAX_PLAYER_COUNT];
    int inputScore[MAX_PLAYER_COUNT] = {0};
    int winningPlayers[MAX_PLAYER_COUNT] = {0};

    playerCount = getPlayerCountFromUserInput();

    clearScanner();

    if (!isPlayerCountValid(playerCount)) {
        return FALSE;
    }
    
    getPlayersNameFromUser(userStringInput);

    clearScanner();
    
    printNewLine();
    
    int isPlayersNameValid = processValidPlayersName(userStringInput, gamePlayers, playerCount);
    
    if (!isPlayersNameValid) {
        return FALSE;
    }
    
    printPlayersInfomation(gamePlayers, playerCount);

    // Loop forever until somebody reaches 30 points.
    while (1) {
        getPlayersPointFromUser(userStringInput);
        
        clearScanner();

        printNewLine();

        int isPlayersPointValid = processValidPlayersPoint(userStringInput, inputScore, playerCount);

        if (!isPlayersPointValid) {
            return FALSE;
        }
        
        distributePointsBasedOnUniqueness(gamePlayers, inputScore, playerCount);

        printPlayersInfomation(gamePlayers, playerCount);

        int isEndGame = checkWinningPlayers(gamePlayers, inputScore, playerCount);

        if (isEndGame) {
            printWinnerPlayers(gamePlayers, inputScore, playerCount);
            return GAME_DONE;
        }
        
    }
    
    return 0;
}