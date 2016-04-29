#ifndef __CPU_H
    #define __CPU_H
    char *HandleInstruction(char *binaryFile, int *bufferSize);
    char LoadRegister(char offset, char *registers);
    int StoreRegister(char toRegister, char offset, char *registers);
#endif
