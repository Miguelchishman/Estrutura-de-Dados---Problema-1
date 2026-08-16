#ifndef ARRAY_H_
#define ARRAY_H_
#include "vetor.h"

typedef struct {
    Vetor* vetores;
    size_t tamanho;
    size_t capacidade;
} Array;

Array inicializar_array(size_t capacidade);
size_t inserir(Array* array, size_t dimensao);
void imprimir(Array array);
Vetor* buscar(Array* array, size_t indice);
void remover(Array* array, size_t indice);
void liberar_array(Array* array);


#endif