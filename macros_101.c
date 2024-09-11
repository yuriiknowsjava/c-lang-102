#include <stdio.h>
#include <stdlib.h>

#define ARR_LEN 999

#define CALC_ARRAY_LEN(x) (sizeof((x)) / sizeof((x)[0]))
#define MAX(a, b) ((a) >= (b) ? (a) : (b))

// hash operator - converts to str
#define TO_STR(x) #x
#define DISPLAY_INT(x) printf(#x "=%d\n", x);
#define DISPLAY_FLOAT(x) printf(#x "=%f\n", x);
#define DISPLAY_GENERIC(x, placeholder) printf(#x "=" #placeholder "\n", x);

int main()
{
    printf("ARR_LEN macros expands to %d\n", ARR_LEN);

#undef ARR_LEN
#define ARR_LEN 10

    printf("After update; ARR_LEN macros expands to %d\n", ARR_LEN);
    printf("Current line number: %d\n", __LINE__);
    printf("Compilation date and time: %s %s\n", __DATE__, __TIME__);

    double doubles[] = {1, 2, 3, 4, 5, 6, 7};
    int len = CALC_ARRAY_LEN(doubles);
    printf("Length is calculated using macro %d\n", len);
    int a = 5;
    int b = 5;
    printf("Max using macro MAX(5, 5+1) == %d\n", MAX(a, b + 1));

    printf("Str formed by preprocessor %s\n", TO_STR(Hello C !));
    DISPLAY_FLOAT(5.5);
    DISPLAY_INT(6);
    DISPLAY_GENERIC('a', '%c');
    DISPLAY_GENERIC("Kek", "%s");

    puts("");
    return EXIT_SUCCESS;
}
