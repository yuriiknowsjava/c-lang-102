#include <stdio.h>
#include <stdlib.h>

#define CALC_ARRAY_LEN(x) (sizeof((x)) / sizeof((x)[0]))

double cube(int a)
{
    return 1.0 * a * a * a;
}

void add(int a, int b)
{
    printf("a + b = %d\n", a + b);
}

void subtract(int a, int b)
{
    printf("a - b = %d\n", a - b);
}

void multiply(int a, int b)
{
    printf("a * b = %d\n", a * b);
}

void divide(int a, int b)
{
    if (b != 0)
    {
        printf("a / b = %d\n", a / b);
    }
    else
    {
        perror("Cannot divide by zero!");
    }
}

void cube_then_add_hof(double (*p_get)(int), int b)
{
    printf("using higher order function: b^3 + b = %0.1f \n", p_get(b) + b);
}

int main()
{
    printf("main address is %p\n", main);

    double (*p_cube)(int a) = cube;
    printf("Cube CB result is %.1f\n", p_cube(3));

    void (*arr_of_functions[])(int, int) = {add, subtract, multiply, subtract};
    int len = CALC_ARRAY_LEN(arr_of_functions);
    for (int i = 0; i < len; i++)
    {
        arr_of_functions[i](2, i);
    }
    puts("");

    cube_then_add_hof(p_cube, 5);

    puts("");
    return EXIT_SUCCESS;
}
