#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LEN 5

void print_and_free_doubles(const int len, double arr[len]);

void print_and_free_ints(const int len, int arr[len]);

void print_and_free_chars(const int len, char arr[len]);

void *generic_insert(const size_t type_size,
                     const int len, const void *const void_arr,
                     const void *const el_to_insert, const int idx)
{
    if (type_size < 1 || len < 1 || void_arr == NULL || el_to_insert == NULL || idx < 0 || idx > len)
    {
        return NULL;
    }

    char *new_arr = (char *)calloc(len + 1, type_size);
    if (new_arr == NULL)
    {
        return NULL;
    }

    const char *const ch_arr = (char *)void_arr;
    const int idx_byte_resized = idx * type_size;
    const int len_bytes = len * type_size;
    if (idx == 0)
    {
        memcpy(new_arr, el_to_insert, type_size);
        memcpy(new_arr + type_size, ch_arr, len_bytes);
    }
    else if (idx < len)
    {
        memcpy(new_arr, ch_arr, idx_byte_resized);
        memcpy(new_arr + idx_byte_resized, el_to_insert, type_size);
        memcpy(new_arr + idx_byte_resized + type_size, ch_arr + idx_byte_resized, len_bytes - idx_byte_resized);
    }
    else
    {
        memcpy(new_arr, ch_arr, len_bytes);
        memcpy(new_arr + len_bytes, el_to_insert, type_size);
    }
    return new_arr;
}

void *generic_delete(const size_t type_size,
                     const int len, const void *const void_arr,
                     const int idx)
{
    if (type_size < 1 || len < 1 || void_arr == NULL || idx < 0 || idx >= len)
    {
        return NULL;
    }

    const int new_len = len - 1;
    char *new_arr = (char *)calloc(new_len, type_size);
    if (new_arr == NULL)
    {
        return NULL;
    }

    const char *const ch_arr = (char *)void_arr;
    const int idx_byte_resized = idx * type_size;
    const int new_len_bytes = new_len * type_size;
    if (idx == 0)
    {
        memcpy(new_arr, ch_arr + type_size, new_len_bytes);
    }
    else if (idx < new_len)
    {
        memcpy(new_arr, ch_arr, idx_byte_resized);
        memcpy(new_arr + idx_byte_resized, ch_arr + type_size + idx_byte_resized, new_len_bytes - idx_byte_resized);
    }
    else
    {
        memcpy(new_arr, ch_arr, new_len_bytes);
    }
    return new_arr;
}

int main()
{
    double doubles[LEN] = {1.1, 2.1, 3.1, 4.1, 5.1};
    int integers[LEN] = {1, 2, 3, 4, 5};
    char characters[LEN] = {'a', 'b', 'c', 'd', 'e'};

    {
        printf("Interting a double in the middle      : ");
        const double to_insert = 9.99;
        const int idx = 2;
        double *result = generic_insert(sizeof(double), LEN, (void *)doubles, &to_insert, idx);
        print_and_free_doubles(LEN + 1, result);
    }
    {
        printf("Inserting an integer at the end       : ");
        const int to_insert = -99;
        const int idx = LEN;
        int *result = generic_insert(sizeof(int), LEN, (void *)integers, &to_insert, idx);
        print_and_free_ints(LEN + 1, result);
    }
    {
        printf("Inserting a character at the beginning:");
        const char to_insert = 'W';
        const int idx = 0;
        char *result = generic_insert(sizeof(char), LEN, (void *)&characters, &to_insert, idx);
        print_and_free_chars(LEN + 1, result);
    }
    puts("");

    {
        printf("Deleting a double at idx#0       : ");
        const int idx = 0;
        double *result = generic_delete(sizeof(double), LEN, doubles, idx);
        print_and_free_doubles(LEN - 1, result);
    }
    {
        printf("Deleting an integer in the middle: ");
        const int idx = 3;
        int *result = generic_delete(sizeof(int), LEN, integers, idx);
        print_and_free_ints(LEN - 1, result);
    }
    {
        printf("Deleting a character from the end:");
        const int idx = LEN - 1;
        char *result = generic_delete(sizeof(char), LEN, characters, idx);
        print_and_free_chars(LEN - 1, result);
    }

    puts("");
    return EXIT_SUCCESS;
}

int validate_before_print(const int len, const void *const arr)
{
    if (len < 1)
    {
        printf("Array length cannot be less than 1\n");
        return 0;
    }
    if (arr == NULL)
    {
        printf("Array cannot be NULL\n");
        return 0;
    }
    return 1;
}

void print_and_free_doubles(const int len, double arr[len])
{
    if (validate_before_print(len, arr) == 0)
    {
        return;
    }
    for (int i = 0; i < len; i++)
    {
        printf("%.2f ", arr[i]);
    }
    free(arr);
    puts("");
}

void print_and_free_ints(const int len, int arr[len])
{
    if (validate_before_print(len, arr) == 0)
    {
        return;
    }
    for (int i = 0; i < len; i++)
    {
        printf("%4d ", arr[i]);
    }
    free(arr);
    puts("");
}

void print_and_free_chars(const int len, char arr[len])
{
    if (validate_before_print(len, arr) == 0)
    {
        return;
    }
    for (int i = 0; i < len; i++)
    {
        printf("%5c", arr[i]);
    }
    free(arr);
    puts("");
}
