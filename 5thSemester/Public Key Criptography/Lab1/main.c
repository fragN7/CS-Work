#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Normal subtraction
int gcdSubtraction(int a, int b) {

    if(a == 0)
        return b;

    while (a != b) {
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }
    return a;
}

// Normal division
int gcdDivision(int a, int b) {
    if (a == 0){
        return b;
    }
    if (b == 0) {
        return a;
    }

    while(b != 0){
        int r = a % b;
        a = b;
        b = r;
    }

    return a;
}

// Normal
int gcdBasic(int a, int b){

    if(a == 0)
        return b;

    int min = 0;
    if(a < b){
        min = a;
    } else {
        min = b;
    }

    if(a % min == 0 && b % min == 0){
        return min;
    }

    int i = min / 2;
    while(i > 2){
        if(a % i == 0 && b % i == 0){
            return i;
        }
        i = i - 1;
    }
    return 1;
}

int main() {
    srand(time(NULL));
    struct timespec start, end;
    double cpu_time_used;

    long long int pairs[20][2] = {
            {0, 5},
            {2 * 13, 3 * 13},
            {2 * 17, 3 * 17},
            {2 * 19, 3 * 19},
            {2 * 23, 3 * 23},
            {2 * 29, 3 * 29},
            {2 * 31, 3 * 31},
            {2 * 37, 3 * 37},
            {2 * 41, 3 * 41},
            {2 * 43, 3 * 43},
            {2 * 47, 3 * 47},
            {2 * 53, 3 * 53},
            {2 * 59, 3 * 59},
            {8 * 61, 9 * 61},
            {187877, 321321},
            {312312, 883213},
            {412421, 421414},
            {321313, 999999},
            {321311, 493213},
            {124143, 431266}
    };

    printf("Comparative Analysis of GCD Algorithms\n");

    for (int i = 0; i < 10; i++) {
        int index = rand() % 20;

        int a = pairs[index][0];
        int b = pairs[index][1];

        clock_gettime(CLOCK_REALTIME, &start);
        int result1 = gcdSubtraction(a, b);
        clock_gettime(CLOCK_REALTIME, &end);
        cpu_time_used = (end.tv_sec - start.tv_sec) + (double) (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        printf("GCD of %d and %d using normal subtraction algorithm is %d. Time taken: %.9f seconds\n", a, b, result1, cpu_time_used);

        clock_gettime(CLOCK_REALTIME, &start);
        int result2 = gcdDivision(a, b);
        clock_gettime(CLOCK_REALTIME, &end);
        cpu_time_used = (end.tv_sec - start.tv_sec) + (double) (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        printf("GCD of %d and %d using normal division algorithm is %d. Time taken: %.9f seconds\n", a, b, result2, cpu_time_used);

        clock_gettime(CLOCK_REALTIME, &start);
        int result3 = gcdBasic(a, b);
        clock_gettime(CLOCK_REALTIME, &end);
        cpu_time_used = (end.tv_sec - start.tv_sec) + (double) (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        printf("GCD of %d and %d using basic algorithm is %d. Time taken: %.9f seconds\n", a, b, result3, cpu_time_used);

        printf("\n\n");
    }

    return 0;
}