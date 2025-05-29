# Integrantes do Grupo

- Enzo Ponte Gamberi RA:10389931
- Thiago Ruiz Fernandes Silva RA:10426057
- João Guilherme Messias de Oliveira Santos RA:10426110

# Projeto Simulador de Paginação de Memória

Este nosso projeto simula o funcionamento de um sistema de gerenciamento de memória com paginação, usando os algoritmos de substituição FIFO e Random. Foi desenvolvido como parte da disciplina Sistemas Operacionais

# Descrição do Projeto

O simulador implementa um sistema de paginação de memória com as seguintes características:
- Tradução de endereços virtuais para endereços físicos
-Gerenciamento de tabela de páginas para um processo (versão simplificada)
-Implementação de algoritmos de substituição de páginas:
  - FIFO (First-In-First-Out)
  - Random (Escolha aleatória de página para substituição)

O simulador registra estatísticas importantes como o número de acessos à memória, page faults e a taxa de page faults, permitindo avaliar o comportamento dos algoritmos em diferentes padrões de acesso.

# Configurações do Simulador

- Tamanho da página: 4096 bytes (4KB)
- Tamanho da memória física: 16384 bytes (16KB) — 4 frames
- Número de processos: 1 processo
- Tamanho do processo: 32768 bytes (8 páginas)
- Sequência de acessos: pré-definida com endereços virtuais variados

# Estrutura do Projeto

simulador_memoria

├── main.c  // Função principal da simulação

├── simulador.c/.h  // Lógica da simulação, controle de tempo e estatísticas

├── memoria.c/.h  // Controle de memória física e substituição

├── estruturas.h  // Tipos e constantes do sistema

├── README.md  // Este arquivo

# Funcionalidades Implementadas
## Algoritmos de Substituição

- FIFO: Substitui a página mais antiga na memória (ordem de chegada).
- Random: Substitui uma página aleatória da memória física.

# Recursos do Simulador

- Tradução de endereços virtuais para físicos
- Detecção e tratamento de page faults
- Carga de páginas em memória e substituição automática
- Coleta de estatísticas:
  - Total de acessos
  - Total de page faults
  - Taxa de page fault

# Instruções de Compilação e Execução
## Requisitos

- Compilador GCC
- Sistema Linux, macOS ou Windows com suporte a rand() e time.h

# Compilação
## Comando de compilação:

gcc -o simulador simulador.c

./simulador

Por padrão, o algoritmo utilizado é FIFO. Para usar Random, basta modificar o valor algoritmo dentro da função inicializar_simulador.

# Como Usar o Simulador

1 - Compile e execute o programa

2 - O simulador inicia com a configuração padrão

3 - Ele executa uma sequência fixa de acessos virtuais simulando um processo

4 - A cada acesso, o simulador:
  - Traduz o endereço virtual
  - Trata o page fault (se ocorrer)
  - Exibe o frame correspondente
    
5 - Ao final, imprime as estatísticas da execução

# Exemplo de Saída

Page Fault! Página 0 não está na memória.

Página 0 carregada no Frame 0, Endereço Físico: 0

Acesso OK: Página 1 -> Frame 1, Endereço Físico: 4096

Page Fault! Página 2 não está na memória.

Página 2 carregada no Frame 2, Endereço Físico: 8192

...

--- ESTATÍSTICAS ---
Total de acessos: 9
Page faults: 7
Taxa de page fault: 77.78%

# Considerações
Este simulador é uma versão simplificada com foco em demonstrar os conceitos fundamentais de paginação e substituição de páginas. A estrutura modular permite fácil expansão para múltiplos processos e algoritmos mais sofisticados como LRU e CLOCK.
