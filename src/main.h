#ifndef __MAIN_H
    #define __MAIN_H
        char *ReadBinary(char fileName[32], int *);
        void reset_terminal_mode();
        void set_conio_terminal_mode();
        int kbhit();
        int getch();

        extern const char *__reg_map[];
        struct termios orig_termios;
#endif
