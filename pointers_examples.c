#include <stdio.h>

// int arr[] is just a syntatic sugar, but it's basically int *arr
// do NOT try int len = sizeof(arr) / sizeof(arr[0]);
int pointers_arithmetic(const int len, const int arr[len])
{
    for (const int *p_item = arr; p_item < arr + len; p_item++)
    {
        printf("p_item is %p\n", p_item);
        printf("*p_item is %d\n", *p_item);
        printf("offset is %ld\n", p_item - arr);
        printf("\n");
    }
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int *arr_p = arr;
    int (*fp)[5] = &arr;
    printf("arr_p=%p == fp=%p\n", arr_p, fp);
    printf("\n");

    // this trick of calculating size only works for static arrays and only in the scope of the function.
    int len = sizeof(arr) / sizeof(arr[0]);
    pointers_arithmetic(len, arr);

    int vlen = 6;
    int varr[6]; // cannot init a variable length arr
    for (int i = 0; i < vlen; i++)
    {
        varr[i] = i;
        printf("%d", varr[i]);
    }
    printf("\n");

    char str[] = "My String";
    // str = "Another String"; // compilation error
    char *str_ptr = "Str pointer";
    str_ptr = "Another string";
}
