/*
 * JOGO.H
 *
 */

#ifndef _JOGO_H_
#define _JOGO_H_

#include "definicoes.h"

extern const int C_LINHAS_MAPA;
extern const int C_COLUNAS_MAPA;

int constroi_mapa_jogo(TIPO_FASE* item, int qtdeItens, char** mapa);
void movimentar_sapo(int direcao);
void atualiza_movimento(char** mapa);

#endif