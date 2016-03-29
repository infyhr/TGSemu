#ifndef __CPU_H
    #define __CPU_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <string.h>

    char *HandleInstruction(char *binaryFile);
    char LoadRegister(char offset, char *registers);
    char StoreRegister(char toRegister, char offset, char *registers);
#endif
