#ifndef GRAFO_H
#define GRAFO_H
typedef struct GrafoPonderado GrafoPonderado;
GrafoPonderado* alocarGrafo(int numCidades);
void desalocarGrafo(GrafoPonderado* grafo);
void leGrafo(GrafoPonderado* grafo);
void encontraCaminho(GrafoPonderado* grafo, int* melhorCaminho);
void imprimeCaminho(GrafoPonderado* grafo, int* caminho, int distancia);
int obterDistancia(GrafoPonderado* grafo, int cidadeOrigem, int cidadeDestino);
#endif
