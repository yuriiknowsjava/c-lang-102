#include <stdio.h>
#include <stdlib.h>

enum Menu
{
    COFFEE = 1, // if we don't want zero based enum
    TEA,
    JUICE,
    BEER,
    WINE,
};
typedef enum Menu Menu; // it's a good practice to keep struct/enum name same as typedef name.
// sometimes people use "_t" suffix, but it's only common for some system libs.

int main()
{
    enum Menu x = COFFEE;
    Menu my_choice = JUICE;
    printf("my choice is %d\n", my_choice);
    return EXIT_SUCCESS;
}
