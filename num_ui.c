#include <stdio.h>
#include "numconv.h"
int main()
{
    run_tests();
    while (1)
    {

        printf("Enter a number type to convert from:\n");
        printf("(d) for decimal\n");
        printf("(o) for octal\n");
        printf("(h) for hex\n");
        printf("(b) for binary\n");
        printf("(x) to exit\n");
        char num_type;
        scanf(" %c", &num_type);
        if (num_type == 'x' || num_type == 'X'){
            return 0;
        }

        printf("Now enter the value you want to convert: ");
        char str_val[255];
        scanf(" %s", &str_val);

        printf("You entered: %s\n", str_val);

        int int_val;
        switch (num_type)
        {
        case 'd':
            int_val = dec_to_int(str_val);
            break;
        case 'h':
            int_val = hex_to_int(str_val);
            break;
        case 'o':
            int_val = oct_to_int(str_val);
            break;
        case 'b':
            int_val = bin_to_int(str_val);
            break;

        default:
            printf("Invalid number type\n");
            break;
        }

        printf("Int val: %d\n", int_val);
        char buffer[510];
        int_to_dec(int_val, buffer);
        printf(" in decimal string: %s\n", buffer);

        int_to_bin(int_val, buffer);
        printf(" in binary string: %s\n", buffer);

        int_to_oct(int_val, buffer);
        printf(" in octal string: %s\n", buffer);

        int_to_hex(int_val, buffer);
        printf(" in hex string: %s\n", buffer);

    }
    return 0;
}
