#include <stdio.h>
#include <stdbool.h>
#include <string.h>


void sieveOfEratosthenes(int n) {
    // initialising the table with true values
    bool isPrime[n+1];
    memset(isPrime, true, sizeof(isPrime));

    // parsing the table with p*p because i only need the numbers smaller than n
    // it will check if the index is set to true if it is then every multiple of that index is set to false
    // starting with 2 as 2 is the smallest prime
    printf("Prime numbers smaller than %d are: \n", n);
    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p] == true) {
            for (int i = p * p; i <= n; i += p)
                isPrime[i] = false;
        }
    }

    // printing all true values from the table
    for (int p = 2; p <= n; p++) {
        if (isPrime[p])
            printf("%d ", p);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the upper bound:");
    scanf("%d", &n);
    sieveOfEratosthenes(n);
    return 0;
}
