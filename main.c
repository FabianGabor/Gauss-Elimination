#include <stdio.h>

void print_matrix(int *a, int *b, int n)
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
            printf("%8d", *(a + i*n + j ));
        printf("\t | %8d", *(b + i));
        printf("\n");
    }
    printf("\n");
}

int *swap(int *a, int *b, int n)
{
    for (int i=0; i<n; i++)
    {
        int tmp_val = *(a + i);
        *(a + i) = *(a + n + i);
        *(a + n + i) = tmp_val;

    }
    return a;
}

int main()
{
    int a[4][4] =
    {
        {0,2,5,1},
        {3,-4,3,-2},
        {4,3,2,-1},
        {1,-2,-4,-1}
    };
    int b[4] = {4,7,1,2};
    double x[4] = {0};

    int n = sizeof(b)/sizeof(b[0]);

    if (a[0][0] == 0) swap(*a,b,n);

    print_matrix(a, b, n);


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

    print_matrix(*a, b, n);

    for (int i=n-1; i>=0; i--)
    {
        int j;
        double sum = b[i];
        for (j=0; j<n; j++)
        {
            sum -= a[i][j] * x[j];
        }
        x[i] = sum / a[i][i];
    }

    for (int i=0; i<n; i++)
        printf("x%d = %7.3f\n", i+1, x[i]);

    return 0;
}
