#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "estruturas.h" 

void inicializar_simulador(Simulador *sim, int algoritmo);
void acessar_memoria(Simulador *sim, int endereco_virtual);
void exibir_estatisticas(Simulador *sim);

#endif
