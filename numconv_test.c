#include "numconv.h"

#include <stdio.h>
#include <string.h>

void run_tests() {
  int wrongs_corrects[] = {0, 0};

  char bin_str[] = "102";
  int int_from_bin = bin_to_int(bin_str);
  wrongs_corrects[run_to_int_tests(bin_str, 2, bin_to_int, "binary")]++;

  char hex_str[] = "Ab9";
  wrongs_corrects[run_to_int_tests(hex_str, 2745, hex_to_int, "hex")]++;
  strcpy(hex_str, "00a");
  wrongs_corrects[run_to_int_tests(hex_str, 10, hex_to_int, "hex")]++;

  char oct_string[255] = "94329";
  wrongs_corrects[run_to_int_tests(oct_string, 282, oct_to_int, "octal")]++;
  strcpy(oct_string, "00329");
  wrongs_corrects[run_to_int_tests(oct_string, 26, oct_to_int, "octal")]++;

  char dec_string[255] = "1234";
  wrongs_corrects[run_to_int_tests(dec_string, 1234, dec_to_int, "decimal")]++;
  strcpy(dec_string, "012340");
  wrongs_corrects[run_to_int_tests(dec_string, 12340, dec_to_int, "decimal")]++;

  wrongs_corrects[run_from_int_tests(123, "123", int_to_dec, "decimal")]++;

  wrongs_corrects[run_from_int_tests(0, "0", int_to_hex, "hex")]++;
  wrongs_corrects[run_from_int_tests(9, "9", int_to_hex, "hex")]++;
  wrongs_corrects[run_from_int_tests(15, "f", int_to_hex, "hex")]++;
  wrongs_corrects[run_from_int_tests(123, "7b", int_to_hex, "hex")]++;
  wrongs_corrects[run_from_int_tests(282, "11a", int_to_hex, "hex")]++;
  wrongs_corrects[run_from_int_tests(854, "356", int_to_hex, "hex")]++;

  wrongs_corrects[run_from_int_tests(0, "0", int_to_oct, "octal")]++;
  wrongs_corrects[run_from_int_tests(7, "7", int_to_oct, "octal")]++;
  wrongs_corrects[run_from_int_tests(8, "10", int_to_oct, "octal")]++;
  wrongs_corrects[run_from_int_tests(11, "13", int_to_oct, "octal")]++;
  wrongs_corrects[run_from_int_tests(123, "173", int_to_oct, "octal")]++;

  wrongs_corrects[run_from_int_tests(0, "0", int_to_bin, "binary")]++;
  wrongs_corrects[run_from_int_tests(1, "1", int_to_bin, "binary")]++;
  wrongs_corrects[run_from_int_tests(2, "10", int_to_bin, "binary")]++;
  wrongs_corrects[run_from_int_tests(123, "1111011", int_to_bin, "binary")]++;

  printf("\nRan %d tests:\n", (wrongs_corrects[0] + wrongs_corrects[1]));
  printf("Passed: %d\n", wrongs_corrects[1]);
  printf("Failed: %d\n", wrongs_corrects[0]);
}

int run_to_int_tests(char *str, int expected, int (*f)(char *),
                     char *num_type) {
  int result = (*f)(str);
  if (result != expected) {
    printf("Test FAILED for %s. Expected: %d. Actual: %d. \n", num_type,
           expected, result);
    return 0;
  }
  return 1;
}

int run_from_int_tests(int val_in_int, char *expected,
                       void (*conv_f)(int, char *), char *num_type) {
  char buffer[510];
  (*conv_f)(val_in_int, buffer);

  // printf("Expected: %s. Actual: %s \n", expected, buffer);

  if (strcmp(buffer, expected) != 0) {
    printf("Test FAILED for %s. Expected: %s (int=%d). Actual: %s.\n", num_type,
           expected, val_in_int, buffer);
    return 0;
  }
  return 1;
}