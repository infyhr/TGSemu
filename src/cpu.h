#ifndef __CPU_H
    #define __CPU_H
    int HandleInstruction(char, int, int, char *, int);
    char LoadRegister(char offset, char *registers);
    int StoreRegister(char toRegister, char offset, char *registers);
#endif
