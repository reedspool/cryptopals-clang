#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// First index is 'a'
double expectedFrequencies[] = {
    0.082,  0.015,  0.028, 0.043,  0.127, 0.022,  0.02,  0.061,   0.07,
    0.0015, 0.0077, 0.04,  0.024,  0.067, 0.075,  0.019, 0.00095, 0.06,
    0.063,  0.091,  0.028, 0.0098, 0.024, 0.0015, 0.02,  0.00074};

int main() {
  char *hexInput =
      "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  char *binaryInput = hexDecode(hexInput);
  // Can't depend on strlen(binaryInputA) because it has null bytes in the
  // middle!
  int inputLength = strlen(hexInput) / 2;
  /* char *results[0xffff] = {0}; */

  double minScore = 99999;
  char *minScoreBinary;
  for (int j = 0; j < 0x7f; j++) {
    double score = 0;
    char *f = malloc(inputLength + 1);
    f[inputLength] = 0x00;

    // Fill the test array with one byte repeated
    for (int i = 0; i < inputLength; i++) {
      f[i] = j;
    }
    char *binaryOutput = malloc(inputLength + 1);
    binaryOutput[inputLength] = 0x00;

    for (int i = 0; i < inputLength; i++) {
      binaryOutput[i] = binaryInput[i] ^ f[i];
    }
    int length = 26;
    int *histogram = malloc((length * sizeof(int)) + 1);
    for (int i = 0; i < inputLength; i++) {
      int character = binaryOutput[i];
      if (character >= 'A' && character <= 'Z') {
        histogram[character - 'A'] += 1;
      } else if (character >= 'a' && character <= 'z') {
        histogram[character - 'a'] += 1;
      } else {
        score += 1;
      }
    }

    for (int i = 0; i < length; i++) {
      double freq = histogram[i] / (float)inputLength;
      double difference = expectedFrequencies[i] - freq;
      score += difference < 0 ? -difference : difference;
    }

    if (score < minScore) {
      minScore = score;
      minScoreBinary = binaryOutput;
    }

    printf("#%d,  Binary output %s, score %f\n", j, binaryOutput, score);
  }

  printf("Min score %f, binary %s\n", minScore, minScoreBinary);

  return 0;
}
