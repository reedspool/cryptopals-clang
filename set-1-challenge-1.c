#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *hexInput = "49276d206b696c6c696e6720796f757220627261696e206c696b6520612"
                   "0706f69736f6e6f7573206d757368726f6f6d";
  char *expectedBase64Output = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29"
                               "ub3VzIG11c2hyb29t";
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

    printf("i is %d, c is %c, input %s\n", i / 2,
           (first4Bits << 4) | second4Bits, binaryInput);
    binaryInput[i / 2] = (first4Bits << 4) | second4Bits;
  }
  printf("input %s\n", binaryInput);

  char *base64Table =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  // Base64 output length is the input binary length / 6, padded to the nearest
  // multiple of 4
  int binaryBitLength = binaryLength * (sizeof(char));
  int outputLength = (binaryBitLength / 6) + ((binaryBitLength / 6) % 8);
  char *output = malloc((outputLength + 1));
  output[outputLength] = 0x00;

  char previousBits;
  int nextOutput = 0;
  for (i = 0; i < binaryLength; i++) {
    switch (i % 3) {
    case 0:
      output[nextOutput++] = base64Table[(binaryInput[i] >> 2) & 0x3f];
      previousBits = (binaryInput[i] << 4);
      break;
    case 1:
      output[nextOutput++] =
          base64Table[(previousBits | binaryInput[i] >> 4) & 0x3f];
      previousBits = binaryInput[i] << 2;
      break;
    case 2:
      output[nextOutput++] =
          base64Table[(previousBits | binaryInput[i] >> 6) & 0x3f];
      output[nextOutput++] = base64Table[binaryInput[i] & 0x3f];
      previousBits = 0; // Unused
      break;
    }
    printf("Binary length %d, i %d, prev masked %c #%d\n", binaryLength, i,
           previousBits & 0x3f, previousBits & 0x3f);
  }

  if (binaryLength % 3 == 0) {
  } else {
    printf("Binary length %d, i %d, prev %c #%d, prev masked 0x3f %c #%d\n",
           binaryLength, i, previousBits, previousBits, previousBits & 0x3f,
           previousBits & 0x3f);
    output[nextOutput++] = base64Table[previousBits & 0x3f];
    while (nextOutput % 4 != 0) {
      output[nextOutput++] = '=';
    }
  }

  int isCorrect = strcmp(expectedBase64Output, output) == 0;
  printf("Binary input: %s\n", binaryInput);
  printf("Expected ASCII output: %s\n", expectedBase64Output);
  printf("ASCII output: %s\n", output);
  printf("Correct? %s\n", isCorrect ? "Yes" : "No");

  return 0;
}
