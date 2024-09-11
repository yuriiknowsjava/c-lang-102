#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

void print_arr(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int generic_swap(void *a, void *b, size_t size)
{
    void *tmp_mem = malloc(size);
    if (tmp_mem == NULL)
    {
        // cannot complete swap because it couldn't allocate temp memory;
        return 0;
    }

    // void * memcpy(void *dest, const void *src, sizet_t num)
    memcpy(tmp_mem, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp_mem, size);
    free(tmp_mem);
    tmp_mem = NULL;
    return 1;
}

void reverse_recursively(int arr[], int size)
{
    if (size < 2)
    {
        return;
    }
    generic_swap(&arr[0], &arr[size - 1], sizeof(int));
    // -2 because we reduce arr size from both ends
    return reverse_recursively(arr + 1, size - 2);
}

void swap_arrays_O1(void **ptr1, void **ptr2)
{
    void *tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
}

// All static arrays will automatilly be freed after the function exits.
// You cannot call free function on a static array.
// Are static arrays stored on stack?
int *generate_arr(int size, int strategy)
{
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < size; i++)
    {
        if (strategy == 1)
        {
            arr[i] = i;
        }
        else if (strategy == -1)
        {
            arr[i] = size - i - 1;
        }
        else
        {
            arr[i] = 0;
        }
    }
    return arr;
}

int main()
{
    int grade = 80;
    printf("size of int var = %d\n", sizeof(grade)); // 4

    double dgrade = 97.4;
    printf("size of double var = %d\n", sizeof(dgrade)); // 8

    printf("size of double %d\n", sizeof(double)); // 8

    printf("size of char %d\n", sizeof(char)); // 1

    printf("size of 'a' char %d\n", sizeof('a')); // 'a' gets converted to ascii num

    printf("size of \"a\" str %d\n ", sizeof("a")); // 2

    printf("pointer size %d\n", sizeof(&grade));

    int arr[5] = {0};
    int *arr_ptr = arr;       // points only to the first element
    int(*arr_ptr2)[5] = &arr; // points to the whole array, the different can be seen in debug
    printf("Arr %d; size %d\n", arr, sizeof(arr));
    printf("Arr address %d; sizeof %d\n", arr_ptr, sizeof(arr_ptr));
    printf("Arr address2 %d; sizeof %d\n", arr_ptr2, sizeof(arr_ptr2));
    printf("arr_ptr == arr_ptr2 => %d\n", arr_ptr == arr_ptr2);

    void *void_ptr = &grade;
    printf("void ptr: %d\n", *(int *)void_ptr);

    double a = 7.0;
    double b = 42.0;
    generic_swap(&a, &b, sizeof(double));
    printf("after swap: a=%.1f, b=%.1f\n", a, b);

    int to_reverse[5] = {1, 2, 3, 4, 5};
    reverse_recursively(to_reverse, 5);
    print_arr(to_reverse, 5);

    printf("\n");
    const int arrs_to_swap_size = 3;
    int *to_swap1 = generate_arr(arrs_to_swap_size, 1);
    int *to_swap2 = generate_arr(arrs_to_swap_size, -1);
    printf("before ARRAY swap: \n");
    print_arr(to_swap1, arrs_to_swap_size);
    print_arr(to_swap2, arrs_to_swap_size);
    swap_arrays_O1(&to_swap1, &to_swap2);
    printf("after ARRAY swap: \n");
    print_arr(to_swap1, arrs_to_swap_size);
    print_arr(to_swap2, arrs_to_swap_size);
    free(to_swap1);
    to_swap1 = NULL;
    free(to_swap2);
    to_swap2 = NULL;

    // calloc function is similar to malloc but has different signature
    // void *calloc(unsigned num, unsigned size) ==> number of elements (int, double, etc...), size of each element
    // also, calloc function nullifies each element (malloc does not do it and you may get some garbage data).
    int *to_reallocate = (int *)calloc(5, sizeof(5));
    if (to_reallocate == NULL)
    {
        return 3;
    }
    to_reallocate[0] = 999999;

    // realloc may return NULL, 
    // so be careful not to override the old memory's pointer!
    int *reallocated = (int *)realloc(to_reallocate, 7 * sizeof(int));
    if (reallocated == NULL)
    {
        return 4;
    }
    reallocated[5] = 55555;
    reallocated[6] = 666666;
    printf("Reallocated array: \n");
    print_arr(reallocated, 7);
    printf("\n");
    free(reallocated);
}
