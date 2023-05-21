#include <stdlib.h>
#include <stdio.h>

int hundreds(int x);

int main()
{
    int n, v[100], suta;
    printf("The number of numbers is :");
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        printf("The number labeled %d is", i);
        scanf("%d", v[i]);
        suta = hundreds(v[i]);
        v[i] = suta;
    }
    for (int i = 0; i < n; ++i)
        printf("Hundreds number %d is %d", i, v[i]);
    return 0;
}