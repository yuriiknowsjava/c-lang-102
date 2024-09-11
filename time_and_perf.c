#include <time.h>
#include <stdio.h>

double elapsed_time_seconds(clock_t start, clock_t end)
{
    return (end - start) / (double)CLOCKS_PER_SEC;
}

void heavy_compulation()
{
    for (int i = 0; i < 1000000000; i++)
    {
        // do nothing
    }
}

int main()
{
    time_t current_time = time(NULL);
    printf("Current time: %ld\n", current_time);

    clock_t start, end = 0;

    start = clock();
    heavy_compulation();
    end = clock();

    double elapsed_time_s = elapsed_time_seconds(start, end);
    printf("Elapsed time %.3f(s)\n", elapsed_time_s);
}
