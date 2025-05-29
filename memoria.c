#include <stdlib.h> 
#include "memoria.h"

int substituir_pagina_fifo(Simulador *sim) {
    int frame = sim->proximo_fifo;
    sim->proximo_fifo = (sim->proximo_fifo + 1) % NUM_FRAMES;
    return frame;
}

int substituir_pagina_random(Simulador *sim) {
    return rand() % NUM_FRAMES;
}

int carregar_pagina(Simulador *sim, int pagina) {
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

    int frame = (sim->algoritmo == 0) ? substituir_pagina_fifo(sim)
                                      : substituir_pagina_random(sim);

    int old = sim->memoria.frames[frame] & 0xFFFF;
    sim->processo.tabela_paginas[old].presente = 0;
    sim->processo.tabela_paginas[old].frame = -1;

    sim->memoria.frames[frame] = (PID << 16) | pagina;
    sim->memoria.tempo_carga[frame] = sim->tempo_atual;

    sim->processo.tabela_paginas[pagina].presente = 1;
    sim->processo.tabela_paginas[pagina].frame = frame;
    sim->processo.tabela_paginas[pagina].tempo_carga = sim->tempo_atual;

    return frame;
}
