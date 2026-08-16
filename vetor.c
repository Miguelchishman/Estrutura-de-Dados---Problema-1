#include "vetor.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
float norma_vetor(Vetor vetor1){
    float res = 0;

    for (size_t i = 0; i < vetor1.dimensao; i++){
        res += vetor1.valores[i] * vetor1.valores[i]; 
    }

    return sqrt(res);
}

float produto_escalar(Vetor vetor1, Vetor vetor2){
    if (vetor1.dimensao != vetor2.dimensao){
        printf("Erro: nao e possivel calcular o produto escalar entre 2 vetores com dimensoes diferentes\n");
        return NAN;
    }

    float res = 0;

    for (size_t i = 0; i < vetor1.dimensao; i++){
        res += vetor1.valores[i] * vetor2.valores[i];
    }

    return res;

}

float similaridade_de_cosseno(Vetor vetor1, Vetor vetor2){
    if (vetor1.dimensao != vetor2.dimensao){
        printf("Erro: nao e possivel calcular a similaridade de cossenos entre 2 vetores com dimensoes diferentes\n");
        return NAN;
    }

    if (norma_vetor(vetor1) == 0 || norma_vetor(vetor2) == 0){
        printf("Erro: nao e possivel calcular a similaridade de cossenos entre 2 vetores com um dos vetores sendo nulo\n");
        return NAN;
    }

    float res = produto_escalar(vetor1, vetor2) / (norma_vetor(vetor1) * norma_vetor(vetor2));

    return res;

}

Vetor soma_de_vetores(Vetor vetor1, Vetor vetor2){
    if (vetor1.dimensao != vetor2.dimensao){
        printf("Erro: nao e possivel calcular a soma de vetores entre 2 vetores com dimensoes diferentes\n");
        return (Vetor){0};
    }

    Vetor vetor_resultado = {0};
    vetor_resultado.valores = malloc(vetor1.dimensao * sizeof(float));
    vetor_resultado.dimensao = vetor1.dimensao;

    for (size_t i = 0; i < vetor1.dimensao; i++){
        vetor_resultado.valores[i] = vetor1.valores[i] + vetor2.valores[i];
    }
    return vetor_resultado;
}

Vetor multiplicar_escalar(Vetor vetor1, float escalar){
    Vetor vetor_resultado = {0};

    vetor_resultado.valores = malloc(vetor1.dimensao * sizeof(float));
    vetor_resultado.dimensao = vetor1.dimensao;

    for (size_t i = 0; i < vetor1.dimensao; i++){
        vetor_resultado.valores[i] = vetor1.valores[i] * escalar;
    }

    return vetor_resultado;
}

void imprimir_vetor(Vetor vetor){

    printf("{");
    for (size_t j = 0; j < vetor.dimensao; j++){
        if (j == vetor.dimensao - 1) printf("%f", vetor.valores[j]);
        else printf("%f, ", vetor.valores[j]);
    }
    printf("}");


}