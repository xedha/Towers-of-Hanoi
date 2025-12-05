#include <stdio.h>
#include "../include/hanoi_itterative.h"
#include "../include/hanoi_recursive.h"


static void clear_input_buffer(void) // hada to avoid any double enter erros, and the thing where it skips the input prompt
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
       
    }
}
// --------- hna yebda el sah
static int ask_number_of_disks(void)
{
    int n;
    while (1) {
        printf("\nEnter number of disks N (>= 1): ");
        if (scanf("%d", &n) == 1 && n >= 1) {
            clear_input_buffer();
            return n;
        }

        printf("Invalid input. Please enter a positive integer.\n");
        clear_input_buffer();
    }
}

static int ask_algorithm_choice(void)
{
    int choice;

    printf("\nChoose how you want to solve the puzzle:\n");
    printf("  1. Iterative algorithm only\n");
    printf("  2. Recursive algorithm only\n");
    printf("  3. Both algorithms (display both algos results)\n");
    printf("  0. Exit\n");

    while (1) {
        printf("Your choice: ");
        if (scanf("%d", &choice) == 1 && choice >= 0 && choice <= 3) {
            clear_input_buffer();
            return choice;
        }

        printf("Invalid choice. Please enter 0, 1, 2, or 3.\n");
        clear_input_buffer();
    }
}

static int ask_retry(void)
{
    char answer;

    while (1) {
        printf("\nDo you want to try again with another N? (y/n): ");
        if (scanf(" %c", &answer) == 1) {
            clear_input_buffer();

            if (answer == 'y' || answer == 'Y')
                return 1;
            if (answer == 'n' || answer == 'N')
                return 0;
        }

        printf("Please answer with 'y' or 'n'.\n");
    }
}

/* --- le main ---------------------------------------------------------------- */

int main(void)
{
    int running = 1;

    /* Welcome / intro */
    printf("=============================================\n");
    printf("        Tower of Hanoi – C Project\n");
    printf("=============================================\n\n");
    printf("Welcome to the Tower of Hanoi analytical project!\n\n");
    printf("Puzzle description:\n");
    printf("We have three towers, with the first tower having N number");
    printf(" of disks, stacked so that a smaller disk is always on top of");
    printf(" a bigger disk.\n The goal is to move all the disks from Tower 1 ");
    printf("to Tower 3, using Tower 2 as auxiliary.\n\n");
    printf("Rules:\n");
    printf("  - You can move only one disk at a time.\n");
    printf("  - You may never place a larger disk on top of a smaller one.\n\n");
    printf("This program will display analytical data on how two algorithms\n");
    printf("solve this puzzle: an iterative version and a recursive version.\n");

    while (running) {
        int n = ask_number_of_disks();
        int choice = ask_algorithm_choice();

        if (choice == 0) {
            printf("\nExiting program. Goodbye!\n");
            break;
        }

        printf("\n=============================================\n");
        printf("  Solving Tower of Hanoi for N = %d disks\n", n);
        printf("=============================================\n\n");

        switch (choice) {
            case 1:
                printf("[Iterative algorithm]\n");
                hanoi_iterative(n);
                break;

            case 2:
                printf("[Recursive algorithm]\n");
                hanoi_recursive(n);
                break;

            case 3:
                printf("[Iterative algorithm]\n");
                hanoi_iterative(n);
                printf("\n---------------------------------------------\n");
                printf("[Recursive algorithm]\n");
                hanoi_recursive(n);
                break;

            default:
                break;
        }

        
        if (!ask_retry()) {
            printf("\nThank you for using the Tower of Hanoi analyzer. Bye!\n");
            running = 0;
        }
    }

    return 0;
}