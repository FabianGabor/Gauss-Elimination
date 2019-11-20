#include <stdio.h>

void print_matrix(int *a, int *b, int n)
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
            printf("%4d", *(a + i*n + j ));
        printf("%4d", *(b + i));
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int a[3][3] =
    {
        {1,2,1},
        {2,1,-1},
        {2,-1,1}
    };
    int b[3] = {8,1,3};
    int x[3] = {0};

    print_matrix(*a, b, 3);

    int n=3;
    for (int k=0; k<n-1; k++)
    {
        for (int i=k+1; i<n; i++)
        {
            int mult = a[i][k];
            int lead = a[k][k];

            b[i] *= lead;
            b[i] -= mult * b[k];

            for (int j=k; j<n; j++)
            {
                a[i][j] *= lead;
                a[i][j] -= mult * a[k][j];
            }
        }
    }

    print_matrix(*a, b, 3);

    for (int i=n-1; i>=0; i--)
    {
        int j;
        int sum = b[i];
        for (j=0; j<n; j++)
        {
            sum -= a[i][j] * x[j];
        }
        x[i] = sum / a[i][i];
        printf("x[%d] = %d\n", i, x[i]);
    }

    return 0;
}
