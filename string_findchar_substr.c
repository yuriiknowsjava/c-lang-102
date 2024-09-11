#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

void find_char_occurrences(const char str[], const char ch, long **occurrences)
{
    int len = strlen(str);
    *occurrences = (long *)calloc(len, sizeof(long));
    if (occurrences == NULL)
    {
        return;
    }
    memset(*occurrences, -1, len);

    int found_idx = 0;
    const char *pstr = str;
    while (found_idx < len)
    {
        // Find char address in a string
        pstr = strchr(pstr, ch);
        if (pstr != NULL)
        {
            long offset = pstr - str;
            (*occurrences)[found_idx] = offset;
            found_idx++;
            pstr++;
        }
        else
        {
            break;
        }
    }

    int occurrences_len = found_idx;
    if (occurrences_len == 0)
    {
        // if nothing is found
        occurrences_len++;
    }

    long *result = (long *)realloc(*occurrences, occurrences_len * sizeof(long));
    if (result != NULL)
    {
        result[found_idx] = -1;
        *occurrences = result;
    }
    else
    {
        *occurrences = NULL;
    }
}

void print_occurrences(const char const str[], const long const occurrences[])
{
    int str_len = strlen(str);
    char pattern[str_len + 1];
    memset(pattern, ' ', sizeof(pattern));
    for (int i = 0; i < str_len; i++)
    {
        long occurrence = occurrences[i];
        if (occurrence == -1)
        {
            break;
        }
        else
        {
            pattern[occurrence] = '^';
        }
    }

    pattern[str_len] = '\0';
    printf("%s\n", str);
    printf("%s\n", pattern);
}

void find_substrings(const char str[], const char substr[], long **occurrences)
{
    int len = strlen(str);
    const char *pstr = str;
    int found_idx = 0;
    *occurrences = (long *)calloc(len, sizeof(long));
    if (occurrences == NULL)
    {
        return;
    }
    memset(*occurrences, -1, len);
    while (found_idx < len)
    {
        pstr = strstr(pstr, substr);
        if (pstr != NULL)
        {
            long offset = pstr - str;
            (*occurrences)[found_idx] = offset;
            found_idx++;
            pstr++;
        }
        else
        {
            break;
        }
    }

    int occurrences_len = found_idx;
    if (occurrences_len == 0)
    {
        // if nothing is found
        occurrences_len++;
    }
    long *result = (long *)realloc(*occurrences, sizeof(long) * occurrences_len);
    if (result != NULL)
    {
        result[found_idx] = -1;
        *occurrences = result;
    }
    else
    {
        *occurrences = NULL;
    }
}

void print_substr(const char const str[], const char const substr[], const long *const occurences)
{
    int str_len = strlen(str);
    char pattern[str_len + 1];
    memset(pattern, ' ', sizeof(pattern));
    for (int i = 0; i < str_len; i++)
    {
        long occurrence = occurences[i];
        if (occurrence == -1)
        {
            break;
        }
        else
        {
            memset(pattern + occurrence, '-', strlen(substr));
        }
    }
    pattern[str_len] = '\0';
    printf("%s\n", str);
    printf("%s\n", pattern);
}

int main()
{
    {
        char str[64] = {'\0'};
        int len = sizeof(str);

        // strcpy - deprecated; use strncpy instead.
        strncpy(str, "This is a sample string", len);
        // strncpy does not automatically add \0 to the dest str. If you want to make a str shorter, add it manually!

        long *occurrences = NULL;
        find_char_occurrences(str, 's', &occurrences);
        if (occurrences == NULL)
        {
            printf("Cannot allocate memory\n");
            return EXIT_FAILURE;
        }
        print_occurrences(str, occurrences);
        free(occurrences);
        puts("");
    }

    {
        char str2[] = "if two witches were watching two watches, which witch would watch which watch?";
        char substr[] = "witch";
        long *occurrences2 = NULL;
        find_substrings(str2, substr, &occurrences2);
        if (occurrences2 == NULL)
        {
            printf("Cannot find substrings");
            return EXIT_FAILURE;
        }
        print_substr(str2, substr, occurrences2);
        free(occurrences2);
        puts("");
    }
    return EXIT_SUCCESS;
}
