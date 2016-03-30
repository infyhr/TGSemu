#ifndef __CPU_H
    #define __CPU_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <string.h>

    char *__reg_map[] = {
        "R0",
        "R1",
        "R2",
        "R3",
        "R4",
        "R5",
        "R6",
        "R7", // 8
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        "BA", // 16 0b00010000 <=> 0x10
        "BB",
        "D0",
        "D1",
        "D2",
        "D3",
        "PC",
        "CR"
    };

    char *HandleInstruction(char *binaryFile);
    char LoadRegister(char offset, char *registers);
    int StoreRegister(char toRegister, char offset, char *registers);
#endif
