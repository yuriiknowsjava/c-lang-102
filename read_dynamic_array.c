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

void read_int(int *var)
{
    printf("Enter an integer (any negative int to stop): \n");
    scanf("%d", var);
}

void read_arr_dynamic(int **arr_result, int *size_result)
{
    *arr_result = NULL;
    *size_result = 0;

    int offset = -1;
    int tmp_size = 1;
    int *arr = (int *)malloc(tmp_size * sizeof(int));
    if (arr == NULL)
    {
        return;
    }

    int var = -1;
    read_int(&var);
    while (var > 0)
    {
        offset++;
        arr[offset] = var;
        if (tmp_size - 1 >= offset)
        {
            tmp_size <<= 1; // tmp_size = tmp_size << 1; // tmp_size *= 2;
            int *tmp = (int *)realloc(arr, tmp_size * sizeof(int));
            if (tmp == NULL)
            {
                free(arr);
                return;
            }
            // free(arr); realloc frees the source memory;
            arr = tmp;
        }
        read_int(&var);
    }

    if (offset == -1)
    {
        free(arr);
        return;
    }

    const int size_result_val = offset + 1;
    *size_result = size_result_val;

    int *trimmed_to_size = (int *)malloc(size_result_val * sizeof(int)); // realloc also works to shrink the array
    if (trimmed_to_size == NULL)
    {
        *arr_result = arr;
        printf("Cannot trim array to size. Returning the array as is!\n");
        return;
    }
    memcpy(trimmed_to_size, arr, size_result_val * sizeof(int));
    *arr_result = trimmed_to_size;
    *size_result = size_result_val;
    free(arr);
}

int main()
{
    int size = 0;
    int *arr = NULL;
    read_arr_dynamic(&arr, &size);
    print_ints(arr, size);
}
