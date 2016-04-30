#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"

const char *__reg_map[] = {
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

int HandleInstruction(char instruction, int arg1, int arg2, char *registers, int i) {
    /*arg1   = (int)binaryFile[i+1];
    arg2   = (int)binaryFile[i+2];*/

    switch(instruction) {
        case 0b01100000: // MOV %RX, %RY
            #ifdef DEBUG
            printf("Command is MOV [%s][%s]\n\r", __reg_map[(int)arg1], __reg_map[(int)arg2]);
            #endif

            StoreRegister(arg1, LoadRegister(arg2, registers), registers);
        break;
        case 0b01100001: // MOV %RX, C
            #ifdef DEBUG
            printf("Command is MOV CONSTANT [%s][%d]\n\r", __reg_map[(int)arg1], (int)arg2);
            #endif

            StoreRegister(arg1, arg2, registers);
        break;
        case 0b001000000: // CMP %RX, %RY
            #ifdef DEBUG
            printf("Command is CMP [%s][%s]\n\r", __reg_map[(int)arg1], __reg_map[(int)arg2]);
            #endif

            // Store to CR, arg1-arg2, LEFT-RIGHT.
            StoreRegister(0b00010111, (LoadRegister(arg1, registers) - LoadRegister(arg2, registers)), registers);
        break;
        case 0b001000001: // CMP %RX, C
            #ifdef DEBUG
            printf("Command is CMP CONSTANT [%s][%d]\n\r", __reg_map[(int)arg1], (int)arg2);
            #endif

            // Store to CR, arg1-C.
            StoreRegister(0b00010111, (LoadRegister(arg1, registers) - arg2), registers);
        break;
        case 0b001010000: // BR C
            #ifdef DEBUG
            printf("Command is BR [%s]\n\r", __reg_map[(int)arg1]);
            #endif

            // BRANCH jmps absolutely and not relatively to PC, so adjust "PC"
            i = (arg1*3)-3; // pseudo program counter.
            StoreRegister(0b00010110, i, registers);
        break;
        case 0b00010000: // ADD %RX, %RY
            #ifdef DEBUG
            printf("Command is ADD [%s][%s]\n\r", __reg_map[(int)arg1], __reg_map[(int)arg2]);
            #endif

            StoreRegister(arg1, (LoadRegister(arg1, registers) + LoadRegister(arg2, registers)), registers);
        break;
        case 0b00010001: // ADD %RX, C
            #ifdef DEBUG
            printf("Command is ADD CONSTANT [%s][%d]\n\r", __reg_map[(int)arg1], (int)arg2);
            #endif

            StoreRegister(arg1, (LoadRegister(arg1, registers) + arg2), registers);
        break;
        case 0b00010010: // SUB %RX, %RY
            #ifdef DEBUG
            printf("Command is SUB [%s][%s]\n\r", __reg_map[(int)arg1], __reg_map[(int)arg2]);
            #endif

            StoreRegister(arg1, (LoadRegister(arg1, registers) - LoadRegister(arg2, registers)), registers);
        break;
        case 0b00010011: // ADD %RX, C
            #ifdef DEBUG
            printf("Command is SUB CONSTANT [%s][%d]\n\r", __reg_map[(int)arg1], (int)arg2);
            #endif

            StoreRegister(arg1, (LoadRegister(arg1, registers) - arg2), registers);
        break;
        case 0b00100000: // LSH %RX, %RY
            #ifdef DEBUG
            printf("Command is LSH [%s][%s]\n\r", __reg_map[(int)arg1], __reg_map[(int)arg2]);
            #endif

            StoreRegister(arg1, (LoadRegister(arg1, registers) << LoadRegister(arg2, registers)), registers);
        break;
        case 0b00100001: // LSH %RX, C
            #ifdef DEBUG
            printf("Command is LSH CONSTANT [%s][%d]\n\r", __reg_map[(int)arg1], (int)arg2);
            #endif

            StoreRegister(arg1, (LoadRegister(arg1, registers) << arg2), registers);
        break;
        case 0b00100010: // RSH %RX, %RY
            #ifdef DEBUG
            printf("Command is RSH [%s][%s]\n\r", __reg_map[(int)arg1], __reg_map[(int)arg2]);
            #endif

            StoreRegister(arg1, (LoadRegister(arg1, registers) >> LoadRegister(arg2, registers)), registers);
        break;
        case 0b00100011: // RSH %RX, C
            #ifdef DEBUG
            printf("Command is RSH CONSTANT [%s][%d]\n\r", __reg_map[(int)arg1], (int)arg2);
            #endif

            StoreRegister(arg1, (LoadRegister(arg1, registers) >> arg2), registers);
        break;
        case 0b00110000: // AND %RX, %RY
            #ifdef DEBUG
            printf("Command is AND [%s][%s]\n\r", __reg_map[(int)arg1], __reg_map[(int)arg2]);
            #endif

            StoreRegister(arg1, (LoadRegister(arg1, registers) & LoadRegister(arg2, registers)), registers);
        break;
        case 0b00110001: // AND %RX, C
            #ifdef DEBUG
            printf("Command is AND CONSTANT [%s][%d]\n\r", __reg_map[(int)arg1], (int)arg2);
            #endif

            StoreRegister(arg1, (LoadRegister(arg1, registers) & arg2), registers);
        break;
        case 0b00110010: // OR %RX, %RY
            #ifdef DEBUG
            printf("Command is OR [%s][%s]\n\r", __reg_map[(int)arg1], __reg_map[(int)arg2]);
            #endif

            StoreRegister(arg1, (LoadRegister(arg1, registers) | LoadRegister(arg2, registers)), registers);
        break;
        case 0b00110011: // OR %RX, C
            #ifdef DEBUG
            printf("Command is OR CONSTANT [%s][%d]\n\r", __reg_map[(int)arg1], (int)arg2);
            #endif

            StoreRegister(arg1, (LoadRegister(arg1, registers) | arg2), registers);
        break;
        case 0b00110100: // XOR %RX, %RY
            #ifdef DEBUG
            printf("Command is XOR [%s][%s]\n\r", __reg_map[(int)arg1], __reg_map[(int)arg2]);
            #endif

            StoreRegister(arg1, (LoadRegister(arg1, registers) ^ LoadRegister(arg2, registers)), registers);
        break;
        case 0b00110101: // XOR %RX, C
            #ifdef DEBUG
            printf("Command is XOR CONSTANT [%s][%d]\n\r", __reg_map[(int)arg1], (int)arg2);
            #endif

            StoreRegister(arg1, (LoadRegister(arg1, registers) ^ arg2), registers);
        break;
        case 0b01010010: // BE C
            #ifdef DEBUG
            printf("Command is BE [%s]\n\r", __reg_map[(int)arg1]);
            #endif

            // BE, absolutely.
            if(LoadRegister(0b00010111, registers) == 0) {
                i = (arg1*3)-3;
                StoreRegister(0b00010110, i, registers);
            }
        break;
        case 0b01010100: // BNE C
            #ifdef DEBUG
            printf("Command is BNE [%s]\n\r", __reg_map[(int)arg1]);
            #endif

            // BNE, absolutely.
            if(LoadRegister(0b00010111, registers) != 0) {
                i = (arg1*3)-3;
                StoreRegister(0b00010110, i, registers);
            }
        break;
        case 0b01010110: // BG C
            #ifdef DEBUG
            printf("Command is BNE [%s]\n\r", __reg_map[(int)arg1]);
            #endif

            // BG, absolutely.
            if(LoadRegister(0b00010111, registers) < 128) {
                i = (arg1*3)-3;
                StoreRegister(0b00010110, i, registers);
            }
        break;
        case 0b01011000: // BL C
            #ifdef DEBUG
            printf("Command is BNE [%s]\n\r", __reg_map[(int)arg1]);
            #endif

            // BL, absolutely.
            if(LoadRegister(0b00010111, registers) > 127) {
                i = (arg1*3)-3;
                StoreRegister(0b00010110, i, registers);
            }
        break;
    }

    registers[27] = i; // PC++

    return i;
}

char LoadRegister(char offset, char *registers) {
    // Check offset
    if(offset == 0b00010110) {
        printf("accessing PC/CR violated.~\n\r");
        return 0x00;
    }

    // Just grab and return
    #ifdef DEBUG
    printf("Return %c from offset %c  (%d), register %s\n\r", registers[(int)offset], offset, (int)offset, __reg_map[(int)offset]);
    #endif
    return registers[(int)offset];
}

int StoreRegister(char toRegister, char value, char *registers) {
    // TODO: check offsets... to see if we can write..?

    registers[(int)toRegister] = value;
    return 1;
}
