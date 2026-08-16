#ifndef VETOR_H_
#define VETOR_H_

#include <stddef.h>

typedef struct {
    float* valores;
    size_t dimensao;
} Vetor;

float norma_vetor(Vetor vetor1);
float produto_escalar(Vetor vetor1, Vetor vetor2);
float similaridade_de_cosseno(Vetor vetor1, Vetor vetor2);
Vetor soma_de_vetores(Vetor vetor1, Vetor vetor2);
Vetor multiplicar_escalar(Vetor vetor1, float escalar);
void imprimir_vetor(Vetor vetor);


#endif