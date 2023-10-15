#include "grafo.h" // Inclui o cabeçalho "grafo.h" que contém as declarações de funções e estruturas.
#include <stdio.h> // Inclui a biblioteca padrão de entrada/saída.
#include <stdlib.h> // Inclui a biblioteca padrão de alocação de memória.
#include <limits.h> // Inclui a biblioteca que fornece constantes de limites, incluindo INT_MAX.

struct GrafoPonderado { // Define uma estrutura chamada GrafoPonderado para representar o grafo.
    int numCidades; // Número de cidades no grafo.
    int** matrizAdj; // Matriz de adjacência para representar as distâncias entre as cidades.
};

GrafoPonderado* alocarGrafo(int numCidades) { // Função para alocar memória para uma estrutura GrafoPonderado.
    GrafoPonderado* grafo = (GrafoPonderado*)malloc(sizeof(GrafoPonderado)); // Aloca memória para a estrutura.
    if (grafo == NULL) { // Verifica se a alocação foi bem-sucedida.
        // Tratamento de erro de alocação de memória.
        exit(1); // Encerra o programa com código de erro 1 ou toma alguma outra ação apropriada.
    }
    grafo->numCidades = numCidades; // Inicializa o número de cidades no grafo.
    grafo->matrizAdj = (int**)malloc(numCidades * sizeof(int*)); // Aloca memória para a matriz de adjacência.
    if (grafo->matrizAdj == NULL) { // Verifica se a alocação da matriz foi bem-sucedida.
        // Tratamento de erro de alocação de memória.
        free(grafo); // Libera a memória alocada para a estrutura GrafoPonderado.
        exit(1); // Encerra o programa com código de erro 1 ou toma alguma outra ação apropriada.
    }
    for (int i = 0; i < numCidades; i++) {
        grafo->matrizAdj[i] = (int*)malloc(numCidades * sizeof(int)); // Aloca memória para as distâncias entre as cidades.

        if (grafo->matrizAdj[i] == NULL) { // Verifica se a alocação das distâncias foi bem-sucedida.
            // Tratamento de erro de alocação de memória.
            free(grafo->matrizAdj); // Libera a memória alocada para a matriz de adjacência.
            free(grafo); // Libera a memória alocada para a estrutura GrafoPonderado.
            exit(1); // Encerra o programa com código de erro 1 ou toma alguma outra ação apropriada.
        }
    }
    // Inicializa a matriz de adjacência com distâncias iniciais.
    for (int i = 0; i < numCidades; i++) {
        for (int j = 0; j < numCidades; j++) {
            grafo->matrizAdj[i][j] = 0; // Inicializa as distâncias com 0.
        }
    }
    return grafo; // Retorna a estrutura GrafoPonderado alocada.
}

void desalocarGrafo(GrafoPonderado* grafo) {
    if (grafo != NULL) { // Verifica se o ponteiro para a estrutura GrafoPonderado é válido.
        if (grafo->matrizAdj != NULL) { // Verifica se o ponteiro para a matriz de adjacência é válido.
            for (int i = 0; i < grafo->numCidades; i++) { // Loop para percorrer todas as linhas da matriz.
                free(grafo->matrizAdj[i]); // Libera a memória alocada para as distâncias da cidade atual.
            }
            free(grafo->matrizAdj); // Libera a memória alocada para a matriz de adjacência em si.
        }
        free(grafo); // Libera a memória alocada para a estrutura GrafoPonderado.
    }
}

void leGrafo(GrafoPonderado* grafo) {
    int numCidades = grafo->numCidades; // Obtém o número de cidades do grafo.
    for (int i = 0; i < numCidades; i++) { // Loop externo para percorrer as cidades de origem.
        for (int j = 0; j < numCidades; j++) { // Loop interno para percorrer as cidades de destino.
            int origem, destino, distancia; // Declara variáveis para armazenar dados lidos.
            scanf("%d %d %d", &origem, &destino, &distancia); // Lê três valores da entrada padrão.
            grafo->matrizAdj[origem][destino] = distancia; // Atualiza a matriz de adjacência com a distância entre origem e destino.
        }
    }
}

// Função para obter a distância entre duas cidades no grafo.
int obterDistancia(GrafoPonderado* grafo, int cidadeOrigem, int cidadeDestino) {
    // Verifica se as cidades fornecidas são válidas (dentro dos limites do grafo).
    if (cidadeOrigem >= 0 && cidadeOrigem < grafo->numCidades && cidadeDestino >= 0 && cidadeDestino < grafo->numCidades) {
        // Retorna a distância armazenada na matriz de adjacência para as cidades fornecidas.
        return grafo->matrizAdj[cidadeOrigem][cidadeDestino];
    } else {
        // Se as cidades não forem válidas, retorna -1 para indicar um erro ou distância inválida.
        return -1;
    }
}

// Função recursiva para encontrar o melhor caminho em um grafo ponderado.
void encontraCaminhoRec(int posicao, int distancia, int contador, int* visitado, int* caminhoAtual, int* melhorCaminho, int numCidades, GrafoPonderado* grafo, int* menorDistancia) {
    // Verifica se o contador alcançou o número total de cidades no grafo.
    if (contador == numCidades - 1) {
        // Se o contador atingir o número de cidades - 1, significa que visitamos todas as cidades.
        // Verifica se há uma aresta de retorno para a cidade de origem (ciclo completo) e se a distância total é menor.
        if (grafo->matrizAdj[posicao][0] != 0 && distancia + grafo->matrizAdj[posicao][0] < *menorDistancia) {
            // Se encontrarmos um caminho mais curto, atualizamos o menorDistancia e o melhorCaminho.
            *menorDistancia = distancia + grafo->matrizAdj[posicao][0];
            for (int i = 0; i < numCidades; i++) {
                melhorCaminho[i] = caminhoAtual[i];
            }
        }
        return; // Retorna da recursão.
    }
    // Percorre as próximas cidades a serem visitadas a partir da posição atual.
    for (int proximaCidade = 0; proximaCidade < numCidades; proximaCidade++) {
        if (grafo->matrizAdj[posicao][proximaCidade] != 0 && visitado[proximaCidade] == 0) {
            // Verifica se existe uma aresta para a próxima cidade e se essa cidade ainda não foi visitada.
            // Marcamos a próxima cidade como visitada, atualizamos o caminho atual e a distância.
            visitado[proximaCidade] = 1;
            caminhoAtual[contador] = proximaCidade;
            // Chamamos a função recursivamente para explorar o próximo nível de cidades.
            encontraCaminhoRec(proximaCidade, distancia + grafo->matrizAdj[posicao][proximaCidade], contador + 1, visitado, caminhoAtual, melhorCaminho, numCidades, grafo, menorDistancia);
            // Desmarcamos a próxima cidade como visitada após a recursão para explorar outros caminhos.
            visitado[proximaCidade] = 0;
        }
    }
}

// Função para encontrar o caminho mais curto em um grafo ponderado usando força bruta.
void encontraCaminho(GrafoPonderado* grafo, int* melhorCaminho) {
    int numCidades = grafo->numCidades;
    // Aloca um array para controlar as cidades visitadas.
    int* visitado = (int*)malloc(numCidades * sizeof(int));
    // Aloca um array para rastrear o caminho atual.
    int* caminhoAtual = (int*)malloc(numCidades * sizeof(int));
    // Inicializa a menorDistancia com um valor máximo.
    int menorDistancia = INT_MAX;
    // Marca a cidade de origem (0) como visitada e inicia o caminho atual.
    for (int i = 0; i < numCidades; i++) {
        visitado[i] = 0;
    }
    visitado[0] = 1;
    caminhoAtual[0] = 0;
    // Chama a função encontraCaminhoRec para encontrar o caminho mais curto.
    encontraCaminhoRec(0, 0, 0, visitado, caminhoAtual, melhorCaminho, numCidades, grafo, &menorDistancia);
    // Libera a memória alocada para os arrays de controle.
    free(visitado);
    free(caminhoAtual);
}

// Função para imprimir o caminho mais curto encontrado e a distância total.
void imprimeCaminho(GrafoPonderado* grafo, int* caminho, int distancia) {
    // Imprime a cidade de origem (0) para iniciar o caminho.
    printf("0 ");
    // Percorre as cidades do caminho, exceto a última, e as imprime.
    for (int i = 0; i < grafo->numCidades - 1; i++) {
        printf("%d ", caminho[i]);
    }
    // Imprime a cidade de origem (0) novamente para completar o ciclo.
    printf("0\n");
    // Imprime a distância total do caminho encontrado.
    printf("%d\n", distancia);
}

