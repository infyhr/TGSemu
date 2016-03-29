#include "cpu.h"

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

char *HandleInstruction(char *binaryFile) {
    char arg1, arg2;
    // Construct registers
    char *registers = (char *)calloc(27, sizeof(char));

    // Parse binary file 3 by 3 bytes
    for(short i = 0; i < strlen(binaryFile); i = i+3) {
        arg1   = (int)binaryFile[i+1];
        arg2   = (int)binaryFile[i+2];

        switch(binaryFile[i]) {
            case 0b01100000: // MOV %RX, %RY
                #ifdef DEBUG
                printf("Command is MOV [%s][%s]\n", __reg_map[(int)arg1], __reg_map[(int)arg2]);
                #endif

                StoreRegister(arg1, LoadRegister(arg2, registers), registers);
            break;
        }
    }

    #ifdef DEBUG
    printf("printing registers...\n");
    for(short i = 0; i < 27; i++) {
        printf("%s: %c (%d)\n", __reg_map[i], registers[i], (int)registers[i]);
    }
    #endif

    return registers;
}

char LoadRegister(char offset, char *registers) {
    // Check offset
    if(offset >= 0b00010110) {
        printf("accessing PC/CR violated.~\n");
        return 0x00;
    }

    // Just grab and return
    #ifdef DEBUG
    printf("Return %c from offset %c  (%d), register %s\n", registers[(int)offset], offset, (int)offset, __reg_map[(int)offset]);
    #endif
    return registers[(int)offset];
}

int StoreRegister(char toRegister, char value, char *registers) {
    // TODO: check offsets... to see if we can write..?

    registers[(int)toRegister] = value;
    return 1;
}
