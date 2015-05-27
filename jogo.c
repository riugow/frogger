#include "jogo.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define INICIO_AGUA 1
#define FIM_AGUA 5

void adicionar_item(TIPO_FASE*, char **mapa);
/*
 * Inicializar o mapa com os elementos padrao:
 * A: agua
 * V: vazio (ou asfalto)
 * SAIDA:
 *   char** mapa - mapa de itens do jogo
 * RETORNO:
 *   int: -1 se falhou na alocacao de memoria
 *         0 se OK
 */
int inicializar_mapa(char **mapa) {
    //indices da matriz;
    int i, j;
        
    for (i = 0; i < C_LINHAS_MAPA; i++) {
        for (j = 0; j < C_COLUNAS_MAPA; j++) {
            if ((i >= INICIO_AGUA ) && (i <= FIM_AGUA))  // inicializar a area da agua
                mapa[i][j] = 'A';
            else
                mapa[i][j] = 'V'; // inicializar o espaco vazio
        }
    }
    return 0;
}


/*
 * Constroi matriz de itens de jogo
 * ENTRADA:
 *   TIPO_FASE* itens - colecao de dados de itens do jogo
 *   int qtdeItens - numero de itens a serem adicionados
 * RETORNO:
 *   char** mapa - matriz de itens
 */
int constroi_mapa_jogo(TIPO_FASE* itens, int qtdeItens, char **mapa) {
    int n, status, i;
    
    status = inicializar_mapa(mapa);

    if (status == 0) {
        for (n = 0; n < qtdeItens; n++) {
           // i = itens[n].linha_inicial/2;
           
            adicionar_item(&itens[n], mapa);
        }
        printf("\n");
    }
    else return -1;
}


/*
 * Adicionar item do jogo no mapa
 * Para os itens com sentido de movimento relevante, o padrao adotado
 * e:
 *   caractere tipo de objeto minusculo: movimento para a esquerda
 *   caractere tipo de objeto maiusculo: movimento para a direita
 * ENTRADA: 
 *   TIPO_FASE* item - estrutura de um item do jogo, previamente validada
 *   char **mapa - matriz do mapa do jogo
 */
void adicionar_item(TIPO_FASE* item, char **mapa) {
    int i; // iterador da coluna da matriz de mapa
    int t; // iterador do tamanho do objeto a ser adicionado na matriz
     
    if (item != NULL) {
        printf("%c ", item->objeto);
        if (item->objeto == 'S') { // sapo
            // somente pode ser adicionado em um espaco vazio, um tronco ou uma tartaruga
            if ( ( toupper(mapa[item->linha_inicial / 2][item->coluna_inicial / 2]) == 'V' ) ||
                 ( toupper(mapa[item->linha_inicial / 2][item->coluna_inicial / 2]) == 'T' ) ||
                 ( toupper(mapa[item->linha_inicial / 2][item->coluna_inicial / 2]) == 'R' ) )
                mapa[item->linha_inicial / 2][item->coluna_inicial / 2] = 'S';
        } else if (item->objeto != ' ') {
            char objeto;
            
            i = item->coluna_inicial / 2;
            
            if (toupper(item->objeto) == 'C') {
            // identifica direcao no mapa, importante para carros
                if (item->velocidade < 0.0)
                    objeto = 'c';
                else
                    objeto = 'C';
                item->tamanho = 4;
            }
            else objeto = item->objeto;
            while (i < C_COLUNAS_MAPA) {                
                // preenche o mapa com o item
                for (t = 0; (t < item->tamanho) && ((i+t) < C_COLUNAS_MAPA); t++)
                    if ((i + t) >= 0)  
                        mapa[item->linha_inicial / 2][i + t] = objeto;
                i += item->tamanho + item->espacamento;
            }
        }
    }
}

void imprimir(char **mapa, char **tela) {
    int i;
    
    for (i = 0; i < C_LINHAS_MAPA; i++)
        atualizar_linha(mapa[C_LINHAS_MAPA], C_LINHAS_MAPA, tela);
        
    imprimir_tela(tela);
}

void movimentar_sapo(int direcao) {
}

void atualiza_movimento(char** mapa) {
    //int i;
    
    //for (i = 0; i < C_LINHAS_MAPA; i++)
}