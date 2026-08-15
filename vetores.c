#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
typedef struct {
    float* valores;
    size_t dimensao;
} Vetor;


typedef struct {
    Vetor* vetores;
    size_t tamanho;
    size_t capacidade;
} Array;

float norma_vetor(Vetor vetor1){
    // if (vetor1.dimensao != vetor2.dimensao){
    //     printf("Erro: nao e possivel calcular a norma entre 2 vetores com dimensoes diferentes\n");
    //     return NAN;
    // }
    float res = 0;

    for (int i = 0; i < vetor1.dimensao; i++){
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

    for (int i = 0; i < vetor1.dimensao; i++){
        res += vetor1.valores[i] * vetor2.valores[i];
    }

    return res;

}

float similaridade_de_cosseno(Vetor vetor1, Vetor vetor2){
    if (vetor1.dimensao != vetor2.dimensao){
        printf("Erro: nao e possivel calcular a similaridade de cossenos entre 2 vetores com dimensoes diferentes\n");
        return NAN;
    }

    float res = produto_escalar(vetor1, vetor2) / (norma_vetor(vetor1) * norma_vetor(vetor2));

    return res;

}

Vetor* soma_de_vetores(Vetor vetor1, Vetor vetor2){
    if (vetor1.dimensao != vetor2.dimensao){
        printf("Erro: nao e possivel calcular a soma de vetores entre 2 vetores com dimensoes diferentes\n");
        return NULL;
    }

    Vetor* vetor_resultado = {0};

    vetor_resultado->valores = malloc(vetor1.dimensao * sizeof(float));
    vetor_resultado->dimensao = vetor1.dimensao;

    for (int i = 0; i < vetor1.dimensao; i++){
        vetor_resultado->valores[i] = vetor1.valores[i] + vetor2.valores[i];
    }
    return vetor_resultado;
}

Vetor* multiplicar_escalar(Vetor vetor1, float escalar){
    Vetor* vetor_resultado = {0};

    vetor_resultado->valores = malloc(vetor1.dimensao * sizeof(float));
    vetor_resultado->dimensao = vetor1.dimensao;

    for (int i = 0; i < vetor1.dimensao; i++){
        vetor_resultado->valores[i] = vetor1.valores[i] * escalar;
    }

    return vetor_resultado;
}




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
    for (size_t i = 0; i < dimensao;){
        printf("Valor %llu: ", i+1);
        fgets(buffer, 256, stdin);
        float valor = (float) strtod(buffer, &endptr);

        if (buffer == endptr) {
            printf("\nErro: numero invalido, por favor tente novamente\n");
        } else {
            array->vetores[array->tamanho].valores[i] = valor;
            i++;
        }

    }   


    array->tamanho++;
}

void imprimir(Array array){
    printf("----------VETORES----------\n");

    if (array.tamanho == 0){
        printf("Array de vetores esta vazio. \n");
    }

    for (size_t i = 0; i < array.tamanho; i++){
        printf("%llu: Vetor[%llu] = {", i,  array.vetores[i].dimensao);
        for (size_t j = 0; j < array.vetores[i].dimensao; j++){
            if (j == array.vetores[i].dimensao - 1) printf("%f", array.vetores[i].valores[j]);
            else printf("%f, ", array.vetores[i].valores[j]);
        }
        printf("}\n");
        
    }

    printf("---------------------------\n");
}

Vetor* buscar(Array* array, size_t indice){
    if (indice >= array->tamanho) return NULL;
    return &array->vetores[indice];
}


void remover(Array* array){
    char buffer[256] = {0};
    char *endptr;

    if (array->tamanho == 0){
        printf("Erro: nao existem vetores para remover\n");
        return;
    }


    printf("Digite o indice do vetor a ser removido: \n");
    fgets(buffer, 256, stdin);
    arrumar_string(buffer);
    size_t indice = (size_t) strtol(buffer, &endptr, 10);


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
    printf("Vetor removido\n");
}

void imprimir_comandos(){
    printf("Comandos:\n");
    printf("    listar       - Listar atuais vetores\n");
    printf("    inserir      - Inserir um vetor de n dimensoes\n");
    printf("    remover      - Remover um vetor por indice\n");
    printf("    buscar       - Buscar um vetor por indice e realizar operacoes matematicas\n");
    printf("    sair         - Sair do programa\n");
}

void imprimir_operacoes(){
    printf("Operacoes:\n");
    printf("    norma                   - Calcular a norma do vetor\n");
    printf("    soma                    - Calcular a soma entre esse vetor e outro\n");
    printf("    multiplicar_escalar     - Calcular multiplicacao por escalar \n");
    printf("    produto_escalar         - Calcular o produto escalar entre esse vetor e outro\n");
    printf("    similaridade            - Calcular a similaridade de cosseno entre esse vetor e outro\n");

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
            imprimir(*array);
            remover(array);
        } else if (strcmp(buffer, "buscar") == 0){
            imprimir(*array);
            printf("Nao implementado ainda \n");
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