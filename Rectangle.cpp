#include <stdio.h>

int inputRect(size_t sizeY, size_t sizeX, int mas[3][4]);
int outputRect(size_t sizeY, size_t sizeX, int mas[3][4]);
int maxRect(size_t sizeY, size_t sizeX, int mas[3][4]);
int minRect(size_t sizeY, size_t sizeX, int mas[3][4]);

int main()
{
    int mas[3][4] = {};
    inputRect(3, 4, mas);
    outputRect(3, 4, mas);
    int max_mas = minRect(3, 4, mas);
    printf("%d\n", max_mas);
    return 0;
}

int inputRect(size_t sizeY, size_t sizeX, int mas[3][4])
{
    for (unsigned int y = 0; y < sizeY; y++)
    {
        for (unsigned int x = 0; x < sizeX; x++)
        {
            scanf("%d", &mas[y][x]);
        }
    }

    return 1;
}

int outputRect(size_t sizeY, size_t sizeX, int mas[3][4])
{

    printf("\n\n---------------------------\n\n");

    for (unsigned int y = 0; y < sizeY; y++)
    {
        for (unsigned int x = 0; x < sizeX; x++)
        {
            printf("%4d ", mas[y][x]);
        }
        printf("\n");
    }

    printf("\n---------------------------\n\n");

    return 1;
}

int maxRect(size_t sizeY, size_t sizeX, int mas[3][4])
{
    int max = mas[0][0];

    for (unsigned int y = 0; y < sizeY; y++)
    {
        for (unsigned int x = 0; x < sizeX; x++)
        {
            if (mas[y][x] > max)
            {
                max = mas[y][x];
            }
        }
    }

    return max;
}

int minRect(size_t sizeY, size_t sizeX, int mas[3][4])
{
    int min = mas[0][0];
    for (unsigned int y = 0; y < sizeY; y++)
    {
        for (unsigned int x = 0; x < sizeX; x++)
        {
            if (mas[y][x] < min)
            {
                min = mas[y][x];
            }
        }
    }

    return min;
}
