#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isalpha_win1251(unsigned char c);

int main()
{
    char str[] = "Так люди (первый каюсь я)";

    printf("%d", isalpha_win1251('А'));

    char *s1 = str + strlen(str);

    while (s1 >= str)
    {
        if (isalpha(*s1))
        {
            printf("%c", *s1);
            s1--;
        }
        if (!isalpha(*s1) && s1 >= str)
        {
            s1--;
        }
    }
/*
    unsigned char my_chr = (unsigned char)'я';
    printf("%c, %d", my_chr, my_chr);
    my_chr = (unsigned char)'ю';
    printf("%c, %d", my_chr, my_chr);
*/
}
