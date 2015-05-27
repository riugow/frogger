#include "modconio.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

void gotoxy (int x, int y) {
    printf("\033[%d;%df", y, x);
}

void corDoTexto(cor texto, cor fundo){
    short corTexto, corFundo;

    corTexto = (short)texto + 30;
    corFundo = (short)fundo + 40;

	printf("\033[1;%d;%dm", corTexto, corFundo);
	//printf("\033[0;%d;%dm", corTexto, corFundo);
	//printf("\033[5;%d;%dm", corTexto, corFundo);
}

void cor_padrao() {
    printf("\033[m");
}

void clrscr() {
    // limpa a tela, mantendo sempre o fundo preto!
    printf("\033[40m\033[2J\033[1;1f");
}

int getch_echo (int echo) {
    struct termios oldt, newt;
    int ch;

    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~ICANON;

    if (echo)
        newt.c_lflag &= ECHO;
    else
        newt.c_lflag &= ~ECHO;

    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );

    return ch;
}

int getch() {
    getch_echo (0);
}

int kbhit() {
    struct termios oldt, newt;
    int ch, oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF){
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
