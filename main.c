#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_FRAMES 4
#define NUM_PAGINAS 8
#define PID 1

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
    sim->processo.num_paginas = NUM_PAGINAS;
    sim->processo.tabela_paginas = malloc(sizeof(Pagina) * NUM_PAGINAS);
    for (int i = 0; i < NUM_PAGINAS; i++) {
        sim->processo.tabela_paginas[i].presente = 0;
        sim->processo.tabela_paginas[i].frame = -1;
        sim->processo.tabela_paginas[i].tempo_carga = -1;
    }

    srand(time(NULL)); // para o algoritmo RANDOM
}

int substituir_pagina_fifo(Simulador *sim) {
    int frame_substituido = sim->proximo_fifo;
    sim->proximo_fifo = (sim->proximo_fifo + 1) % NUM_FRAMES;
    return frame_substituido;
}

int substituir_pagina_random(Simulador *sim) {
    return rand() % NUM_FRAMES;
}

int carregar_pagina(Simulador *sim, int pagina) {
    // Verificar se há frame livre
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (sim->memoria.frames[i] == -1) {
            sim->memoria.frames[i] = (PID << 16) | pagina;
            sim->memoria.tempo_carga[i] = sim->tempo_atual;
            sim->processo.tabela_paginas[pagina].presente = 1;
            sim->processo.tabela_paginas[pagina].frame = i;
            sim->processo.tabela_paginas[pagina].tempo_carga = sim->tempo_atual;
            return i;
        }
    }

    // Substituir se necessário
    int frame;
    if (sim->algoritmo == 0)
        frame = substituir_pagina_fifo(sim);
    else
        frame = substituir_pagina_random(sim);

    int old_pid = sim->memoria.frames[frame] >> 16;
    int old_pag = sim->memoria.frames[frame] & 0xFFFF;

    sim->processo.tabela_paginas[old_pag].presente = 0;
    sim->processo.tabela_paginas[old_pag].frame = -1;

    sim->memoria.frames[frame] = (PID << 16) | pagina;
    sim->memoria.tempo_carga[frame] = sim->tempo_atual;

    sim->processo.tabela_paginas[pagina].presente = 1;
    sim->processo.tabela_paginas[pagina].frame = frame;
    sim->processo.tabela_paginas[pagina].tempo_carga = sim->tempo_atual;

    return frame;
}

void acessar_memoria(Simulador *sim, int endereco_virtual) {
    int pagina = endereco_virtual / 4096;
    int deslocamento = endereco_virtual % 4096;
    sim->total_acessos++;
    sim->tempo_atual++;

    if (sim->processo.tabela_paginas[pagina].presente) {
        int frame = sim->processo.tabela_paginas[pagina].frame;
        int endereco_fisico = frame * 4096 + deslocamento;
        printf("Acesso OK: Página %d -> Frame %d, Endereço Físico: %d\n", pagina, frame, endereco_fisico);
    } else {
        sim->page_faults++;
        printf("Page Fault! Página %d não está na memória.\n", pagina);
        int frame = carregar_pagina(sim, pagina);
        int endereco_fisico = frame * 4096 + deslocamento;
        printf("Página %d carregada no Frame %d, Endereço Físico: %d\n", pagina, frame, endereco_fisico);
    }
}

void exibir_estatisticas(Simulador *sim) {
    printf("\n--- ESTATÍSTICAS ---\n");
    printf("Total de acessos: %d\n", sim->total_acessos);
    printf("Page faults: %d\n", sim->page_faults);
    printf("Taxa de page fault: %.2f%%\n", 100.0 * sim->page_faults / sim->total_acessos);
    printf("---------------------\n");
}

int main() {
    Simulador sim;
    inicializar_simulador(&sim, 0); // 0 = FIFO, 1 = RANDOM

    int acessos[] = {0, 4096, 8192, 12288, 0, 4096, 16384, 20480, 0};
    int num_acessos = sizeof(acessos) / sizeof(int);

    for (int i = 0; i < num_acessos; i++) {
        acessar_memoria(&sim, acessos[i]);
    }

    exibir_estatisticas(&sim);
    free(sim.processo.tabela_paginas);
    return 0;
}
