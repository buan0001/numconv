#ifndef NUMCONV_H
#define NUMCONV_H

// Conversion functions
int any_to_int(char *str, int mult_val, int (*f)(char));
// All of these just call any_to_int with different variables
int dec_to_int(char str[]);
int bin_to_int(char str[]);
int hex_to_int(char str[]);
int oct_to_int(char str[]);

void int_to_dec(int num, char str[]);
void int_to_bin(int num, char str[]);
void int_to_hex(int num, char str[]);
void int_to_oct(int num, char str[]);

// Check functions
int is_digit(char c);
int is_bin_digit(char c);
int is_hex_digit(char c);
int is_oct_digit(char c);


// Tests
int check_result(char *str, int expected, int (*f)(char*), char *num_type);
void run_tests();

#endif