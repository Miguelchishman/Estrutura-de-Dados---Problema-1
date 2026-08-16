#include "array.h"
#include <stdlib.h>
#include <stdio.h>
Array inicializar_array(size_t capacidade){
    Array array = {0};
    array.vetores = malloc(sizeof(Vetor) * capacidade);;
    array.tamanho = 0;
    array.capacidade = capacidade;
    return array;
}

size_t inserir(Array* array, size_t dimensao){
    if (array->tamanho == array->capacidade){
        array->capacidade *= 2;
        Vetor* novo = realloc(array->vetores, sizeof(Vetor) * array->capacidade);
        if (novo == NULL){
            printf("Erro ao adicionar vetor\n");
            return 0;
        }
        array->vetores = novo;
    }

    array->vetores[array->tamanho].valores = malloc(sizeof(float) * dimensao);
    array->vetores[array->tamanho].dimensao = dimensao;

    return array->tamanho++;
}

void imprimir(Array array){
    printf("----------VETORES----------\n");

    if (array.tamanho == 0){
        printf("Array de vetores esta vazio. \n");
    }

    for (size_t i = 0; i < array.tamanho; i++){
        printf("%llu: Vetor[%llu] = ", i, array.vetores[i].dimensao);
        imprimir_vetor(array.vetores[i]);
    }

    printf("---------------------------\n");
}

Vetor* buscar(Array* array, size_t indice){
    if (indice >= array->tamanho) return NULL;
    return &array->vetores[indice];
}

void remover(Array* array, size_t indice){
    if (array->tamanho == 0){
        printf("Erro: nao existem vetores para remover\n");
        return;
    }

    if (indice >= array->tamanho){
        printf("Erro: indice invalido\n");
        return;
    }

    Vetor* vetor = buscar(array, indice);

    free(vetor->valores);

    for (size_t i = indice; i < array->tamanho; i++){
        array->vetores[indice] = array->vetores[indice + 1];
    }
    array->tamanho -= 1;
}


void liberar_array(Array* array){
    for (size_t i = 0; i < array->tamanho; i++){
        free(array->vetores[i].valores);
    }

    free(array->vetores);
}