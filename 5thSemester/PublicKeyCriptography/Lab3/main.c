#include <stdio.h>
#include <math.h>

void getFactors(int number, int *n1, int *n2)
{
    
    if(number < 7)
    {
        *n1 = 1;
        *n2 = number;
    }

    // parsing k's
    for(int k = 1; k <= number; k++){

        // get the formula
        float x = sqrt(number + k * k);
        int test = (int)x;

        // checking if x is an integer and assigning the difference of squares to the factors
        if(test == x){
            *n1 = x + k;
            *n2 = x - k;
            return;
        }
    }
}

int main() {
    int number, n1, n2;
    printf("Enter a number:");
    scanf("%d", &number);

    getFactors(number, &n1, &n2);

    printf("%d = %d * %d", number, n1, n2);

    return 0;
}
