#include <stdio.h>

#include "numconv.h"

// USED IN V1
// int any_to_int(char *str, int mult_val, int (*validationFunc)(char)) {
//   int final_val = 0;
//   int pos = 0;
//   // Magic number!
//   const int asc_int_diff = 48;
//   // ASCII for 'A' is 65, but since 'A' is 10 in decimal, we need to subtract
//   // that from our diff val
//   const int upper_hex_diff = 55;
//   // Same story as above, only 'a' == 97
//   const int lower_hex_diff = 87;
//   char digit = str[pos];
//   while (digit != '\0') {
//     if ((*validationFunc)(digit)) {
//       // printf("%c is a valid digit\n", digit);
//       int int_val = digit - asc_int_diff;
//       if (mult_val == 16) {
//         if (digit >= 'a') {
//           int_val = digit - lower_hex_diff;
//         } else if (digit >= 'A') {
//           int_val = digit - upper_hex_diff;
//         }
//       }
//       final_val *= mult_val;
//       final_val += int_val;
//     }
//     digit = str[++pos];
//     // printf("Value at the end of iteration: %d\n", final_val);
//   }

//   return final_val;
// }

int dec_to_int(char str[]) {
  int final_val = 0;
  int pos = 0;

  char digit = str[pos];
  while (digit != '\0') {
    if (is_digit(digit)) {
      final_val *= 10;
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
      // We only care about the last digit. Then we multiply by how far we are
      // in the string +1, since that's how the digit's value's progress
      final_val <<= 1;
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
        temp += 9;
      }
      final_val <<= 4;
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
      final_val <<= 3;
      final_val += (digit & 0b111);
    }
    digit = str[++pos];
  }

  return final_val;
}

// USED IN V1

// void int_to_any(int org_int, char str[], int next_digit_num) {
//   // same story as in any_to_int()
//   const int lower_hex_diff = 87;
//   int remainder = org_int;
//   char temp_array[255];
//   int entries = 0;
//   int negative = org_int < 0;
//   // printf("Negative? %d\n", negative);
//   if (negative) {
//     org_int *= -1;
//   }
//   int temp_hex_count = 0;
//   do {
//     int next_val_int = remainder % next_digit_num;
//     if (next_digit_num == 16) {
//       if (next_val_int < 10) {
//         temp_array[entries++] = next_val_int + '0';  // Convert 0-9 to '0'-'9'
//       } else {
//         temp_array[entries++] =
//             (next_val_int - 10) + 'a';  // Convert 10-15 to 'A'-'F'
//       }
//     } else {
//       temp_array[entries++] = '0' + next_val_int;
//     }
//     remainder /= next_digit_num;
//   } while (remainder);

//   int i = 0;
//   for (; i < entries; i++) {
//     str[entries - i - 1] = temp_array[i];
//   }

//   str[i] = '\0';
// }

void int_to_dec(int num, char str[]) {
  int index = 0;
  char temp_array[33];
  do {
    // 0b110000 == 48
    // Difference between 0 and '0' is 48 in ascii decimal
    // (num & 1) will be either 0 or 1
    // 48 is then "added"
    int ascii_val = num % 10 + 0b110000;
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
      mask_to_ascii_val = 0b1100001 - 10;
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