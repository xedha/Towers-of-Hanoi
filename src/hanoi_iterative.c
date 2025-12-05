#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include "../include/hanoi_itterative.h"
#include "../include/utils.h"

typedef unsigned long long ull;

// Struct (Chghoul Record) for the stack
typedef struct {
    int *arr;
    int top;
} Peg;

// The functions we need for the stack record 
static void push(Peg *p, int disk) { p->arr[++p->top] = disk; }
static int pop_disk(Peg *p) { return p->arr[p->top--]; }
static int peek(Peg *p) { return p->top == -1 ? INT_MAX : p->arr[p->top]; }
static int empty(Peg *p) { return p->top == -1; }

static void move_disk(Peg *from, Peg *to) {
    int d = pop_disk(from);
    push(to, d);
}

// Do the only legal move between p1 and p2, so move the sameller disk
static void legal_move(Peg *p1, Peg *p2) {
    int t1 = peek(p1);
    int t2 = peek(p2);

    if (t1 < t2) move_disk(p1, p2);
    else         move_disk(p2, p1);
}

// ------- MAIN ITERATIVE HANOI FUNCTION -------
void hanoi_iterative(int n)
{
    if (n <= 0) {
        printf("Invalid n\n");
        return;
    }

    // timing
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    ull total_moves = ((ull)1 << n) - 1;

    // pegs
    Peg A, B, C;
    A.arr = malloc(n * sizeof(int)); A.top = -1;
    B.arr = malloc(n * sizeof(int)); B.top = -1;
    C.arr = malloc(n * sizeof(int)); C.top = -1;

    for (int d = n; d >= 1; --d)
        push(&A, d);

    Peg *pegs[3] = { &A, &B, &C };
    int cycle[3] = {0, 1, 2};

    // parity logic
    // if n is even the cycle : A->C->B
    // so here we swap 1 and 2 (houma B and C)
    if (n % 2 == 0) {
        cycle[1] = 2;
        cycle[2] = 1;
    }

    // if n is not even, so odd the cycle is : A->B->C
    // we keep it as it is

    int pos_small = 0;  // smallest disk starts on peg A

    // MAIN LOOP
    for (ull move = 1; move <= total_moves; ++move) {
        if (move % 2 == 1) { // Odd - Impaire
            // smallest disk move
            int idx = -1;
            for (int i = 0; i < 3; ++i)
                if (cycle[i] == pos_small) { idx = i; break; } // we get the index(Peg) of the smallest disk

            int next = cycle[(idx + 1) % 3]; // we get the next Peg for the smallest disk based on where he is (index - idx) so along the cycle A-B-C
            move_disk(pegs[pos_small], pegs[next]); // pops the smallest disk from its current peg and pushes it onto the destination peg
            pos_small = next; // Updates where the smallest disk is now
        }
        else { // Even - Paire
            // legal move between other 2 pegs
            int p = -1, q = -1; // the one that does not contain the smallest disk
            for (int i = 0; i < 3; ++i) { // it stores them here (with i)
                if (i == pos_small) 
                continue;
                if (p == -1) 
                p = i;
                else q = i;
            }
            legal_move(pegs[p], pegs[q]); // This function therefore performs the unique legal move between those two pegs.
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec) 
                + (end.tv_nsec - start.tv_nsec) / 1e9;

    // ----------------------- RESULTS -------------------------
    printf("\n========== ITERATIVE HANOI ==========\n");
    printf("n = %d\n", n);
    printf("Total moves = %llu\n", total_moves);
    printf("Execution time = %.6f seconds\n", elapsed);
    printf("=====================================\n\n");

    // free memory
    free(A.arr);
    free(B.arr);
    free(C.arr);
}
