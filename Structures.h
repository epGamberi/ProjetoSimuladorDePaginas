#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#define NUM_FRAMES 4
#define TAM_PAGINA 4096
#define PID 1

typedef struct {
    int presente;
    int frame;
    int tempo_carga;
} Pagina;

typedef struct {
    int pid;
    int num_paginas;
    Pagina *tabela_paginas;
} Processo;

typedef struct {
    int frames[NUM_FRAMES];      // (pid << 16) | pagina
    int tempo_carga[NUM_FRAMES];
} MemoriaFisica;

typedef struct {
    int tempo_atual;
    Processo processo;
    MemoriaFisica memoria;
    int total_acessos;
    int page_faults;
    int algoritmo; // 0=FIFO, 1=RANDOM
    int proximo_fifo;
} Simulador;

#endif
