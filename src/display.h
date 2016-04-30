#ifndef __DISPLAY_H
    #define __DISPLAY_H
    void updateDisplay(char *registers);
    void updateButtons(int c, char *registers);

    #define D3 0b00010101
    #define D2 0b00010100
    #define D1 0b00010011
    #define D0 0b00010010
#endif
