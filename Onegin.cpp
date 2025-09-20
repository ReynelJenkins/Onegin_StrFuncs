#include <TXlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include "my_string.h"

struct Text
{
    char *buf                 = nullptr;
    struct String *struct_ptr = nullptr;
    size_t lines              = 0;
    size_t file_size          = 0;
};

struct String
{
    char *str   = nullptr;
    int str_len = 0;
};

enum SortType
{
    Forward      = 0,
    Reverse      = 1,
    RestoreOrder = 2
};


struct String* ReadText(FILE *file, char *buf, size_t *file_size, size_t *lines);
size_t GetFileSize(const char *file_name);
int PrintLines(struct String *struct_ptr, size_t lines);
int SwapStr(struct String *str1, struct String *str2);
int CompareStr(struct String str1, struct String str2, int sort_type);
int BubbleSort(struct String *ptr, size_t lines, int sort_type);
int FilePrintLines(FILE *file, struct String *struct_ptr, size_t lines);
int isalpha_win1251(unsigned char c);
bool isAllNonAlpha(const char *str);
FILE *my_fopen(const char *file_name, const char* type);
int FileOutputTask(struct Text *Poem, FILE *file);
int FillPoemParams(struct Text *Poem, const char *file_name, FILE *file);
int QSort(struct String *ptr, size_t lines);
int MyCmp(const void *obj1, const void *obj2);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Invalid arguments\n");
        printf("Usage: ./onegin.exe \"text_file\" \"output_file\" ");
        return 1;
    }

    const char *file_name = argv[1];
    const char *file_name_output = argv[2];
    struct Text Poem = {};

    FILE *file = my_fopen(file_name, "rb");

    if (file == nullptr)
    {
        return 1;
    }

    FillPoemParams(&Poem, file_name, file);

    fclose(file);

    file = my_fopen(file_name_output, "wb");

    if (file == nullptr)
    {
        return 1;
    }

    FileOutputTask(&Poem, file);

    fclose(file);
    QSort(Poem.struct_ptr, Poem.lines);
    PrintLines(Poem.struct_ptr, Poem.lines);

    free(Poem.struct_ptr);
    free(Poem.buf);

    return 0;
}

int FillPoemParams(struct Text *Poem, const char *file_name, FILE *file)
{

    Poem->file_size = GetFileSize(file_name);
    Poem->buf = (char*)calloc(Poem->file_size + 1, sizeof(char));
    assert(Poem->buf);

    Poem->struct_ptr = ReadText(file, Poem->buf, &(Poem->file_size), &(Poem->lines));

    return 1;
}

int FileOutputTask(struct Text *Poem, FILE *file)
{
    BubbleSort(Poem->struct_ptr, Poem->lines, Forward);
    FilePrintLines(file, Poem->struct_ptr, Poem->lines);
    fprintf(file, "\n\n\n\n\n\n\n--------------------------------------------\n\n\n\n\n\n\n");

    BubbleSort(Poem->struct_ptr, Poem->lines, Reverse);
    FilePrintLines(file, Poem->struct_ptr, Poem->lines);
    fprintf(file, "\n\n\n\n\n\n\n--------------------------------------------\n\n\n\n\n\n\n");

    BubbleSort(Poem->struct_ptr, Poem->lines, RestoreOrder);
    FilePrintLines(file, Poem->struct_ptr, Poem->lines);

    return 1;
}

int isalpha_win1251(unsigned char c)
{
    if (isalpha(c))
    {
        return 1;
    }

    if ((c >= 192 && c <= 223) || c == 168 ||
        (c >= 224)             || c == 184)
    {
        return 1;
    }

    return 0;
}

FILE *my_fopen(const char *file_name, const char *type)
{
    assert(file_name);
    assert(type);

    FILE *file = fopen(file_name, type);
    if (!file)
    {
        printf("Failed to open file: %s", file_name);

        return nullptr;
    }

    return file;
}

bool isAllNonAlpha(const char *str)
{
    assert(str);

    if (*str == '\0')
    {
        return true;
    }

    while (*str != '\0')
    {
        if ( isalpha_win1251(*str))
        {
            return false;
        }
        str++;
    }

    return true;
}

struct String* ReadText(FILE *file, char *buf, size_t *file_size, size_t *lines)
{
    assert(file);
    assert(buf);
    assert(file_size);
    assert(lines);

    *file_size = fread(buf, 1, *file_size, file) + 1;
    buf[*file_size] = '\0';

    *lines = 0;

    for (long long i = 0; i < *file_size; i++)
    {
        if (buf[i] == '\n')
        {
            (*lines)++;

            if (i > 0 && ((buf[i-1]) == '\r'))
            {
                buf[i-1] = '\0';
                assert(file);
                assert(buf);
                assert(file_size);
                assert(lines);
            }

            assert(file);
            assert(buf);
            assert(file_size);
            assert(lines);

            buf[i] = '\0';
        }
    }

    assert(file);
    assert(buf);
    assert(file_size);
    assert(lines);

    if(*file_size > 0 && buf[*file_size - 1] != '\n' && buf[*file_size - 1] != '\0')
    {
        (*lines)++;
        assert(file);
        assert(buf);
        assert(file_size);
        assert(lines);
    }

    assert(file);
    assert(buf);
    assert(file_size);
    assert(lines);

    struct String *struct_ptr = (struct String *)calloc(*lines + 1, sizeof(struct String));
    assert(struct_ptr);

    (*struct_ptr).str = buf;
    (*struct_ptr).str_len = (int)(strchr(buf, '\0') - buf);

    assert(file);
    assert(buf);
    assert(file_size);
    assert(lines);

    size_t line_index = 1;

    for(long long i = 0; i < *file_size; i++)
    {
        if(i > 0 && buf[i-1] == '\0' && buf[i] != '\0')
        {
            assert(line_index < *lines);
            assert(file);
            assert(buf);
            assert(file_size);
            assert(lines);
            (*(struct_ptr + line_index)).str = &buf[i];
            (*(struct_ptr + line_index)).str_len = (int)(strchr(&buf[i], '\0') - &buf[i]);
            line_index++;
        }
    }

    *lines = line_index;

    struct_ptr = (struct String *)realloc(struct_ptr, line_index * sizeof(struct String));
    /// Assert is not necessary!!!
    assert(struct_ptr);

    assert(file);
    assert(buf);
    assert(file_size);
    assert(lines);

    return struct_ptr;
}

size_t GetFileSize(const char *file_name)
{
    assert(file_name);
    struct stat file_stat;
    stat(file_name, &file_stat);

    return file_stat.st_size;
}

int PrintLines(struct String *struct_ptr, size_t lines)
{
    assert(struct_ptr);

    for (size_t i = 0; i < lines; i++)
    {
        printf("Line %5d (Line length %3d): %s\n", i + 1, (struct_ptr[i]).str_len, (struct_ptr[i]).str);
    }

    return 1;
}

int SwapStr(struct String *str1, struct String *str2)
{
    assert(str1);
    assert(str2);
    struct String temp = *str1;
    *str1 = *str2;
    *str2 = temp;

    return 1;
}

int CompareStr(struct String str1, struct String str2, int sort_type) //void *
{
    char *s1 = str1.str;
    char *s2 = str2.str;

    bool fl_no_alpha1 = isAllNonAlpha(s1);
    bool fl_no_alpha2 = isAllNonAlpha(s2);

    if (sort_type != RestoreOrder)
    {
        if (fl_no_alpha1 || fl_no_alpha2)
        {
            if (fl_no_alpha1 == true)
            {
                return -1;
            }
            if (fl_no_alpha2 == true)
            {
                return 1;
            }
        }
    }

    if (sort_type == Forward)
    {
        while (*s1 != '\0' && *s2 != '\0')
        {
            if ( isalpha_win1251(*s1) &&  isalpha_win1251(*s2))
            {
                if (*s1 - *s2 != 0)
                {
                    return (unsigned char)*s1 - (unsigned char)*s2;
                }

                s1++;
                s2++;
            }

            if (! isalpha_win1251(*s1) && *s1 != '\0')
            {
                s1++;
            }

            if (! isalpha_win1251(*s2) && *s2 != '\0')
            {
                s2++;
            }
        }
    }

    if (sort_type == Reverse)
    {
        s1 = s1 + str1.str_len;
        s2 = s2 + str2.str_len;

        while (s1 >= str1.str && s2 >= str2.str)
        {
            if ( isalpha_win1251(*s1) &&  isalpha_win1251(*s2))
            {
                if (*s1 - *s2 != 0)
                {
                    return (unsigned char)*s1 - (unsigned char)*s2;
                }

                s1--;
                s2--;
            }

            if (!isalpha_win1251(*s1) && s1 >= str1.str)
            {
                s1--;
            }

            if (!isalpha_win1251(*s2) && s2 >= str2.str)
            {
                s2--;
            }
        }
    }

    if (sort_type == RestoreOrder)
    {
        return str1.str - str2.str;
    }

    return 0;
}

int BubbleSort(struct String *ptr, size_t lines, int sort_type)
{
    assert(ptr);

    for (size_t i = 0; i < lines - 1; i++)
    {
        bool fl_changed = false;

        for (size_t j = 0; j < lines - 1 - i; j++)
        {
            if (CompareStr(ptr[j], ptr[j+1], sort_type) > 0)
            {
                SwapStr(&ptr[j], &ptr[j+1]);
                fl_changed = true;
            }
        }

        if (!fl_changed)
        {
            break;
        }
    }
    return 1;
}

int FilePrintLines(FILE *file, struct String *struct_ptr, size_t lines)
{
    assert(file);
    assert(struct_ptr);

    for (size_t i = 0; i < lines; i++)
    {
        fprintf(file, "Line %5d (Line length %3d): %s\n", i + 1, (struct_ptr[i]).str_len, (struct_ptr[i]).str);
    }

    return 1;
}

int QSort(struct String *ptr, size_t lines)
{
    qsort(ptr, lines, sizeof(struct String), MyCmp);

    return 1;
}

int MyCmp(const void *obj1, const void *obj2)
{
    const char *s1 = ((const struct String *)obj1)->str;
    const char *s2 = ((const struct String *)obj2)->str;

    bool fl_no_alpha1 = isAllNonAlpha(s1);
    bool fl_no_alpha2 = isAllNonAlpha(s2);

    if (fl_no_alpha1 || fl_no_alpha2)
    {
        if (fl_no_alpha1 == true)
        {
            return -1;
        }
        if (fl_no_alpha2 == true)
        {
            return 1;
        }
    }

    while (*s1 != '\0' && *s2 != '\0')
    {
        if ( isalpha_win1251(*s1) &&  isalpha_win1251(*s2))
        {
            if (*s1 - *s2 != 0)
            {
                return (unsigned char)*s1 - (unsigned char)*s2;
            }

            s1++;
            s2++;
        }

        if (! isalpha_win1251(*s1) && *s1 != '\0')
        {
            s1++;
        }

        if (! isalpha_win1251(*s2) && *s2 != '\0')
        {
            s2++;
        }
    }

    return 0;
}
