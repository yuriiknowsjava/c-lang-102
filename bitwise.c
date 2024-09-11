#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void generic_swap_in_place(const size_t type_size, void *a, void *b)
{
    for (size_t i = 0; i < type_size; i++)
    {
        ((uint8_t *)a)[i] = ((uint8_t *)a)[i] ^ ((uint8_t *)b)[i];
        ((uint8_t *)b)[i] = ((uint8_t *)b)[i] ^ ((uint8_t *)a)[i];
        ((uint8_t *)a)[i] = ((uint8_t *)a)[i] ^ ((uint8_t *)b)[i];
    }
}

/**
 * AND - bit clearing
 * OR  - bit setting
 * XOR - bit toggling
 */
int main()
{
    uint8_t a = 12;
    uint8_t b = 5;
    printf("AND: a & b ==> 1100 & 0101  == %2d\n", a & b);
    printf("OR : a | b ==> 1100 & 0101  == %2d\n", a | b);
    printf("XOR: a ^ b ==> 1100 & 0101  == %2d\n", a ^ b);
    printf("ShL: a & 2 ==> 1100 << 2    == %2d\n", a << 2);
    printf("ShR: a & 2 ==> 1100 >> 2    == %2d\n", a >> 2);
    printf("NOT: ~b    ==> ~0101        == %2d\n", ~b); // aka complement
    puts("");

    printf("Using generic swap with bitwise operators:\n");
    generic_swap_in_place(sizeof(uint8_t), &a, &b);
    printf("uint8_t swap a = %u, b = %u\n", a, b);
    uint32_t m = 9999;
    uint32_t n = 4444;
    generic_swap_in_place(sizeof(uint32_t), &m, &n);
    printf("uint32_t swap m = %u, n = %u\n", m, n);

    puts("");
    return EXIT_SUCCESS;
}
