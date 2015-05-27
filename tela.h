/*
 * TELA.H
 *
 */
 
#ifndef _TELA_H_
#define _TELA_H_

/*
 * Imprimir o mapa do jogo
 * ENTRADA: matriz de itens do jogo
 */
void imprimir_tela(char** mapa);
void atualizar_linha(char* linhaMapa, int linha, char **tela);

extern const int C_LINHAS_MAPA;
extern const int C_COLUNAS_MAPA;
extern const int C_LINHAS_TELA;
extern const int C_COLUNAS_TELA;

#endif