#include "numconv.h"
#include <stdio.h>
#include <string.h>

void run_tests()
{
    int wrongs_corrects[] = {0, 0};

    char bin_str[] = "102";
    int int_from_bin = bin_to_int(bin_str);
    wrongs_corrects[check_result(bin_str, 2, bin_to_int, "binary")]++;

    char hex_str[] = "Ab9";
    wrongs_corrects[check_result(hex_str, 2745, hex_to_int, "hex")]++;
    strcpy(hex_str, "00a");
    wrongs_corrects[check_result(hex_str, 10, hex_to_int, "hex")]++;

    char oct_string[255] = "94329";
    wrongs_corrects[check_result(oct_string, 282, oct_to_int, "octal")]++;
    strcpy(oct_string, "00329");
    wrongs_corrects[check_result(oct_string, 26, oct_to_int, "octal")]++;

    char dec_string[255] = "1234";
    wrongs_corrects[check_result(dec_string, 1234, dec_to_int, "decimal")]++;
    strcpy(dec_string, "012340");
    wrongs_corrects[check_result(dec_string, 12340, dec_to_int, "decimal")]++;

    

    printf("\nRan %d tests:\n", (wrongs_corrects[0] + wrongs_corrects[1]));
    printf("Passed: %d\n", wrongs_corrects[1]);
    printf("Failed: %d\n", wrongs_corrects[0]);
}

int check_result(char *str, int expected, int (*f)(char *), char *num_type)
{
    int result = (*f)(str);
    if (result != expected)
    {
        printf("Test FAILED for %s. Expected: %d. Actual: %d \n", num_type, expected, result);
        return 0;
    }
    return 1;
}