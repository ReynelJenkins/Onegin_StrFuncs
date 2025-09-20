#ifndef MY_STRING_H
#define MY_STRING_G

#include <stdlib.h>

//todo: getline
#include <string.h>
#include <stdio.h>
#include <assert.h>

int my_puts(const char *str);
const char *my_strchr(const char *str, int chr);
size_t my_strlen(const char *str);
char *my_strcpy(char *dest, const char *src);
char *my_strncpy(char *dest, const char *src, size_t count);
char *my_strcat(char *dest, const char *src);
char *my_strncat(char *dest, const char *src, size_t count);
char *my_fgets(char *s, int n, FILE *stream);
int my_atoi(const char *str);
char *my_strdup(const char *str1);
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);

#endif //MY_STRING_H
