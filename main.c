#include <stdio.h>
#include <time.h>
long long moveCount = 0;
int maxDepth = 0;

void Hanoi(int n, char A, char C, char B, int depth) {
    if (n != 0) {
        if (depth > maxDepth) maxDepth = depth;
        Hanoi(n - 1, A, B, C, depth + 1);
        moveCount++;
        Hanoi(n - 1, B, C, A, depth + 1);
    }
}

int main() {
    int n;
    char continuer;
    clock_t start, end;
    double time_ms;

    printf("=== TOURS DE HANOI - VERSION RECURSIVE ===\n\n");

    do {
        printf("\nEntrez le nombre de disques (n) : ");
        if (scanf("%d", &n) != 1 || n <= 0) {
            printf("Erreur : Veuillez entrer un nombre entier positif.\n");
            while(getchar() != '\n');
            continue;
        }
        moveCount = 0;
        maxDepth = 0;

        start = clock();
        Hanoi(n, 'A', 'C', 'B', 1);
        end = clock();

        time_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

        printf("\n--- RESULTATS POUR N = %d ---\n", n);
        printf("Nombre de mouvements : %lld\n", moveCount);
        printf("Temps d'execution    : %.3f ms\n", time_ms);
        printf("Time Complexity      : O(2^n)\n");
        printf("Space Complexity     : O(%d) (Profondeur de pile)\n", maxDepth);

        printf("\nVoulez-vous tester une autre valeur ? (o/n) : ");
        scanf(" %c", &continuer);
    } while (continuer == 'o' || continuer == 'O');

    printf("\nFIN\n");
    return 0;
}
