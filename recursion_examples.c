#include <stdio.h>

int _calc_adjacent_max_tailrec(int arr[], int size, int adjacent_max)
{
    if (size < 2)
    {
        return adjacent_max;
    }
    int curr = arr[0] + arr[1];
    if (curr > adjacent_max)
    {
        adjacent_max = curr;
    }
    return _calc_adjacent_max_tailrec(arr + 1, size - 1, adjacent_max);
}

int calc_adjacent_max_tailrec(int arr[], int size)
{
    if (size < 1)
    {
        return 0;
    }
    if (size < 2)
    {
        return arr[0];
    }
    int curr = arr[0] + arr[1];
    return _calc_adjacent_max_tailrec(arr, size, curr);
}

int calc_adjacent_max_with_local_state(int arr[], int size)
{
    if (size < 1)
    {
        return 0;
    }
    if (size < 2)
    {
        return arr[0];
    }
    int adjacent_max = arr[0] + arr[1];
    int curr = calc_adjacent_max_with_local_state(arr + 1, size - 1);
    if (curr > adjacent_max)
    {
        adjacent_max = curr;
    }
    return adjacent_max;
}

void print_binary(int decimal)
{
    if (decimal <= 1)
    {
        printf("%d", decimal);
        return;
    }
    print_binary(decimal / 2);
    printf("%d", decimal % 2);
}

int main()
{
    int arr[] = {1, 2, 4, 3, 1};
    // int arr[] = {9, 2, 4, 5, 3};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("max adjacent == %d\n", calc_adjacent_max_tailrec(arr, size));

    printf("binary: ");
    print_binary(157);
    printf("\n");

    printf("binary: ");
    print_binary(255);
    printf("\n");

    return 0;
}
