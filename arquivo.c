#include <stdio.h>
#include "arquivo.h"

const int C_NUMERO_ITENS = 12;
const char C_ARQ_CONFIGURACAO[] = {"fase.bin"};

int le_arquivo_configuracao(TIPO_FASE* bloco) {
    int retorno = 0;
    int i;
    FILE* arquivo;
    
    if (bloco == NULL)
        retorno = -1;
    else {
        arquivo = fopen(C_ARQ_CONFIGURACAO, "rb");
        
        if (arquivo == NULL)
            retorno = -2;
        else {
            retorno = fread(bloco, sizeof(TIPO_FASE), C_NUMERO_ITENS, arquivo);
    
            fclose(arquivo);
        }
    }
    
    return retorno;
}