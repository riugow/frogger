/*
 * DEFINICOES.H
 */

#ifndef _DEFINICOES_H_
#define _DEFINICOES_H_

#define LINHAS_TELA 26
#define COLUNAS_TELA 57
#define LINHAS_MAPA 13
#define COLUNAS_MAPA 28
#define NUMERO_ITENS 12

typedef struct tipo_fase {
    char objeto;
    int tamanho;
    int espacamento;
    float velocidade;
    int linha_inicial;
    int coluna_inicial;
} TIPO_FASE;


char tela[LINHAS_TELA][COLUNAS_TELA];
char mapa[LINHAS_MAPA][COLUNAS_MAPA];
TIPO_FASE dados[NUMERO_ITENS];
int velocidade[LINHAS_MAPA][2];

extern const int C_LINHAS_MAPA;
extern const int C_COLUNAS_MAPA;
extern const int C_LINHAS_TELA;
extern const int C_COLUNAS_TELA;

#endif