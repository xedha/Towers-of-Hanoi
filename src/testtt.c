
#include <stdio.h>
#include "../include/hanoi_itterative.h"

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    hanoi_iterative(n);

    return 0;
}
