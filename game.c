//
// Created by zaidt on 9/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    char input1;
    int input2;
    double number;

    number = (double)(rand() % 91) + 10;

    printf("Welcome! Press q to quit or any key to continue:\n");
    scanf(" %c", &input1);

    if (input1 == 'q' || input1 == 'Q') {
        printf("Bye Bye!\n");
        return 0;
    } else {
        double square_root = sqrt(number);

        while (input2 != (int)number) {
            printf("%f is the square root of what number?\n", square_root);
            scanf("%d", &input2);

            if (number > input2) {
                printf("Too low, guess again: ");
            } else if (number < input2) {
                printf("Too high, guess again: ");
            }
        }

        if ((int)number == input2) {
            printf("Correct: you got it baby!\n");
            return 0;
        }
    }

    return 0;
