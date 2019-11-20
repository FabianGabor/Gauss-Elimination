#include <stdio.h>

void print_matrix(double *a, int n)
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
            printf("%5.1f", *(a + i*n + j ));
        printf("\n");
    }
    printf("\n");
}

int main()
{
    double a[3][3] =
    {
        /*
        {1,2,1},
        {2,1,-1},
        {2,-1,1}
            */
        {1,5,-2},
        {2,3,1},
        {2,4,-3}
    };
    int b[3] = {8,1,3};

    print_matrix(*a,3);

    int n=3;
    for (int k=0; k<n-1; k++)
    {
        for (int i=k+1; i<n; i++)
        {
            double mult = a[i][k];
            double lead = a[k][k];
            for (int j=k; j<n; j++)
            {
                a[i][j] *= lead;
                a[i][j] -= mult * a[k][j];
            }
        }
    }

    print_matrix(*a,3);

    return 0;
}
