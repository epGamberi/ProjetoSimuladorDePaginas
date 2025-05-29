#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_FRAMES 4
#define NUM_PAGINAS 8
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
    int frames[NUM_FRAMES]; // (pid << 16) | num_pagina
    int tempo_carga[NUM_FRAMES];
} MemoriaFisica;

typedef struct {
    int tempo_atual;
    Processo processo;
    MemoriaFisica memoria;
    int total_acessos;
    int page_faults;
    int algoritmo; // 0 = FIFO, 1 = RANDOM
    int proximo_fifo;
} Simulador;
