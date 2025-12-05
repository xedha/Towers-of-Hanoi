#include <stdio.h>
#include <time.h>
#include <math.h>
#include "../include/hanoi_recursive.h"
#include "../include/utils.h"

typedef unsigned long long ull;

static void hanoi_recursive_solver(int n,
                                   char from,
                                   char to,
                                   char aux,
                                   int depth,
                                   ull *moveCount,
                                   int *maxDepth)
{
    if (n == 0)
        return;

    if (depth > *maxDepth)
        *maxDepth = depth;

    hanoi_recursive_solver(n - 1, from, aux, to, depth + 1, moveCount, maxDepth);
    (*moveCount)++;
    hanoi_recursive_solver(n - 1, aux, to, from, depth + 1, moveCount, maxDepth);
}

void hanoi_recursive(int n)
{
    if (n <= 0) {
        printf("Invalid n\n");
        return;
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    ull moveCount = 0;
    int maxDepth = 0;

    hanoi_recursive_solver(n, 'A', 'C', 'B', 1, &moveCount, &maxDepth);

   clock_gettime(CLOCK_MONOTONIC, &end);

double elapsed_ms =
    (end.tv_sec - start.tv_sec) * 1000.0 +
    (end.tv_nsec - start.tv_nsec) / 1e6;

ull total_moves_theoretical = ((ull)1 << n) - 1;

    printf("\n========== RECURSIVE HANOI ==========\n");
    printf("n = %d\n", n);
    printf("Total moves (theoretical) = %llu\n", total_moves_theoretical);
    printf("Total moves (performed)   = %llu\n", moveCount);
    printf("Max recursion depth       = %d\n", maxDepth);
    printf("Execution time            = %.3f ms\n", elapsed_ms);
    printf("=====================================\n\n");
}