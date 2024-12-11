#include <stdio.h>
int count = 0;
void hanoi(int N, char from, char transitional, char to) {
    if(N == 1) count++; // How many time I move?
    else {
        hanoi(N-1, from, to, transitional); // Move from the 1st to the (N-1)-th discs from the left rod to the middle rod.
        hanoi(1, from, transitional, to); // Move N-th disc from the left rod to the right rod.
        hanoi(N-1, transitional, from, to); // Move from the 1st to the (N-1)-th discs from the middle rod to the right rod.
    }
}

int main() {
    int N;
    scanf("%d", &N);
    hanoi(N, 'A', 'B', 'C');
    printf("%d\n", count);
    count = 0;
    return 0;
} 
