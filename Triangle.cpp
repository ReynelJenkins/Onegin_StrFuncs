#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int * createTri(int n);
int outputTri(int n, int *p);
int inputTri(int n, int *p);
int maxTri(int n, int *p);
int minTri(int n, int *p);
int changeTri(int y_change, int x_chage, int *p, int val);

int main()
{
    int *mas = createTri(6);
    inputTri(6, mas);
    outputTri(6, mas);
    changeTri(2, 1, mas, 100);
    outputTri(6, mas);
    return 0;
}

int * createTri(int n)
{
    int *p = (int*)calloc(n, sizeof(*p));
    return p;
}

int outputTri(int n, int *p)
{
    assert(p);

    int n_line = 1;
    int n_el = 1;
    while (n_el < n)
    {
        n_line++;
        n_el += n_line;
    }

    printf("\n\n---------------------------\n\n");

    for (int y = 0; y < n_line; y++)
    {
        for (int x = 0; x <= y; x++)
        {
            int *curr_p = p + (((1 + y) * y)/2) + x;
            printf("%d ", *curr_p);
        }
        printf("\n");
    }

    printf("\n---------------------------\n\n");

    return 1;
}

int inputTri(int n, int *p)
{
    assert(p);

    int n_line = 1;
    int n_el = 1;
    while (n_el < n)
    {
        n_line++;
        n_el += n_line;
    }

    for (int y = 0; y < n_line; y++)
    {
        for (int x = 0; x <= y; x++)
        {
            int *curr_p = p + (((1 + y) * y)/2) + x;
            scanf("%d", curr_p);
        }
    }

    return 1;
}

int maxTri(int n, int *p)
{
    int max = *p;
    for (; n > 0; n--)
    {
        if (*p > max)
        {
            max = *p;
        }

        p++;
    }

    return max;
}

int minTri(int n, int *p)
{
    int min = *p;
    for (; n > 0; n--)
    {
        if (*p < min)
        {
            min = *p;
        }

        p++;
    }

    return min;
}

int changeTri(int y_change, int x_change, int *p, int val)
{
    assert(p);

    int *pos = p + ((1 + y_change) * y_change)/2 + x_change;

    *pos = val;

    return 1;
}
