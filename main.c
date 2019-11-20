#include <stdio.h>

void print_matrix(int *a, int n)
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
            printf("%3d", *(a + i*n + j ));
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

    print_matrix(*a,3);

    for (int i=1; i<3; i++)
    {
        int mult[2] = {a[0][0],a[i][0]};
        for (int j=0; j<3; j++)
        {
            a[i][j] = a[i][j] * mult[0] - a[0][j] * mult[1];
        }
    }

    print_matrix(*a,3);



    return 0;
}
