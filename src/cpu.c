#include "cpu.h"

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
            case 0b01100001: // MOV %RX, C
                #ifdef DEBUG
                printf("Command is MOV CONSTANT [%s][%s]\n", __reg_map[(int)arg1], __reg_map[(int)arg2]);
                #endif

                StoreRegister(arg1, arg2, registers);
            break;
            case 0b001000000: // CMP %RX, %RY
                #ifdef DEBUG
                printf("Command is CMP [%s][%s]\n", __reg_map[(int)arg1], __reg_map[(int)arg2]);
                #endif

                // Store to CR, arg1-arg2, LEFT-RIGHT.
                StoreRegister(0b00010111, (LoadRegister(arg1, registers) - LoadRegister(arg2, registers)), registers);
            break;
            case 0b001000001: // CMP %RX, C
                #ifdef DEBUG
                printf("Command is CMP CONSTANT [%s][%s]\n", __reg_map[(int)arg1], __reg_map[(int)arg2]);
                #endif

                // Store to CR, arg1-C.
                StoreRegister(0b00010111, (LoadRegister(arg1, registers) - arg2), registers);
            break;
            case 0b001010000: // BR C
                #ifdef DEBUG
                printf("Command is BR [%s]\n", __reg_map[(int)arg1]);
                #endif

                // BRANCH jmps absolutely and not relatively to PC, so adjust "PC"
                i = arg1; // 나느ㄷ아 코레 . . . 
            break;

        }

        registers[27] = i; // PC++
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
