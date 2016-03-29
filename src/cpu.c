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
    // Construct registers
    char *registers = (char *)calloc(27, sizeof(char));

    // Parse binary file 3 by 3 bytes
    for(short i = 0; i < strlen(binaryFile); i = i+3) {
        switch(binaryFile[i]) {
            case 0b01100000: // MOV %RX, %RY
                #ifdef DEBUG
                printf("Command is MOV [%s][%s]", __reg_map[binaryFile[i+1]], __reg_map[binaryFile[i+2]]);
                #endif
            break;
        }
    }

    return registers;
}

char LoadRegister(char offset, char *registers) {
    // Check offset
    if(offset >= 0b00010110) {
        printf("accessing PC/CR violated.~\n");
        return 0x00;
    }

    // Just grab and return
    return registers[(int)offset];
}

char StoreRegister(char toRegister, char value, char *registers) {
    // TODO: check offsets... to see if we can write..?
    

    registers[(int)toRegister] = value;
    return 
}
