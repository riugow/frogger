/**
* modconio
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* See the GNU General Public License for details about use and
* distribution of this code. <http://www.gnu.org/licenses/>.
*/

#ifndef __MODIFIED_CONIO_H
#define __MODIFIED_CONIO_H

typedef enum enum_cores {
    BLACK = 0,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
} cor;

void gotoxy (int x, int y);

void corDoTexto(cor texto, cor fundo);

void cor_padrao();

void clrscr();

int getch();

int kbhit();

#endif