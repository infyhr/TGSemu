#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "cpu.h"

char *ReadBinary(char fileName[32], int *);

int main(int argc, char **argv) {
    char *binaryFile;
    int bufferSize;

    if(argc != 2) {
        printf("Usage: %s <binary file.bin>\n", argv[0]);
        return -1;
    }

    // Grab the binary file
    binaryFile = ReadBinary(argv[1], &bufferSize);
    if(!binaryFile) return -1;

    // Use cpu.c to construct a register set and then after here do the loop and update the screen with screen.c
    //printf("%s", binaryFile);
    char *test = HandleInstruction(binaryFile, bufferSize);
    /*for(char i = 0; i < 27; i++) {
        printf("%c\n", test[i]);
    }*/

    free(binaryFile); binaryFile = NULL;
    return 0;
}

char *ReadBinary(char fileName[32], int *bufferSize) {
    FILE *pFile;
    long lSize;
    char *buffer;
    size_t result;

    // Open the file
    pFile = fopen(fileName, "rb");
    if(!pFile) {
        printf("Cannot fopen() the file.\n");
        return NULL;
    }

    // Get the file size
    fseek(pFile, 0, SEEK_END);
    lSize = ftell(pFile);
    rewind(pFile);

    // Allocate memory to contain the whole file.
    buffer = (char*) malloc(sizeof(char)*lSize);
    if(!buffer) {
        printf("Failed to allocate the memory.\n");
        return NULL;
    }

    // Copy the file into the buffer.
    result = fread(buffer, 1, lSize, pFile);

    /*
    infy@storm ~/Projects/tgs $ xxd -b hi.bin
    00000000: 01100000 00000000 00010000 00010000 00000000 00010001  `.....
    00000006: 01000001 00000000 00000000 01010100 00001001 00000000  A..T..
    0000000c: 01100001 00010010 00000000 01100001 00010011 00000000  a..a..
    00000012: 01100001 00010100 00000000 01100001 00010101 00000000  a..a..
    00000018: 01010000 00000000 00000000 01100001 00010011 00000110  P..a..
    0000001e: 01100001 00010100 01110100 01010000 00000000 00000000  a.tP..

    6 * (8bits) * 6 -> strlen is 36.
    */
    #ifdef DEBUG
        printf("Expected filesize %lu, got filesize %lu\n", lSize, result);
    #endif

    // Check whether it's % 3 since every instruction is *exactly* 3 bytes
    if(result % 3 != 0) {
        printf("Corrupted ROM? Need 3 byte instructions, got total of %lu???", result % 3);
        return NULL;
    }

    if(result != lSize) {
        printf("File corrupted? Number of bytes do not match...\n");
        return NULL;
    }

    // Close the file and return what we have read.
    fclose(pFile);
    *bufferSize = result;
    return buffer;
}
