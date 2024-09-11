#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
Use unions when you need to read the same date in more that one way.
For instance, you may want to read something as word-addressable or as byte-addressable.
*/
typedef union HardwareRegister
{
    struct bytes
    {
        uint8_t byte1;
        uint8_t byte2;
        uint8_t byte3;
        uint8_t byte4;
    } bytes;
    uint32_t word;
} HardwareRegister;

typedef struct Person
{
    // pointer are more versatile, but you've got to remember to cleanup memory.
    char *firstname;

    // it's less flexible and consumes more memory, but you don't need to think about freeing the memory.
    char lastname[64]; // you've got to specify the arr size!

    // flexible array member (array without defined length) should be the last member of the struct!
    double flexible_array_member[];
} Person;

Person *alloc_person(int flexible_arr_len)
{
    // 1. defining a pointer to struct and init it with NULL
    // 2. access would be flexible_array_member's first element
    // That's all to avoid hard-coding sizeof(double)
    size_t flexible_arr_el_size = sizeof(((Person *)0)->flexible_array_member[0]);
    Person *p_person = malloc(sizeof(Person) + flexible_arr_el_size * flexible_arr_len);
    if (p_person == NULL)
    {
        return NULL;
    }
    return p_person;
}

int main()
{
    char str[] = "Hello";   // str value points directly to the first element of the string
    char *p_astr = "Hello"; // p_astr value has the address to the first element of the string.
    // Additional variable for pointer is created

    str[0] = 'G'; // works
    printf("%s\n", str);

    // p_astr[0] = 'X'; // segmentation failure, because we try to set element through pointer in read only area
    // str = "Another str"; // compilation error - cannot reassign value of str[]
    p_astr = "Another str";

    Person person = {
        .firstname = "Slim",
        .lastname = "Shady",
    };
    printf("Person{firstname=%s, lastname=%s}\n", person.firstname, person.lastname);
    printf("sizeof(Person) == %ld(bytes) // 72 bytes: 8 bytes for a pointer, 64 for the char array\n", sizeof(Person));
    printf("sizeof(person.firstname) == %ld(bytes); sizeof(person.lastname) == %ld(bytes)\n",
           sizeof(person.firstname), sizeof(person.lastname));
    printf("sizeof(person.flexible_array_member) won't compile, flexible array member is not stored in the struct, ");
    printf("it's a placeholder!\n");
    puts("");

    person.firstname = "John";
    // person.firstname[0] = 'G'; // segmentation failure,
    // person.lastname = "Wick"; // compilation error
    memcpy(person.lastname, "Wick", sizeof(person.lastname) - 1); // same last char for \0
    printf("Person{firstname=%s, lastname=%s}\n", person.firstname, person.lastname);

    int fam_len = 3;
    Person *p_person = alloc_person(fam_len);
    if (p_person == NULL)
    {
        printf("cannot allocate person!");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < fam_len; i++)
    {
        p_person->flexible_array_member[i] = i;
        printf("fam[i] == %.1f \n", p_person->flexible_array_member[i]);
    }
    puts("");

    HardwareRegister hr = {.word = 0xAABBCCDD};
    printf("As word: %X\n", hr.word);
    printf("As bytes: %X %X %X %X\n", hr.bytes.byte4, hr.bytes.byte3, hr.bytes.byte2, hr.bytes.byte1);
    // lets change only one byte
    hr.bytes.byte3 = 0xFF;
    printf("after byte change: \n");
    printf("As word: %X\n", hr.word);
    printf("As bytes: %X %X %X %X\n", hr.bytes.byte4, hr.bytes.byte3, hr.bytes.byte2, hr.bytes.byte1);

    free(p_person);
    puts("");
    return EXIT_SUCCESS;
}
