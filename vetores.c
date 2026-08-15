#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    float* valores;
    size_t dimensao;
} Vetor;


typedef struct {
    Vetor* vetores;
    size_t tamanho;
    size_t capacidade;
} Array;


Array inicializar_array(size_t capacidade){
    Array array = {0};
    array.vetores = malloc(sizeof(Vetor) * capacidade);;
    array.tamanho = 0;
    array.capacidade = capacidade;
    return array;
}

void arrumar_string(char* string){
    int comeco = 0;
    int fim = strlen(string) - 1;


    while (isspace(string[comeco]) && comeco < fim){
        comeco++;
    }

    while(isspace(string[fim]) && fim > comeco){
        fim--;
    }

    for(int i = 0; i + comeco < fim + 1; i++){
        string[i] = string[i + comeco];
    }

    string[fim-comeco+1] = '\0';

}

void inserir(Array* array){
    char buffer[256] = {0};
    char *endptr;
    if (array->tamanho == array->capacidade){
        array->capacidade *= 2;
        Vetor* novo = realloc(array->vetores, sizeof(Vetor) * array->capacidade);
        if (novo == NULL){
            printf("Erro ao adicionar vetor\n");
            return;
        }
        array->vetores = novo;
    }

    printf("Inserir a dimensao do vetor: \n");
    fgets(buffer, 256, stdin);
    arrumar_string(buffer);

    size_t dimensao = (size_t) strtol(buffer, &endptr, 10);
    if (dimensao < 1){
        printf("Erro: valor invalido para dimensao\n");
        return;
    }

    if (buffer == endptr) {
        printf("Erro: numero invalido\n");
        return;
    }


    array->vetores[array->tamanho].valores = malloc(sizeof(float) * dimensao);
    array->vetores[array->tamanho].dimensao = dimensao;

    printf("Inserir os valores do vetor de %llu dimensoes\n", dimensao);
    for (size_t i = 0; i < dimensao; i++){
        printf("Valor %llu: ", i);
        fgets(buffer, 256, stdin);
        float valor = (float) strtod(buffer, &endptr);

        if (buffer == endptr) {
            printf("\nErro: numero invalido\n");
            return;
        }

        array->vetores[array->tamanho].valores[i] = valor;
    }   


    array->tamanho++;
}

void imprimir(Array array){
    printf("----------VETORES----------\n");

    if (array.tamanho == 0){
        printf("Array de vetores esta vazio. \n");
    }

    for (size_t i = 0; i < array.tamanho; i++){
        printf("%llu: Vetor[%llu] = {", i + 1,  array.vetores[i].dimensao);
        for (size_t j = 0; j < array.vetores[i].dimensao; j++){
            if (j == array.vetores[i].dimensao - 1) printf("%f", array.vetores[i].valores[j]);
            else printf("%f, ", array.vetores[i].valores[j]);
        }
        printf("}\n");
        
    }

    printf("---------------------------\n");
}

void imprimir_comandos(){
    printf("Comandos:\n");
    printf("    listar       - Listar atuais vetores\n");
    printf("    inserir      - Inserir um vetor de n dimensoes\n");
    printf("    remover      - Remover um vetor por indice\n");
    printf("    sair         - Sair do programa\n");
}


void loop_programa(Array* array){
    int sair = 0;
    char buffer[256] = {0};
    while (!sair){
        imprimir_comandos();
        fgets(buffer, 256, stdin);
        arrumar_string(buffer);

        if (strcmp(buffer, "listar") == 0){
            imprimir(*array);
        } else if (strcmp(buffer, "inserir") == 0){
            inserir(array);
        } else if (strcmp(buffer, "remover") == 0){
            
        } else if (strcmp(buffer, "sair") == 0){
            sair = 1;
        } else {
            printf("Comando: %s nao encontrado\n", buffer);
        }
    }
}


// int main(void){
//     char mensagem[] = "  Ola meu amigo      ";
//     arrumar_string(mensagem);
//     printf("%s\n", mensagem);
//     return 0;
// }

int main(void){
    char buffer[255] = {0};
    Array array = inicializar_array(32);
    loop_programa(&array);
    return 0;
}