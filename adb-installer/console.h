//
//  console.h
//  adb-get
//
//  Created by 上坂龍二 on 2019/7/24.
//  Copyright © 2019 上坂龍二. All rights reserved.
//

#ifndef console_h
#define console_h

#define CLEAR()           printf("\033[2J")
#define CLEARLINE()       printf("\r\e[K")
#define MOVEUP(x)         printf("\033[%dA", (x))
#define MOVEDOWN(x)       printf("\033[%dB", (x))
#define MOVELEFT(y)       printf("\033[%dD", (y))
#define MOVERIGHT(y)      printf("\033[%dC",(y))
#define MOVETO(x,y)       printf("\033[%d;%dH", (x), (y))
#define BACK()            printf("\033[H")

#define HIDE()            printf("\033[?25l")
#define SHOW()            printf("\033[?25h")

#define NONE                 "\e[0m"
#define BLACK                "\e[0;30m"
#define L_BLACK              "\e[1;30m"
#define RED                  "\e[0;31m"
#define L_RED                "\e[1;31m"
#define GREEN                "\e[0;32m"
#define L_GREEN              "\e[1;32m"
#define BROWN                "\e[0;33m"
#define YELLOW               "\e[1;33m"
#define BLUE                 "\e[0;34m"
#define L_BLUE               "\e[1;34m"
#define PURPLE               "\e[0;35m"
#define L_PURPLE             "\e[1;35m"
#define CYAN                 "\e[0;36m"
#define L_CYAN               "\e[1;36m"
#define GRAY                 "\e[0;37m"
#define WHITE                "\e[1;37m"

void CLEARLINES(int x) {
    for(int i=0; i<x; i++) {
        MOVEUP(1);
        CLEARLINE();
    }
}

#endif /* console_h */
