#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

#define BASE_10 10

int main()
{
    {
        char str_num[] = "4";
        char *pend = NULL;
        printf("Is first chart a num: %s\n", isdigit(str_num) ? "true" : "false");

        long num = strtol(str_num, &pend, BASE_10);
        printf("Converting str (%s)\n", str_num);
        printf("\terrno: %d %s", errno, errno == ERANGE ? "ERANGE error occurred" : "");
        printf("\t%s\n", str_num == pend ? "cannot parse string" : "");
    }

    puts("Converting an invalid str");
    {
        char invalid_num[] = "www.google.com";
        char *pend = NULL;
        strtol(invalid_num, &pend, BASE_10);
        if (invalid_num == pend)
        {
            printf("\tInvalid string!\n");
        }
    }

    puts("Converting too long num");
    {
        char too_long_num[] = "100000000000000000000000000000000000000000000000";
        char *pend = NULL;
        strtol(too_long_num, &pend, BASE_10);
        if (errno != 0)
        {
            printf("\tThe number is too large\n");
        }
    }

    puts("Parse multiple string");
    {
        errno = 0;
        char nums[] = "10 -20 54 42";
        char *pstart = nums;
        char *pend = NULL;
        while (pstart[0] != '\0')
        {
            long n = strtol(pstart, &pend, BASE_10);
            if (errno == 0 && pend != pstart)
            {
                printf("%ld ", n);
            }
            pstart = pend;
        }
        puts("");
    }
}
