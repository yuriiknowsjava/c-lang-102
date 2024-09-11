#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void print_bin_with_selectors_arr(const uint8_t a)
{
    const uint8_t const selectors[] = {1, 2, 4, 8, 16, 32, 128};
    for (int i = 7; i >= 0; i--)
    {
        uint8_t test = a & selectors[i];
        if (test == 0)
        {
            printf("0");
        }
        else
        {
            printf("1");
        }
    }
    puts("");
}

void print_bin(const uint8_t a)
{
    uint8_t mask = 128;
    for (int i = 0; i < 8; i++)
    {
        uint8_t test = a & mask;
        if (test == 0)
        {
            printf("0");
        }
        else
        {
            printf("1");
        }
        mask >>= 1;
    }
}

int main()
{
    uint8_t a = 2;

    print_bin_with_selectors_arr(a);
    print_bin(a);

    puts("");
    return EXIT_SUCCESS;
}
