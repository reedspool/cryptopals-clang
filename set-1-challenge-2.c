#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *hexInputA = "1c0111001f010100061a024b53535009181c";
  char *hexInputB = "686974207468652062756c6c277320657965";
  char *expectedHexOutput = "746865206b696420646f6e277420706c6179";
  char *binaryInputA = hexDecode(hexInputA);
  char *binaryInputB = hexDecode(hexInputB);
  char *binaryExpectedOutput = hexDecode(expectedHexOutput);
  // Can't depend on strlen(binaryInputA) because it has null bytes in the
  // middle!
  int inputLength = strlen(hexInputA) / 2;
  char *binaryOutput = malloc(inputLength + 1);
  binaryOutput[inputLength] = 0x00;

  for (int i = 0; i < inputLength; i++) {
    binaryOutput[i] = binaryInputA[i] ^ binaryInputB[i];
  }

  char *output = hexEncode(binaryOutput);
  int isCorrect = strcmp(expectedHexOutput, output) == 0;
  printf("Binary input: A %s, B %s\n", binaryInputA, binaryInputB);
  printf("Expected hex output: %s, binary %s\n", expectedHexOutput,
         binaryExpectedOutput);
  printf("hex output: %s, binary matches? %s\n", output,
         strcmp(binaryOutput, binaryExpectedOutput) == 0 ? "Yes" : "no");
  printf("Correct? (hex ascii matches) %s\n", isCorrect ? "Yes" : "No");

  return 0;
}
