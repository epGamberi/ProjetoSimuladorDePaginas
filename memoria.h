#ifndef MEMORIA_H
#define MEMORIA_H

#include "estruturas.h"

int carregar_pagina(Simulador *sim, int pagina);
int substituir_pagina_fifo(Simulador *sim);
int substituir_pagina_random(Simulador *sim);

#endif
