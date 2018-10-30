#include <stdio.h>

int main()
{
    int arr[1000]; // for solving online problem, don't do this in production code :D
    int n, r, tmp;
    int i;

    while (scanf("%d %d", &n, &r) == 2)
    {
        for (i = 0; i < n; ++i) arr[i] = 1; // init :D
        for (i = 0; i < r; ++i)
        {
            scanf("%d", &tmp);
            arr[tmp - 1] = 0; // tmp should less then r
        }
        if (n != r)
        {
            for (i = 0; i < n; ++i)
                if (arr[i])
                    printf("%d ", i + 1);
        }
        else printf("*");
        printf("\n");
    }

    return 0;
}
