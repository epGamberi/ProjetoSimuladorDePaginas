#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "memoria.h"

void inicializar_simulador(Simulador *sim, int algoritmo) {
    sim->tempo_atual = 0;
    sim->total_acessos = 0;
    sim->page_faults = 0;
    sim->algoritmo = algoritmo;
    sim->proximo_fifo = 0;

    for (int i = 0; i < NUM_FRAMES; i++) {
        sim->memoria.frames[i] = -1;
        sim->memoria.tempo_carga[i] = -1;
    }

    sim->processo.pid = PID;
    sim->processo.num_paginas = 8;
    sim->processo.tabela_paginas = malloc(sizeof(Pagina) * 8);

    for (int i = 0; i < 8; i++) {
        sim->processo.tabela_paginas[i].presente = 0;
        sim->processo.tabela_paginas[i].frame = -1;
        sim->processo.tabela_paginas[i].tempo_carga = -1;
    }

    srand(42); // semente fixa para testes previsíveis
}

void acessar_memoria(Simulador *sim, int endereco_virtual) {
    int pagina = endereco_virtual / TAM_PAGINA;
    int deslocamento = endereco_virtual % TAM_PAGINA;

    sim->total_acessos++;
    sim->tempo_atual++;

    if (sim->processo.tabela_paginas[pagina].presente) {
        int frame = sim->processo.tabela_paginas[pagina].frame;
        int endereco_fisico = frame * TAM_PAGINA + deslocamento;
        printf("[OK] Página %d está presente -> Frame %d -> Endereço físico: %d\n", pagina, frame, endereco_fisico);
    } else {
        sim->page_faults++;
        printf("[Page Fault] Página %d ausente -> carregando...\n", pagina);
        int frame = carregar_pagina(sim, pagina);
        int endereco_fisico = frame * TAM_PAGINA + deslocamento;
        printf("Página %d alocada no Frame %d -> Endereço físico: %d\n", pagina, frame, endereco_fisico);
    }
}

void exibir_estatisticas(Simulador *sim) {
    printf("\n=== ESTATÍSTICAS ===\n");
    printf("Total de acessos: %d\n", sim->total_acessos);
    printf("Page Faults: %d\n", sim->page_faults);
    printf("Taxa de page faults: %.2f%%\n", 100.0 * sim->page_faults / sim->total_acessos);
}
