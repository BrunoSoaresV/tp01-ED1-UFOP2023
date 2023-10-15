#include "grafo.h" // Inclui a definição das estruturas e funções do grafo.
#include <stdio.h> // Inclui a biblioteca padrão para entrada/saída.
#include <stdlib.h> // Inclui a biblioteca padrão de alocação de memória.
int main() {
    int numCidades;
    scanf("%d", &numCidades); // Lê o número de cidades a partir da entrada padrão.
    // Aloca espaço na memória para um grafo ponderado com 'numCidades'.
    GrafoPonderado* grafo = alocarGrafo(numCidades);
    // Lê as informações das distâncias entre as cidades e as armazena no grafo.
    leGrafo(grafo);
    // Aloca memória para armazenar o melhor caminho encontrado, exceto a cidade de origem.
    int* melhorCaminho = (int*)malloc((numCidades - 1) * sizeof(int));
    // Encontra o caminho mais curto através do grafo.
    encontraCaminho(grafo, melhorCaminho);
    int distancia = 0; // Inicializa a variável que armazenará a distância total do caminho.
    // Calcula a distância total percorrida ao somar as distâncias entre as cidades do caminho.
    for (int i = 0; i < numCidades - 1; i++) {
        int cidadeOrigem = melhorCaminho[i];
        int cidadeDestino = melhorCaminho[i + 1];
        distancia += obterDistancia(grafo, cidadeOrigem, cidadeDestino);
    }
    // Adiciona a distância entre a última cidade e a cidade de origem para fechar o ciclo.
    distancia += obterDistancia(grafo, melhorCaminho[numCidades - 1], melhorCaminho[0]);
    // Imprime o caminho mais curto encontrado e a distância total.
    imprimeCaminho(grafo, melhorCaminho, distancia);
    // Libera a memória alocada para o vetor do melhor caminho.
    free(melhorCaminho);
    // Libera a memória alocada para o grafo.
    desalocarGrafo(grafo);
    return 0; // Retorna 0 para indicar que o programa foi executado com sucesso.
}
