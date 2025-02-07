//
//  main.cpp
//  test
//
//  Created by 신예준 on 2/28/25.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int secretNumber, guess, attempts = 0;
    
    // Seed the random number generator
    srand(time(NULL));
    secretNumber = rand() % 100 + 1; // Random number between 1 and 100
    
    printf("1부터 100까지의 숫자를 맞춰보세요!\n");
    
    do {
        printf("숫자를 입력하세요: ");
        scanf("%d", &guess);
        attempts++;
        
        if (guess > secretNumber) {
            printf("Too big!\n");
        } else if (guess < secretNumber) {
            printf("Too small!\n");
        } else {
            printf("Correct! You have got it correct in %d attempts!\n", attempts);
        }
    } while (guess != secretNumber);
    
    return 0;
}

