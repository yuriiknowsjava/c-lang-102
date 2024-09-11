#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generic_swap(void *a, void *b, size_t size)
{
    void *tmp_mem = malloc(size);
    memcpy(tmp_mem, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp_mem, size);
    free(tmp_mem);
}

void free2d(const int rows, void **arr)
{
    if (arr == NULL)
    {
        return;
    }
    for (int r = 0; r < rows; r++)
    {
        if (arr[r] != NULL)
        {
            free(arr[r]);
            arr[r] = NULL;
        }
    }
}

double **create_doubles2d(const int rows, const int columns)
{
    double **doubles2d = calloc(rows, sizeof(*doubles2d)); // sizeof(double *)
    if (doubles2d == NULL)
    {
        printf("Cannot allocate mem\n");
        return NULL;
    }
    for (int i = 0; i < rows; i++)
    {
        double *b = calloc(columns, sizeof(**doubles2d)); // sizeof(double)
        if (b == NULL)
        {
            printf("Cannot allocate mem\n");
            goto cleanup;
        }
        else
        {
            doubles2d[i] = b;
        }
    }
    return doubles2d;

cleanup:
    free2d(rows, (void **)doubles2d);
    return NULL;
}

void swap_rows(const int rows, const int idx1, const int idx2, void **arr)
{
    if (idx1 < 0 || idx1 >= rows || idx2 < 0 || idx2 >= rows || idx1 == idx2)
    {
        return;
    }
    void *tmp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = tmp;
}

void swap_columns(const size_t type_size,
                  const int rows, const int columns,
                  const int idx1, const int idx2,
                  void **arr)
{
    if (idx1 < 0 || idx1 >= columns || idx2 < 0 || idx2 >= columns)
    {
        return;
    }
    char **ch_arr = (char **)arr;
    const int idx1_byte_resized = idx1 * type_size;
    const int idx2_byte_resized = idx2 * type_size;

    // array of points has the fix length - platform pointer size. Don't need to resize.
    for (int i = 0; i < rows; i++)
    {
        char *p_idx1 = ch_arr[i] + idx1_byte_resized;
        char *p_idx2 = ch_arr[i] + idx2_byte_resized;
        generic_swap(p_idx1, p_idx2, type_size);
    }
}

void print2d(const int rows, const int columns, double **const arr);

int main()
{
    const int rows = 5;
    const int columns = 7;
    double **arr = create_doubles2d(rows, columns);
    if (arr == NULL)
    {
        return EXIT_FAILURE;
    }

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            arr[r][c] = r * c;
        }
        puts("");
    }

    swap_rows(rows, 0, 1, (void **)arr);
    swap_columns(sizeof(double), rows, columns, 3, 4, (void **)arr);
    print2d(rows, columns, arr);

    free2d(rows, (void **)arr);
    puts("");
    return EXIT_SUCCESS;
}

void print2d(const int rows, const int columns, double **const arr)
{
    printf("    ");
    for (int i = 0; i < columns; i++)
    {
        printf("%5d|", i);
    }
    puts("");

    for (int r = 0; r < rows; r++)
    {
        printf("%2d |", r);
        for (int c = 0; c < columns; c++)
        {
            printf("%5.1f ", arr[r][c]);
        }
        puts("");
    }
}
