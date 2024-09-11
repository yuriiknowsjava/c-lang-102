#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

void print_arr(int size, int const arr[size])
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int *make_arr_copy(int len, const int *const arr)
{
    int *arr_copy = calloc(len, sizeof(arr[0]));
    if (arr_copy == NULL)
    {
        perror("Cannot allocate memory to copy an array");
        exit(EXIT_FAILURE);
    }
    memcpy(arr_copy, arr, len * sizeof(arr[0]));
    return arr_copy;
}

void generic_swap(void *a, void *b, size_t size)
{
    void *tmp_mem = malloc(size);
    if (tmp_mem == NULL)
    {
        return;
    }

    // void * memcpy(void *dest, const void *src, size_t num)
    memcpy(tmp_mem, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp_mem, size);
    free(tmp_mem);
}

void bubble_sort(int len, int arr[len])
{
    int was_swapped;
    for (int i = 0; i < len; i++)
    {
        was_swapped = 0;
        for (int j = 0; j < len - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                generic_swap(&arr[j], &arr[j + 1], sizeof(arr[0]));
                was_swapped = 1;
            }
        }
        if (was_swapped == 0)
        {
            break;
        }
        //
    }
}

void _merge(int *arr, const int left_offset, const int middle_offset, const int right_offset)
{
    const int left_arr_len = middle_offset - left_offset + 1;
    int left_cpy[left_arr_len];
    int left_idx = 0;
    memcpy(left_cpy, arr + left_offset, left_arr_len * sizeof(int));

    const int right_arr_len = right_offset - middle_offset;
    int right_cpy[right_arr_len];
    int right_idx = 0;
    memcpy(right_cpy, arr + middle_offset + 1, right_arr_len * sizeof(int));

    int global_idx = left_offset;

    while (left_idx < left_arr_len && right_idx < right_arr_len)
    {
        if (left_cpy[left_idx] < right_cpy[right_idx])
        {
            arr[global_idx] = left_cpy[left_idx];
            left_idx++;
        }
        else
        {
            arr[global_idx] = right_cpy[right_idx];
            right_idx++;
        }
        global_idx++;
    }
    while (left_idx < left_arr_len)
    {
        arr[global_idx] = left_cpy[left_idx];
        global_idx++;
        left_idx++;
    }
    while (right_idx < right_arr_len)
    {
        arr[global_idx] = right_cpy[right_idx];
        global_idx++;
        right_idx++;
    }
}

void _merge_sort(int *arr, int left_offset, int right_offset)
{
    if (left_offset >= right_offset)
    {
        return;
    }
    int middle_offset = left_offset + (right_offset - left_offset) / 2;
    _merge_sort(arr, left_offset, middle_offset);
    _merge_sort(arr, middle_offset + 1, right_offset);
    _merge(arr, left_offset, middle_offset, right_offset);
}

void merge_sort(int len, int arr[len])
{
    if (len < 0)
    {
        return;
    }
    _merge_sort(arr, 0, len - 1);
}

int main()
{
    const int const arr[] = {4, 3, 5, 6, 2, 1, 5};
    int len = sizeof(arr) / sizeof(arr[0]);
    int *arr_copy = NULL;
    printf("Unordered  : ");
    print_arr(len, arr);

    arr_copy = make_arr_copy(len, arr);
    bubble_sort(len, arr_copy);
    printf("bubble sort: ");
    print_arr(len, arr_copy);
    free(arr_copy);
    arr_copy = NULL;

    arr_copy = make_arr_copy(len, arr);
    merge_sort(len, arr_copy);
    printf("merge sort : ");
    print_arr(len, arr_copy);
    free(arr_copy);
    arr_copy = NULL;

    puts("");
    return EXIT_SUCCESS;
}
