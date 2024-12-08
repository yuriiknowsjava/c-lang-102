#include <stdio.h>
#include <stdlib.h>

#include "add.h"
#include "multiply.h"

int main()
{
    printf("2 + 2 * 2 = %d\n", add_ints(2, multiply_ints(2, 2)));
    return EXIT_SUCCESS;
}
