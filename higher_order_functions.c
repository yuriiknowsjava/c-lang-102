#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

typedef void (*DoubleConsumer)(double);
typedef double (*DoubleSupplier)();
typedef double (*DoubleFn)(double);
typedef double (*DoubleBiFn)(double, double);

typedef double (*Double)(DoubleBiFn, double);

typedef struct DoubleBiFnClojure
{
    DoubleBiFn fn;
    double val;
} DoubleBiFnClojure;

double supply_double()
{
    return 42.0;
}

void consumer_double(double x)
{
    printf("Consumed double is %.3f", x);
}

double identity_double(double x)
{
    return x;
}

double add_doubles(double a, double b)
{
    return a + b;
}

double somewhat_partial(DoubleBiFnClojure cj, double a)
{
    return cj.fn(cj.val, a);
}

int main()
{
    DoubleSupplier s = supply_double;
    DoubleConsumer c = consumer_double;
    DoubleFn f1 = identity_double;
    DoubleBiFn f2 = add_doubles;

    DoubleBiFnClojure cj = {.fn = add_doubles, .val = 5};
    assert(somewhat_partial(cj, 4) == 9);

    return EXIT_SUCCESS;
}
