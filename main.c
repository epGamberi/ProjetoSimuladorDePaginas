#include <stdio.h> 
#include "simulador.h"

int main() {
    Simulador sim;
    inicializar_simulador(&sim, 0); // 0 = FIFO, 1 = RANDOM

    int acessos[] = {0, 4096, 8192, 12288, 0, 4096, 16384, 20480, 0};
    int qtd = sizeof(acessos) / sizeof(int);

    printf("\n=== INICIANDO SIMULAÇÃO ===\n\n");
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Acesso %d: endereço virtual %d ---\n", i + 1, acessos[i]);
        acessar_memoria(&sim, acessos[i]);
    }

    exibir_estatisticas(&sim);
    free(sim.processo.tabela_paginas);
    return 0;
}
