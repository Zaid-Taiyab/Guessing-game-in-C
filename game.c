#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Struct to store player information
struct Player {
    char firstName[50];
    char lastName[50];
    int guesses;
};

// Function to update and display the leaderboard
void updateLeaderboard(struct Player leaderboard[], int *numPlayers, struct Player currentPlayer) {
    int i;

    // Check if the player is already in the leaderboard
    int playerIndex = -1;
    char playerName[100];
    sprintf(playerName, "%s %s", currentPlayer.firstName, currentPlayer.lastName);

    for (i = 0; i < *numPlayers; i++) {
        char existingName[100];
        sprintf(existingName, "%s %s", leaderboard[i].firstName, leaderboard[i].lastName);

        if (strcmp(playerName, existingName) == 0) {
            playerIndex = i;
            break;
        }
    }

    if (playerIndex == -1) {
        // Player not found, add them to the leaderboard
        leaderboard[*numPlayers] = currentPlayer;
        (*numPlayers)++;
    } else {
        // Player found, update their entry if they have fewer guesses
        if (currentPlayer.guesses < leaderboard[playerIndex].guesses) {
            leaderboard[playerIndex] = currentPlayer;
        }
    }

    // Sort the leaderboard based on the number of guesses (ascending order)
    for (i = 0; i < *numPlayers; i++) {
        for (int j = i + 1; j < *numPlayers; j++) {
            if (leaderboard[i].guesses > leaderboard[j].guesses) {
                // Swap the players
                struct Player temp = leaderboard[i];
                leaderboard[i] = leaderboard[j];
                leaderboard[j] = temp;
            }
        }
    }

    // Display the top 5 players
    printf("Here are the current leaders:\n");
    for (i = 0; i < *numPlayers && i < 5; i++) {
        printf("%s %s made %d guesses\n", leaderboard[i].firstName, leaderboard[i].lastName, leaderboard[i].guesses);
    }
}

int main() {
    char input1;
    int input2;
    struct Player leaderboard[5];
    int numPlayers = 0;

    // Load leaderboard from file (if it exists)
    FILE *file = fopen("leaderboard.txt", "r");
    if (file != NULL) {
        while (fread(&leaderboard[numPlayers], sizeof(struct Player), 1, file) == 1 && numPlayers < 5) {
            numPlayers++;
        }
        fclose(file);
    }

    while (1) {
        printf("Welcome! Press 'q' to quit or any other key to continue:\n");
        scanf(" %c", &input1);

        if (input1 == 'q' || input1 == 'Q') {
            printf("Bye Bye!\n");
            break;
        } else {
            struct Player currentPlayer;
            printf("Please enter your first name: ");
            scanf("%s", currentPlayer.firstName);

            printf("Please enter your last name: ");
            scanf("%s", currentPlayer.lastName);

            currentPlayer.guesses = 0;

            // Generate a new random number for each game
            double number = (double)(rand() % 91) + 10;
            double square_root = sqrt(number);

            while (1) {
                printf("%.8f is the square root of what number?\nGuess a value between 10 and 100: ", square_root);
                scanf("%d", &input2);
                currentPlayer.guesses++;

                if (number > input2) {
                    printf("Too low, guess again: ");
                } else if (number < input2) {
                    printf("Too high, guess again: ");
                } else {
                    printf("You got it, baby!\n");
                    break;
                }
            }

            // Update and display the leaderboard
            updateLeaderboard(leaderboard, &numPlayers, currentPlayer);
        }
    }

    // Save the updated leaderboard to a file
    file = fopen("leaderboard.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < numPlayers; i++) {
            fwrite(&leaderboard[i], sizeof(struct Player), 1, file);
        }
        fclose(file);
    }

    return 0;
}

