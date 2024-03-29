#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

void print_matrix_double(double *a, double *b, int n)
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
            printf("%12.3f", *(a + i*n + j ));
        printf("\t | %12.3f", *(b + i));
        printf("\n");
    }
    printf("\n");
}

int *swap(int *a, int *b, int n)
{
    for (int i=0; i<n; i++)
    {
        int tmp = *(a + i);
        *(a + i) = *(a + n + i);
        *(a + n + i) = tmp;
    }
    int tmp = *b;
    *b = *(b+1);
    *(b+1) = tmp;

    return NULL;
}

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int findGCD(int *a, int *b, int row, int n)
{
    int result = *(a+n*row);
    for (int i = 1; i < n; i++)
            result = gcd(*(a+i+n*row), result);
    return gcd(result, *(b+row));
}

int *parseStr(char str[255])
{
    int i=0;
    static int data[10] = {0};
    char plus[2] = "+";
    char equal[2] = "=";
    char *ptr;

    ptr = strtok(str, equal);   // kezdjük az egyenlőségjel két oldalával
    ptr = strtok(NULL, equal);  // ugorjunk át az elválasztó karakter (equal) másik oldalára
    data[i] = round(atof(ptr));        // data[0] az egyenlőség jobb oldala
    i++;

    ptr = strtok(str, plus);
    while (ptr != NULL)
    {
        data[i] = round(atof(ptr));    // data[1–x] az együtthatók
        i++;
        ptr = strtok(NULL, plus);
    }

    return data;
}

double *parseStrDouble(char str[255])
{
    int i=0;
    static double data[10] = {0};
    char plus[2] = "+";
    char equal[2] = "=";
    char *ptr;

    ptr = strtok(str, equal);   // kezdjük az egyenlőségjel két oldalával
    ptr = strtok(NULL, equal);  // ugorjunk át az elválasztó karakter (equal) másik oldalára
    data[i] = atof(ptr);        // data[0] az egyenlőség jobb oldala
    i++;

    ptr = strtok(str, plus);
    while (ptr != NULL)
    {
        data[i] = atof(ptr);    // data[1–x] az együtthatók
        i++;
        ptr = strtok(NULL, plus);
    }

    return data;
}

void buildArray (int *target_a, int *target_b, int *source, int row, int n)
{
    *(target_b + row) = *source; // b matrix row sora = parseStr(er[i].egyenlet) első eleme

    for (int i=0; i<n; i++)
        *(target_a + i + row*n) = *(source + i +1);
}

void buildArrayDouble (double *target_a, double *target_b, double *source, int row, int n)
{
    *(target_b + row) = *source; // b matrix row sora = parseStr(er[i].egyenlet) első eleme

    for (int i=0; i<n; i++)
        *(target_a + i + row*n) = *(source + i +1);
}

int main()
{    

    int n = 4;
    /*
    int a[4][4] =
    {
        {1,2,5,1},
        {3,-4,3,-2},
        {4,3,2,-1},
        {1,-2,-4,-1}
    };
    int b[4] = {4,7,1,2};
    */

    /*
    double a_double[4][4] =
    {
        {1.41,      2.4,       5,     1.4},
        {3.1415,   -4.2,     3.7,      -2},
        {4.99,   3.1415,    2.01,   -1.01},
        {1,          -2,  -4.891,      -1}
    };
    double b_double[4] = {4.2,7.8,1.1,2.54};
    double x[5] = {0};
    */

    char megad = 'n';

    typedef struct egyenletrendszer
    {
        char egyenlet[255];
    } egyenletrendszer;

    egyenletrendszer er[10];

    strncpy(er[0].egyenlet, "1.1 * x1  +  2 * x2  +  5 * x3 +  1 * x4 = 4", 255);
    strncpy(er[1].egyenlet, "3 * x1  + -4 * x2  +  3 * x3 + -2 * x4 = 6.8", 255);
    strncpy(er[2].egyenlet, "4 * x1  +  3 * x2  +  2 * x3 + -1 * x4 = 1.2", 255);
    strncpy(er[3].egyenlet, "1 * x1  + -2 * x2  + -4 * x3 + -1 * x4 = 2.09", 255);
    char tmp_egyenlet[255];


    printf("Elore definialt egyenletrendszer: \n");
    for (int i=0; i<n; i++)
        printf("\t%s \n", er[i].egyenlet);
    printf("\n");

    printf("Szeretnel megadni mas egyenleteket? (i/n) : ");
    scanf("%c", &megad);
    getchar();

    if ( megad - 'n') // n = nem, bármi egyéb válasz = igen. // default = nem
    {
        printf("Egyenletek szama: ");
        scanf("%d", &n);
        getchar();

        for (int i=0; i<n; i++)
        {
            printf("%d. egyenlet: ", i+1);
            fgets(er[i].egyenlet, 255, stdin);
        }
    }

    int a[n][n];            // C99 standard szerint lehetséges dinamikusan foglalni memóriát
    int b[n];               // C99 standard szerint lehetséges dinamikusan foglalni memóriát
    double x[n];            // C99 standard szerint lehetséges dinamikusan foglalni memóriát
    double a_double[n][n];  // C99 standard szerint lehetséges dinamikusan foglalni memóriát
    double b_double[n];     // C99 standard szerint lehetséges dinamikusan foglalni memóriát
    double x_double[n];     // C99 standard szerint lehetséges dinamikusan foglalni memóriát


    for (int i=0; i<n; i++)
    {
        strcpy(tmp_egyenlet, er[i].egyenlet);               // parseStr függvényben az strtok() destruktív
        buildArray(*a, b, parseStr(tmp_egyenlet), i, n);    // parseStr visszatéríti a szöveges egyenletből kinyert együtthatókat // első eleme az egyenlőség jobb oldala
        strcpy(tmp_egyenlet, er[i].egyenlet);               // parseStrDouble függvényben az strtok() destruktív
        buildArrayDouble(*a_double, b_double, parseStrDouble(tmp_egyenlet), i, n);
    }



    // Ha az első sor első együtthatója 0, akkor felcserélem a következő sorral
    if (a[0][0] == 0) swap(*a,b,n);

    print_matrix(*a, b, n);

    // Gauss-elimináció egész együtthatókra
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
        print_matrix(*a, b, n);
    }

    // Soronként a legnagyobb közös osztóval végigosztani
    for (int i=0; i<n; i++)
    {
        int gcd = findGCD(*a,b,i,n);
        for (int j=0; j<n; j++)
            a[i][j] /= gcd;
        b[i] /= gcd;
    }

    print_matrix(*a, b, n);

    // Ismeretlenek kiszámítása
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


    ////////////////////////////////////////////////
    ///////////// Valós együtthatókkal /////////////
    ////////////////////////////////////////////////

    printf("\n\n ### Valos egyutthatokkal ###\n\n");

    print_matrix_double(*a_double, b_double, n);

    // Gauss-elimináció valós együtthatókra
    for (int k=0; k<n-1; k++)
    {
        for (int i=k+1; i<n; i++)
        {
            double mult = a_double[i][k];
            double lead = a_double[k][k];

            b_double[i] *= lead;
            b_double[i] -= mult * b_double[k];

            for (int j=k; j<n; j++)
            {
                a_double[i][j] *= lead;
                a_double[i][j] -= mult * a_double[k][j];
            }
        }
        print_matrix_double(*a_double, b_double, n);
    }

    // Ismeretlenek kiszámítása
    // Első egyenlet összege: 4.19999967‬ ~ 4.2

    for (int i=n-1; i>=0; i--)
    {
        int j;
        double sum = b_double[i];
        for (j=0; j<n; j++)
        {
            sum -= a_double[i][j] * x_double[j];
        }
        x_double[i] = sum / a_double[i][i];
    }

    for (int i=0; i<n; i++)
        printf("x%d = %12f\n", i+1, x_double[i]);

    printf("\n\nNyomj meg barmilyen billentyut a kilepeshez.\n");
    getchar();

    return 0;
}
