#include "my_string.h"

int my_puts(const char *str)
{
    assert(str);

    const char *i = str;
    while (*i != EOF && *i != '\0')
    {
        putchar(*i);
        i++;
    }

    return 1;
}

const char *my_strchr(const char *str, int chr)
{
    assert(str);

    const char *c = str;
    while (*c != '\0' && *c != EOF)
    {
        if (*c == chr)
        {
            return c;
        }
        c++;
    }
    if (*c == '\0')
    {
        if (*c == chr)
        {
            return c;
        }
    }

    return NULL;
}

size_t my_strlen(const char *str)
{
    assert(str);

    const char *start = str;
    const char *end = str;

    while (*end != '\0')
    {
        end++;
    }
    return end - start;
}

char *my_strcpy(char *dest, const char *src)
{
    assert(dest);
    assert(src);

    while (*src != '\0')
    {
        *(dest++) = *(src++);
    }
    *dest = '\0';

    return dest;
}

char *my_strncpy(char *dest, const char *src, size_t count)
{
    assert(dest);
    assert(src);
    if (my_strlen(src) <= count)
    {
        my_strcpy(dest, src);
    }

    else
    {
        for (unsigned int i = 0; i < count; i++)
        {
            *(dest++) = *(src++);
        }

        *dest = '\0';
    }

    return dest;
}

char *my_strcat(char *dest, const char *src)
{
    assert(dest);
    assert(src);

    char *start = dest + my_strlen(dest);

    my_strcpy(start, src);

    return dest;
}

char *my_strncat(char *dest, const char *src, size_t count)
{
    assert(dest);
    assert(src);

    if (my_strlen(src) <= count)
    {
        my_strcpy(dest + my_strlen(dest), src);
    }

    else
    {
        my_strncpy(dest + my_strlen(dest), src, count);
    }

    return dest;
}

char *my_fgets(char *s, int n, FILE *stream)
{
    assert(s);
    assert(stream);

    if (n <= 0) return NULL;

    int c;
    char *p = s;

    while (--n > 0 && (c = getc(stream)) != EOF) {
        *p++ = (char)c;
        if (c == '\n') break;
    }

    *p = '\0';
    return s;
}

int my_atoi(const char *str)
{
    assert(str);

    int sign = 1;
    int result = 0;

    while(!(*str == '-' || (*str <= '9' && *str >= '0')))
    {
        if (*str == '\0')
        {
            return 0;
        }
        str++;

    }

    if (*str == '-')
    {
        sign = -1;
        str++;
    }

    else
    {
        sign = 1;
    }

    while(*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }

    return result * sign;
}

char *my_strdup(const char *str1)
{
    assert(str1);

    char *str2 = (char *)calloc(my_strlen(str1) + 1, sizeof(char));
    my_strcpy(str2, str1);
    return str2;
}

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
    assert(lineptr);
    assert(n);
    assert(stream);

    if (*lineptr == NULL || *n == 0) {
        size_t init_size = 128;
        char *buf = (char*)calloc(init_size, sizeof(*buf));
        if (buf == NULL) {
            printf("No memory found!");
            return -1;
        }
        *lineptr = buf;
        *n = init_size;
    }


    char *buf = *lineptr;
    size_t bufsize = *n;
    size_t pos = 0;
    int c;

    while ((c = getc(stream)) != EOF) {

        if (pos + 1 >= bufsize) {
            size_t new_size = bufsize * 2;
            if (new_size < bufsize + 1)
            {
                printf("No memory found!");
                return -1;
            }
            char *new_buf = (char*)realloc(buf, new_size);
            if (new_buf == NULL) {
                printf("No memory found!");
                return -1;
            }
            buf = new_buf;
            bufsize = new_size;
            *lineptr = buf;
            *n = bufsize;
        }

        buf[pos++] = (char)c;

        if (c == '\n') {
            break;
        }
    }

    if (pos == 0 && c == EOF) {
        return -1;
    }

    buf[pos] = '\0';
    *lineptr = buf;
    *n = bufsize;

    return (ssize_t)pos;
}
