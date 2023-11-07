#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void sieveOfEratosthenes(int n) {
    bool isPrime[n+1];
    memset(isPrime, true, sizeof(isPrime));

    printf("Prime numbers smaller than %d are: \n", n);
    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p] == true) {
            for (int i = p * p; i <= n; i += p)
                isPrime[i] = false;
        }
    }


    for (int p = 2; p <= n; p++) {
        if (isPrime[p])
            printf("%d ", p);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the upper bound: ");
    scanf("%d", &n);
    sieveOfEratosthenes(n);
    return 0;
}
