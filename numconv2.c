#include <stdio.h>

#include "numconv.h"

int dec_to_int(char str[]) {
  int final_val = 0;
  int pos = 0;

  char digit = str[pos];
  while (digit != '\0') {
    if (is_digit(digit)) {
      // Multiply by 10 to adjust for the next digit's higher "value"
      final_val *= 0b1010;
      // We can safely look at all the first 4 bits, since only '0'-'9' will pass is_digit()
      final_val += (digit & 0b1111);
    }
    digit = str[++pos];
  }

  return final_val;
}

int bin_to_int(char str[]) {
  int final_val = 0;
  int pos = 0;

  char digit = str[pos];
  while (digit != '\0') {
    if (is_bin_digit(digit)) {
      final_val <<= 0b1;
      final_val += (digit & 0b1);
    }
    digit = str[++pos];
  }

  return final_val;
}

int hex_to_int(char str[]) {
  int final_val = 0;
  int pos = 0;

  char digit = str[pos];
  while (digit != '\0') {
    if (is_hex_digit(digit)) {
      int temp = (digit & 0b1111);
      // A-F will be converted to 1-6. So add 9
      if (digit > '9') {
        temp += 0b1001;
      }
      final_val <<= 0b100;
      final_val += temp;
    }
    digit = str[++pos];
  }

  return final_val;
}

int oct_to_int(char str[]) {
  int final_val = 0;
  int pos = 0;
  char digit = str[pos];

  while (digit != '\0') {
    if (is_oct_digit(digit)) {
      final_val <<= 0b11;
      final_val += (digit & 0b111);
    }
    digit = str[++pos];
  }

  return final_val;
}


void int_to_dec(int num, char str[]) {
  int index = 0;
  char temp_array[33];
  do {
    // 0b110000 == 48
    // Difference between 0 and '0' is 48 (0b110000) in ascii decimal
    // num % 0b1010 = the next digit
    int ascii_val = num % 0b1010 + 0b110000;
    // printf("ascii val: %d.\n", ascii_val);
    temp_array[index++] = ascii_val;
    num /= 10;
    // 123 == 0111 1011
  } while (num);

  // Reverse array
  for (size_t i = 0; i < index; i++) {
    str[index - i - 1] = temp_array[i];
  }
  str[index] = '\0';
}

void int_to_bin(int num, char str[]) {
  int index = 0;
  char temp_array[33];
  do {
    // 0b110000 == 48
    // Difference between 0 and '0' is 48 in ascii decimal
    // (num & 1) will be either 0 or 1
    // 48 is then "added"
    temp_array[index++] = (num & 0b1) | 0b110000;
    num >>= 1;
  } while (num);

  // Reverse array
  for (size_t i = 0; i < index; i++) {
    str[index - i - 1] = temp_array[i];
  }
  str[index] = '\0';
}

// void int_to_bin(int num, char str[]) { int_to_any(num, str, 2); }
void int_to_hex(int num, char str[]) {
  int index = 0;
  char temp_array[33];
  do {
    // Value between 0 and 15
    int masked_val = num & 0b1111;
    // 0b110000 == '0'
    int mask_to_ascii_val = 0b110000;
    // In case the value is above 9, we change the ascii mask to 'a' - 10, since masked_val will be 0-6 + 10.
    // Alternative would be to subtract 10 from the masked val
    if (masked_val > 0b1001) {
      // 0b1100001 == 'a'
      mask_to_ascii_val = 0b1100001 - 0b1010;
    }

    int final = masked_val + mask_to_ascii_val;
    temp_array[index++] = final;
    // Shift the original number 4 bits, since one hex value is 4 bits
    // Same as dividing by 2^4 == 16
    num >>= 4;

  } while (num);

  // Reverse array
  for (size_t i = 0; i < index; i++) {
    str[index - i - 1] = temp_array[i];
  }
  str[index] = '\0';
}

void int_to_oct(int num, char str[]) {
  int index = 0;
  char temp_array[33];
  do {
    temp_array[index++] = (num & 0b111) | 0b110000;
    num >>= 3;
  } while (num);

  // Reverse array
  for (size_t i = 0; i < index; i++) {
    str[index - i - 1] = temp_array[i];
  }
  str[index] = '\0';
}

int is_digit(char c) { return '0' <= c && c <= '9'; }
int is_bin_digit(char c) { return c == '0' || c == '1'; }
int is_hex_digit(char c) {
  return ('0' <= c && c <= '9') || ('A' <= c && c <= 'F') ||
         ('a' <= c && c <= 'f');
}
int is_oct_digit(char c) { return '0' <= c && c <= '7'; }