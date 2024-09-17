#include "numconv.h"
#include <stdio.h>

int any_to_int(char *str, int mult_val, int (*f)(char))
{
    int final_val = 0;
    int pos = 0;
    // Magic number!
    const int asc_int_diff = 48;
    // ASCII for 'A' is 65, but since 'A' is 10 in decimal, we need to subtract that from our diff val
    const int upper_hex_diff = 55;
    // Same story as above, only 'a' == 97
    const int lower_hex_diff = 87;
    char digit = str[pos];
    while (digit != '\0')
    {
        if ((*f)(digit))
        {
            // printf("%c is a valid digit\n", digit);
            int int_val = digit - asc_int_diff;
            if (mult_val == 16)
            {
                if (digit >= 'a')
                {
                    int_val = digit - lower_hex_diff;
                }
                else if (digit >= 'A')
                {
                    int_val = digit - upper_hex_diff;
                }
            }
            final_val *= mult_val;
            final_val += int_val;
        }
        digit = str[++pos];
        // printf("Value at the end of iteration: %d\n", final_val);
    }

    return final_val;
}

int dec_to_int(char str[])
{
    return any_to_int(str, 10, is_digit);
}
int bin_to_int(char str[])
{
    return any_to_int(str, 2, is_bin_digit);
}
int hex_to_int(char str[])
{
    return any_to_int(str, 16, is_hex_digit);
}
int oct_to_int(char str[])
{
    return any_to_int(str, 8, is_oct_digit);
}

void int_to_any(int org_int, char str[], int next_digit_num)
{
    // same story as in any_to_int()
    const int lower_hex_diff = 87;
    int remainder = org_int;
    char temp_array[255];
    int entries = 0;
    int negative = org_int < 0;
    // printf("Negative? %d\n", negative);
    if (negative)
    {
        org_int *= -1;
    }
    int temp_hex_count = 0;
    do
    {
        int next_val_int = remainder % next_digit_num;
        if (next_digit_num == 16)
        {
            if (next_val_int < 10)
            {
                temp_array[entries++] = next_val_int + '0'; // Convert 0-9 to '0'-'9'
            }
            else
            {
                temp_array[entries++] = (next_val_int - 10) + 'a'; // Convert 10-15 to 'A'-'F'
            }
        }
        else
        {
            temp_array[entries++] = '0' + next_val_int;
        }
        remainder /= next_digit_num;
    } while (remainder);

    int i = 0;
    for (; i < entries; i++)
    {
        str[entries - i - 1] = temp_array[i];
    }

    str[i] = '\0';
}

void int_to_dec(int num, char str[])
{
    int_to_any(num, str, 10);
}
void int_to_bin(int num, char str[])
{
    int_to_any(num, str, 2);
}
void int_to_hex(int num, char str[])
{
    int_to_any(num, str, 16);
}
void int_to_oct(int num, char str[])
{
    int_to_any(num, str, 8);
}

int is_digit(char c)
{
    return '0' <= c && c <= '9';
}
int is_bin_digit(char c)
{
    return c == '0' || c == '1';
}
int is_hex_digit(char c)
{
    return ('0' <= c && c <= '9') || ('A' <= c && c <= 'F') || ('a' <= c && c <= 'f');
}
int is_oct_digit(char c)
{
    return '0' <= c && c <= '7';
}