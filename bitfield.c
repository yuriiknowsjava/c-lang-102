#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct LedStatus
{
    uint8_t led_1;
    uint8_t led_2;
    uint8_t led_3;
} LedStatus;

typedef struct LedStatusBitField
{
    uint8_t led_1 : 1; // number of bits used to represent status
    uint8_t led_2 : 1;
    uint8_t led_3 : 1;
    // the rest 5 bits are unused
} LedStatusBitField;

typedef struct ControlRegister
{
    uint32_t enable_device : 1;
    uint32_t reset_device : 1;
    uint32_t interrupt_enable : 1;
    uint32_t mode_select : 2;
    uint32_t enable_tx : 1;
    uint32_t enable_rx : 1;
    uint32_t payload : 25;
} ControlRegister;

typedef struct Permissions
{
    uint8_t read : 1;
    uint8_t write : 1;
    uint8_t execute : 1;
} Permissions;

typedef struct FilePermissions
{
    Permissions user;
    Permissions group;
    Permissions other;
} FilePermissions;

void print_bits(int len, uint8_t *data)
{
    for (int i = 0; i < len; i++)
    {
        uint8_t byte = data[i];
        for (int j = 0; j < 8; j++)
        {
            // select only most right bit, from the least significant bit to the most significant bit.
            printf("%d", (byte >> j) & 1);
        }
        printf(" ");
    }
    puts("");
}

/**
 * Bit fields access should be used with caution!
 * 1. Bit fields are platform dependent and you may have troubles porting code.
 * 2. Accessing individual bits requires additional computation.
 */

int main()
{
    LedStatus led_status = {.led_1 = 1, .led_2 = 0, .led_3 = 1};
    printf("LedStatus sizeof == %ld(bytes)\n", sizeof(led_status));
    print_bits(sizeof(led_status), (uint8_t *)&led_status);
    puts("");

    // it's a shame to waste 3 bytes just to represent 3 bool values
    // You can use bitfield to save memory
    LedStatusBitField led_bf = {.led_1 = 1, .led_2 = 0, .led_3 = 1};
    printf("LedStatus using Bit Fields sizeof == %ld(byte)\n", sizeof(led_bf));
    print_bits(sizeof(led_bf), (uint8_t *)&led_bf);
    puts("");

    ControlRegister cr = {
        .enable_device = 1,
        .reset_device = 0,
        .interrupt_enable = 1,
        .mode_select = 3,
        .enable_rx = 1,
        .enable_tx = 0,
        .payload = 555555,
    };
    printf("ControlRegister sizeof == %ld(byte)\n", sizeof(cr));
    print_bits(sizeof(cr), (uint8_t *)&cr);
    puts("");

    FilePermissions fp = {
        .user = {
            .read = 1,
            .write = 1,
            .execute = 1,
        },
        .group = {
            .read = 1,
            .write = 0,
            .execute = 0,
        },
        .other = {
            .read = 0,
            .write = 0,
            .execute = 0,
        },
    };
    printf("FilePermissions sizeof == %ld(byte)\n", sizeof(fp));
    print_bits(sizeof(fp), (uint8_t *)&fp);

    puts("");
    return EXIT_SUCCESS;
}
