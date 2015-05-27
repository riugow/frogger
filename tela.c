#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tela.h"

const int C_TAMANHO_CARRO = 4;

/*
 * Desenha o objeto
 * ENTRADA:
 *   int linha - coordenadas do objeto
 *   int coluna - coordenadas do objeto
 *   char* objeto - o objeto em si
 *   char **tela - matriz da tela do jogo
 */
void desenha_objeto(int linha, int coluna, char* objeto, char **tela) {
    char* substring;
    
    substring = &tela[linha][coluna];
    strncpy(substring, objeto, 2);
}

void desenha_casa_vazia(int linha, int coluna, char **tela){
    desenha_objeto(linha, coluna, "|*", tela);
    desenha_objeto(linha + 1, coluna, "|*", tela);
    desenha_objeto(linha, coluna + 2, "*|", tela);
    desenha_objeto(linha + 1, coluna + 2, "*|", tela);
}

/*
 * Desenha o sapo
 * ENTRADA:
 *   int linha - coordenadas do sapo
 *   int coluna - coordenadas do sapo
 *   char **tela - matriz da tela do jogo
 */
void desenha_sapo(int linha, int coluna, char **tela) {
    desenha_objeto(linha, coluna, "@@", tela);
    desenha_objeto(linha + 1, coluna, "00", tela);
}

/*
 * Desenha um tronco
 * ENTRADA:
 *   int linha: coordenada do tronco
 *   int coluna: coordenada do tronco
 *   char **tela - matriz da tela do jogo
 */
void desenha_tronco(int linha, int coluna, char **tela) {
    desenha_objeto(linha, coluna, "##", tela);
    desenha_objeto(linha + 1, coluna, "##", tela);
}

/*
 * Desenha uma tartaruga
 * ENTRADA:
 *   int linha: coordenada do tronco
 *   int coluna: coordenada do tronco
 *   char orientacao: indicador de submersao
 *                    'r' = submergindo
 *                    'R' = flutuando
 *   char **tela - matriz da tela do jogo
 */
void desenha_tartaruga(int linha, int coluna, char orientacao, char **tela) {
    if (orientacao == 'R') {
        desenha_objeto(linha, coluna, "/\\", tela);
        desenha_objeto(linha + 1, coluna, "/\\", tela);
    } else {
        desenha_objeto(linha, coluna, "\\/", tela);
        desenha_objeto(linha + 1, coluna, "\\/", tela);
    }
}

/*
 * Desenha um carro
 * ENTRADA:
 *   int linha: coordenada do carro
 *   int coluna: coordenada do carro
 *   int tamanhoCarro: tamanho do carro na tela (para desenha-lo
 *                     parcialmente nas bordas da tela)
 *   char direcao: orientacao do desenho
 *   char **tela - matriz da tela do jogo
 */
void desenha_carro(int linha, int coluna, int tamanhoCarro, char direcao, char **tela) {
    char carro_topo[9];
    char carro_base[9];
    char parametro[2];
    int offset, n;
    
    offset = 0;
    
    // 18 0 3    18 30 4
    // 20 4 4    20 28 4     20 52 2
    
    if (coluna == 0)
        offset = C_TAMANHO_CARRO - tamanhoCarro;
    
    if (direcao == 'C') {
        strcpy(carro_topo, " _|=\\__ ");
        strcpy(carro_base, "/o___o_\\");
    } else {
        strcpy(carro_topo, " __/=|_ ");
        strcpy(carro_base, "/_o___o\\");
    }
    
    //if (offset == 0)
    //    offset = tamanhoCarro;
    while (tamanhoCarro > 0) {
        strncpy(parametro, &carro_topo[offset * 2], 2);
        desenha_objeto(linha, coluna, parametro, tela);
        strncpy(parametro, &carro_base[offset * 2], 2);
        desenha_objeto(linha+1, coluna, parametro, tela);
        tamanhoCarro--;
        coluna+=2;
        offset++;
    }
}

/*
 * Desenha agua
 * ENTRADA:
 *   int linha: coordenada da agua
 *   int coluna: coordenada da agua
 *   char **tela - matriz da tela do jogo
 */
void desenha_agua(int linha, int coluna, char **tela) {
    desenha_objeto(linha, coluna, "~~", tela);
    desenha_objeto(linha + 1, coluna, "~~", tela);
}

/*
 * Desenha um espaco vazio
 * ENTRADA:
 *   int linha: coordenada do espaco
 *   int coluna: coordenada do espaco
 *   char **tela - matriz da tela do jogo
 */
void desenha_vazio(int linha, int coluna, char **tela) {
    desenha_objeto(linha, coluna, "  ", tela);
    desenha_objeto(linha + 1, coluna, "  ", tela);
}


/*
 * Atualizar o desenho de uma linha na tela
 * ENTRADA:
 *   char* linhaMapa - linha com os caracteres do mapa
 *   int linha - indice da linha no mapa
 *   char **tela - matriz da tela do jogo
 */
void atualizar_linha(char* linhaMapa, int linha, char** tela) {
    int coluna = 0;
    int tamanhoCarro = 0;
    
    while (coluna < (C_COLUNAS_TELA - 1) / 2) {
        switch (linhaMapa[coluna]) {
        case 'S': // sapo
            desenha_sapo(linha*2, coluna*2, tela);
            break;
        case 'T':
            desenha_tronco(linha*2, coluna*2, tela);
            break;
        case 'R':
        case 'r':
            desenha_tartaruga(linha*2, coluna*2, linhaMapa[coluna], tela);
            break;
        case 'C':
        case 'c':
            while ((toupper(linhaMapa[coluna + tamanhoCarro]) == 'C') &&
                   ((coluna + tamanhoCarro) < (C_COLUNAS_TELA - 1)/2)) {
                tamanhoCarro++;
            }
            desenha_carro(linha*2, coluna*2, tamanhoCarro, linhaMapa[coluna], tela);
            coluna+=tamanhoCarro - 1;
            tamanhoCarro = 0;
            break;
        case 'A':
            desenha_agua(linha*2, coluna*2, tela);
            break;
        case 'V':
            desenha_vazio(linha*2, coluna*2, tela);
            break;
        case 'h':
            desenha_casa_vazia(linha*2, coluna*2, tela);
            coluna++;
            break;
        }
        coluna++;
    }        
}


/*
 * Imprimir o mapa do jogo
 * ENTRADA:
 *   char** mapa - matriz de itens do jogo
 */
void imprimir_tela(char** tela) {
    //indice das linhas da matriz;
    int i;
    
    for (i = 0; i < C_LINHAS_TELA; i++) // cada item no mapa e impresso em duas linhas
        puts(tela[i]);
}