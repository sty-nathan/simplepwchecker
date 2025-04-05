// Developed by sty-nathan (https://github.com/sty-nathan)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// * Displays a banner when the program starts
void printBanner() {
    printf("Simple password checker\n");
    printf("\033[1;33m# By: sty-nathan\033[0m\n");
}

// * Gets user input from the terminal.
char* getUserInput() {
    static char password[2048];

    printf("\nPassword > ");

    // Read line from standard input
    if (fgets(password, sizeof(password), stdin) == NULL) {
        exit(EXIT_FAILURE);
    }

    // Remove newline character if present
    password[strcspn(password, "\n")] = '\0';

    // ! Exit if input is empty (user just pressed Enter)
    if (strlen(password) == 0) {
        exit(EXIT_SUCCESS);
    }

    return password; // * Returns a pointer to a static buffer containing the password.
}

// * Evaluates the strength of the password
int evaluatePasswordStrength(const char* password) {
    int score = 0;
    size_t length = strlen(password);

    // Base score: +1 for every 8 characters
    score = length / 8;

    // ! Penalty if password is shorter than 8 characters
    if (length < 8) {
        score--;
    }

    int baseScore = score;

    int hasUpper = 0;
    int hasDigit = 0;
    int hasSpecial = 0;

    // Check for character diversity (uppercase, digit, special)
    for (int i = 0; password[i] != '\0'; i++) {
        char ch = password[i];

        if (isupper(ch) && !hasUpper) {
            score++;
            hasUpper = 1;
        } else if (isdigit(ch) && !hasDigit) {
            score++;
            hasDigit = 1;
        } else if (!isalpha(ch) && !isdigit(ch) && !hasSpecial) {
            score++;
            hasSpecial = 1;
        }

        // Exit early if all three types are found
        if ((score - baseScore) == 3) {
            break;
        }
    }

    return score; // * Returns an integer score based on length and character variety
}

int main() {
    printBanner();

    char* password = getUserInput();
    int score = evaluatePasswordStrength(password);

    printf("\nPassword level: ");

    // * Print password level with ANSI color
    if (score < 3) {
        printf("\033[0;30mWeak"); // * Level 1
    } else if (score == 3) {
        printf("\033[0;33mMedium"); // ? Level 2
    } else if (score >= 4) {
        printf("\033[1;31mStrong"); // ! Level 3
    }

    printf("\n\033[0mYour score: %d\n", score);

    return 0;
}
