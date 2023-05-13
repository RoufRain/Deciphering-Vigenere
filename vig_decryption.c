#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_LENGTH 52 // length of key in bytes

int main() {
    unsigned char ch;
    FILE *fpIn, *fpOut, *fpKey;
    int i;
    unsigned char key[KEY_LENGTH] = {0}; // initialize key with zeros

    // read key from file
    fpKey = fopen("key.txt", "r");
    if (fpKey == NULL) {
        perror("Error opening key file");
        exit(1);
    }
    if (fread(key, sizeof(unsigned char), KEY_LENGTH, fpKey) != KEY_LENGTH) {
        perror("Error reading key file");
        exit(1);
    }
    fclose(fpKey);

    fpIn = fopen("ctext.txt", "r");
    if (fpIn == NULL) {
        perror("Error opening input file");
        exit(1);
    }

    fpOut = fopen("dtext.txt", "w");
    if (fpOut == NULL) {
        perror("Error opening output file");
        exit(1);
    }

    i = 0;

    while (fscanf(fpIn, "%2hhx", &ch) != EOF) {
        fprintf(fpOut, "%c", ch ^ key[i % KEY_LENGTH]); // Logical XOR operation with key
        i++;
    }

    fclose(fpIn);
    fclose(fpOut);

    return 0;
}
