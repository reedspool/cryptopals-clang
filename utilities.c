#include "utilities.h"
#include <stdlib.h>
#include <string.h>

char *hexDecode(char *hexInput) {
  // 1 char is 8 bits. hexInput represents 4 bits of information per char. So we
  // only need half that length when it's unpacked
  int hexLength = strlen(hexInput);

  int binaryLength = hexLength / 2;
  char *binaryInput = malloc((binaryLength + 1) * sizeof(char));
  binaryInput[binaryLength] = 0x00;
  int i;
  for (i = 0; i < hexLength; i += 2) {
    int j;
    // If j >= 10, then it's actually a letter, and we need to shift up the
    // ASCII table to the start of the lowercase characters
    j = hexInput[i] - '0';
    char first4Bits = j < 10 ? j : (j - ('a' - '0') + 10);
    j = hexInput[i + 1] - '0';
    char second4Bits = j < 10 ? j : (j - ('a' - '0') + 10);

    binaryInput[i / 2] = (first4Bits << 4) | second4Bits;
  }

  return binaryInput;
}

char *hexEncode(char *binaryInput) {
  // 1 char is 8 bits. hexInput represents 4 bits of information per char. So we
  // only need half that length when it's unpacked
  int binaryLength = strlen(binaryInput);
  int hexLength = binaryLength * 2;

  char *hexInput = malloc((hexLength + 1) * sizeof(char));
  hexInput[hexLength] = 0x00;
  int i;
  for (i = 0; i < binaryLength; i++) {
    int j = binaryInput[i] >> 4;
    int k = binaryInput[i] & 0x0f;
    // If j >= 10, then it's actually a letter, and we need to shift up the
    // ASCII table to the start of the lowercase characters
    hexInput[(i * 2)] = j < 10 ? j + '0' : ((j - 10) + 'a');
    hexInput[(i * 2) + 1] = k < 10 ? k + '0' : ((k - 10) + 'a');
  }

  return hexInput;
}
