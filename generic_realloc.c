#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_ints(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_doubles(double arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%.2f ", arr[i]);
    }
    printf("\n");
}

void print_chars(char arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%c ", arr[i]);
    }
    printf("\n");
}

void *my_generic_realloc(void *srcblock, size_t oldsize_bytes, size_t newsize_bytes);

int main()
{
    int ints[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double doubles[] = {0.01, 0.02, 0.03, 0.04, 0.05, 0.06};
    char chars[] = {'a', 'b', 'c', 'd'};

    int new_int_size = 20;
    int *new_ints = my_generic_realloc(ints, sizeof(ints) * sizeof(int), new_int_size * sizeof(int));

    int new_double_size = 3;
    double *new_doubles = my_generic_realloc(doubles, sizeof(doubles) * sizeof(double), new_double_size * sizeof(double));

    int new_char_size = sizeof(chars) / sizeof(char);
    char *new_chars = my_generic_realloc(chars, sizeof(chars) * sizeof(char), new_char_size * sizeof(char));

    puts("New ints: ");
    print_ints(new_ints, new_int_size);
    puts("");
    puts("New doubles: ");
    print_doubles(new_doubles, new_double_size);
    puts("");
    puts("New chars: ");
    print_chars(new_chars, new_char_size);
    puts("");
}

void *my_generic_realloc(void *srcblock, size_t oldsize_bytes, size_t newsize_bytes)
{
    if (srcblock == NULL || oldsize_bytes <= 0 || newsize_bytes <= 0)
    {
        return NULL;
    }

    char *destblock = (char *)malloc(newsize_bytes); // char is just 1 byte
    if (destblock == NULL)
    {
        return NULL;
    }

    char *old = (char *)srcblock;
    if (newsize_bytes >= oldsize_bytes)
    {
        memcpy(destblock, srcblock, oldsize_bytes + 1);
        for (size_t i = oldsize_bytes; i < newsize_bytes; i++)
        {
            destblock[i] = 0;
        }
    }
    else
    {
        memcpy(destblock, srcblock, newsize_bytes + 1);
    }

//  does not work for static arrays
    // free(srcblock);
    // srcblock = NULL;
    // old = NULL;
    return (void *) destblock;
}
