#include <stdio.h>
#include "display.h"
#include "cpu.h"

void updateDisplay(char *registers) {
    int __disp[4] = {D3, D2, D1, D0};
    short i;

    printf("\x1B[0;0H"); // Reset cursor?

    // TOPMOST
    printf(" ");
    for(i = 0; i < 4; i++) {
        (LoadRegister(__disp[i], registers) & 1) == 1 ? printf("_") : printf(" ");
        printf("   ");
    }

    printf("\n\r");

    // MIDDLE
    for(i = 0; i < 4; i++) {
        // number 6 -> shift to right 5 times -> make 0 or 1 appear at topmost right (least significant bit).
        ((LoadRegister(__disp[i], registers) >> 5) & 1) == 1 ? printf("|") : printf(" "); // 6
        ((LoadRegister(__disp[i], registers) >> 6) & 1) == 1 ? printf("_") : printf(" "); // 7
        ((LoadRegister(__disp[i], registers) >> 1) & 1) == 1 ? printf("|") : printf(" "); // 2
        printf(" ");
    }

    printf("\n\r");

    // BOTTOM
    for(i = 0; i < 4; i++) {
        ((LoadRegister(__disp[i], registers) >> 4) & 1) == 1 ? printf("|") : printf(" "); // 6
        ((LoadRegister(__disp[i], registers) >> 3) & 1) == 1 ? printf("_") : printf(" "); // 7
        ((LoadRegister(__disp[i], registers) >> 2) & 1) == 1 ? printf("|") : printf(" "); // 2
        printf(" ");
    }
}

void updateButtons(int c, char *registers) {
    printf("\r\npress q to exit");
    switch(c) {
        case 97:
            StoreRegister(0b00010000, 1, registers);
            StoreRegister(0b00010001, 0, registers);
            printf("\r\nA Pressed");
        break;
        case 98:
            StoreRegister(0b00010000, 0, registers);
            StoreRegister(0b00010001, 1, registers);
            printf("\r\nB Pressed");
        break;
        default:
            StoreRegister(0b00010000, 0, registers);
            StoreRegister(0b00010001, 0, registers);
            printf("\r\n          ");
        break;
    }
}
