#include <stdio.h>
#include "modconio.h"
#include <time.h>
#include <sys/select.h>
#include <unistd.h>
#include "jogo.h"
#include "tela.h"
#include "definicoes.h"
#include "arquivo.h"

extern const int C_NUMERO_ITENS;
const int C_LINHAS_MAPA = LINHAS_MAPA;
const int C_COLUNAS_MAPA = COLUNAS_MAPA;
const int C_LINHAS_TELA = LINHAS_TELA;
const int C_COLUNAS_TELA = COLUNAS_TELA;

int escreve_conf() {
    FILE* arq;
    int retorno = 0;
    TIPO_FASE teste[] = {
        // objeto, tamanho, espacamento, velocidade, linha, coluna
        {'h', 2, 3, 0.0, 0, 6},
        {'R', 2, 3, -0.2, 2, -2},
        {'T', 5, 8, 0.9, 4, 4},
        {'R', 5, 6, 0.6, 6, 2},
        {'T', 3, 12, -0.3, 8, 8},
        {'R', 2, 2, -0.4, 10, 4},
        {'C', 0, 14, 0.9, 14, 18},
        {'C', 0, 4, 0.1, 16, 6},
        {'C', 0, 6, -0.5, 18, -4},
        {'C', 0, 12, 1.0, 20, -2},
        {'C', 0, 8, -0.2, 22, 2},
        {'S', 0, 0, 0.0, 24, 26}
    };
    
    arq = fopen("fase.bin", "wb");
    if (arq != NULL) { 
       // printf("imprimiu?\n");
        retorno = fwrite(teste, sizeof(TIPO_FASE), C_NUMERO_ITENS, arq);
       // printf("imprimiu\n");
        
        fclose(arq);
    }
    return retorno;
}

int main() {
    TIPO_FASE teste[C_NUMERO_ITENS];
    char* ppMapa[LINHAS_MAPA];
    char* ppTela[LINHAS_TELA];

    int i, j;
    
    for (i = 0; i < LINHAS_MAPA; i++)
        ppMapa[i] = mapa[i];
    for (i = 0; i < LINHAS_TELA; i++)
        ppTela[i] = tela[i];
        
  //  i = le_arquivo_configuracao(teste);
  //  if (i != C_NUMERO_ITENS) {
        i = escreve_conf();
        if (i != C_NUMERO_ITENS)
            return -1;
        i = le_arquivo_configuracao(teste);
  //  }
    
    constroi_mapa_jogo(teste, C_NUMERO_ITENS, ppMapa);
    
    for (i = 0; i < LINHAS_MAPA; i++) {
       // for (j = 0; j < COLUNAS_MAPA; j++)
       //    printf("%c ", mapa[i][j]);
       atualizar_linha(mapa[i], i, ppTela);
       // printf("\n\n");
    }
    //*
    
    while (!kbhit())  {
      //fflush(stdout);
       //printf("teste");
       clrscr();
       usleep(200000);
       imprimir_tela(ppTela);
     //  printf("\n\n\n\n\n\n\n\n");
    }
//*/
  //  if (getch() == 224)
 // printf("%c", getch());
        switch (getch()) {
        case 87:
            printf("w - pra cima");
            break;
        case 83:
            printf("s - pra baixo");
            break;
        case 65:
            printf("a - pra esquerda");
            break;
        case 68:
            printf("d - pra direita");
            break;
        }
    printf("SAiu"); 
    //*/
    
    
    return 0;
}