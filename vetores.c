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

void buscar_loop(Array* array);
void imprimir_operacoes();


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

size_t inserir(Array* array, size_t dimensao){
    if (array->tamanho == array->capacidade){
        array->capacidade *= 2;
        Vetor* novo = realloc(array->vetores, sizeof(Vetor) * array->capacidade);
        if (novo == NULL){
            printf("Erro ao adicionar vetor\n");
            return NAN;
        }
        array->vetores = novo;
    }

    array->vetores[array->tamanho].valores = malloc(sizeof(float) * dimensao);
    array->vetores[array->tamanho].dimensao = dimensao;

    return array->tamanho++;
}

void imprimir_vetor(Vetor vetor){

    printf("{");
    for (size_t j = 0; j < vetor.dimensao; j++){
        if (j == vetor.dimensao - 1) printf("%f", vetor.valores[j]);
        else printf("%f, ", vetor.valores[j]);
    }
    printf("}\n");


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

void terminal_inserir(Array* array){
    char buffer[256] = {0};
    char *endptr;

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
    size_t indice_adicionado = inserir(array, dimensao);

    printf("Inserir os valores do vetor de %llu dimensoes\n", dimensao);
    for (size_t i = 0; i < dimensao;){
        printf("Valor %llu: ", i+1);
        fgets(buffer, 256, stdin);
        float valor = (float) strtod(buffer, &endptr);

        if (buffer == endptr) {
            printf("\nErro: numero invalido, por favor tente novamente\n");
        } else {
            array->vetores[indice_adicionado].valores[i] = valor;
            i++;
        }

    }   
}

void terminal_remover(Array* array){
    char buffer[256] = {0};
    char *endptr;

    printf("Digite o indice do vetor a ser removido: \n");
    fgets(buffer, 256, stdin);
    arrumar_string(buffer);
    size_t indice = (size_t) strtol(buffer, &endptr, 10);

    remover(array, indice);
    printf("Vetor removido\n");
}

void terminal_somar(Array* array, Vetor* vetor1){
    char buffer[256] = {0};
    char* endptr;
    printf("Digite o indice do segundo vetor: ");
    fgets(buffer, 256, stdin);
    arrumar_string(buffer);
    size_t indice = (size_t) strtol(buffer, &endptr, 10);

    if (buffer == endptr){
        printf("Erro: escalar invalido\n");
        return;
    }

    if (indice >= array->tamanho){
        printf("Erro: indice invalido!\n");
        return;
    }
    Vetor* vetor2 = buscar(array, indice);

    Vetor vetor_resultado = soma_de_vetores(*vetor1, *vetor2);

    printf("+ ");
    imprimir_vetor(*vetor1);
    printf("  ");
    imprimir_vetor(*vetor2);
    printf("--------------\n  ");
    imprimir_vetor(vetor_resultado);
    free(vetor_resultado.valores);
}

void terminal_multiplicar_escalar(Vetor* vetor){
    char buffer[256] = {0};
    char* endptr;
    printf("Digite o escalar: ");
    fgets(buffer, 256, stdin);
    arrumar_string(buffer);
    float escalar = (float) strtod(buffer, &endptr);
    
    if (buffer == endptr){
        printf("Erro: escalar invalido\n");
        return;
    }

    Vetor vetor_resultado = multiplicar_escalar(*vetor, escalar);

    printf("* ");
    imprimir_vetor(*vetor);
    printf("  %f\n", escalar);
    printf("--------------\n  ");
    imprimir_vetor(vetor_resultado);
    free(vetor_resultado.valores);
}

void terminal_produto_escalar(Array* array, Vetor* vetor1){
    char buffer[256] = {0};
    char* endptr;
    printf("Digite o indice do segundo vetor: ");
    fgets(buffer, 256, stdin);
    arrumar_string(buffer);
    size_t indice = (size_t) strtol(buffer, &endptr, 10);

    if (indice >= array->tamanho || buffer == endptr){
        printf("Erro: indice invalido!\n");
        return;
    }
    Vetor* vetor2 = buscar(array, indice);

    float resultado = produto_escalar(*vetor1, *vetor2);

    printf("* ");
    imprimir_vetor(*vetor1);
    printf("  ");
    imprimir_vetor(*vetor2);
    printf("--------------\n");
    printf("  %f\n", resultado);
}   

void terminal_similaridade(Array* array, Vetor* vetor1){
    char buffer[256] = {0};
    char* endptr;
    printf("Digite o indice do segundo vetor: ");
    fgets(buffer, 256, stdin);
    arrumar_string(buffer);
    size_t indice = (size_t) strtol(buffer, &endptr, 10);

    if (indice >= array->tamanho || buffer == endptr){
        printf("Erro: indice invalido!\n");
        return;
    }
    Vetor* vetor2 = buscar(array, indice);

    float similaridade = similaridade_de_cosseno(*vetor1, *vetor2);

    printf("v1: ");
    imprimir_vetor(*vetor1);
    printf("v2: ");
    imprimir_vetor(*vetor2);
    printf("Sim(v1, v2) = %f\n", similaridade);
}

void imprimir_comandos(){
    printf("Comandos:\n");
    printf("    comandos     - Exibir os comandos disponiveis\n");
    printf("    listar       - Listar atuais vetores\n");
    printf("    inserir      - Inserir um vetor de n dimensoes\n");
    printf("    remover      - Remover um vetor por indice\n");
    printf("    buscar       - Buscar um vetor por indice e realizar operacoes matematicas nele\n");
    printf("    sair         - Sair do programa\n");
}

void loop_programa(Array* array){
    int sair = 0;
    char buffer[256] = {0};
    while (!sair){
        printf("\nDigite 'comandos' para listar os comandos.\n");
        printf("Digite um comando: ");
        fgets(buffer, 256, stdin);
        arrumar_string(buffer);

        if (strcmp(buffer, "comandos") == 0){
            imprimir_comandos();
        } else if (strcmp(buffer, "listar") == 0){
            imprimir(*array);
        } else if (strcmp(buffer, "inserir") == 0){
            terminal_inserir(array);
        } else if (strcmp(buffer, "remover") == 0){
            imprimir(*array);
            terminal_remover(array);
        } else if (strcmp(buffer, "buscar") == 0){
            imprimir(*array);
            buscar_loop(array);
        } else if (strcmp(buffer, "sair") == 0){
            sair = 1;
        } else {
            printf("Comando: %s nao encontrado\n", buffer);
        }
    }
}

void imprimir_operacoes(){
    printf("Operacoes:\n");
    printf("    operacoes               - Exibe as operacoes disponiveis\n");
    printf("    norma                   - Calcular a norma do vetor\n");
    printf("    soma                    - Calcular a soma entre esse vetor e outro\n");
    printf("    multiplicar_escalar     - Calcular multiplicacao por escalar \n");
    printf("    produto_escalar         - Calcular o produto escalar entre esse vetor e outro\n");
    printf("    similaridade            - Calcular a similaridade de cosseno entre esse vetor e outro\n");
    printf("    sair                  - Voltar para a tela de comandos\n");

}

void buscar_loop(Array* array){
    char buffer[256] = {0};
    char *endptr;

    if (array->tamanho == 0){
        printf("Erro: nao existem vetores no array \n");
        return;
    }


    printf("Digite o indice do vetor: ");
    fgets(buffer, 256, stdin);
    arrumar_string(buffer);
    size_t indice = (size_t) strtol(buffer, &endptr, 10);

    if (indice >= array->tamanho){
        printf("Erro: indice invalido!\n");
        return;
    }

    Vetor* vetor = buscar(array, indice); 
    imprimir_operacoes();
    printf("Vetor: ");
    imprimir_vetor(*vetor);
    
    int voltar = 0;
    while (!voltar){
        printf("\nDigite 'operacoes' para listar as operacoes.\n");
        printf("Digite uma operacao: ");
        fgets(buffer, 256, stdin);
        arrumar_string(buffer);

        if (strcmp(buffer, "operacoes") == 0){
            imprimir_operacoes();
        } else if (strcmp(buffer, "norma") == 0){
            printf("Norma: %f\n", norma_vetor(*vetor));
        } else if (strcmp(buffer, "soma") == 0){
            imprimir(*array);
            terminal_somar(array, vetor);

        } else if (strcmp(buffer, "multiplicar_escalar") == 0){
            terminal_multiplicar_escalar(vetor);
        } else if (strcmp(buffer, "produto_escalar") == 0){
            imprimir(*array);
            terminal_produto_escalar(array, vetor);
        } else if (strcmp(buffer, "similaridade") == 0){
            imprimir(*array);
            terminal_similaridade(array, vetor);
        } else if (strcmp(buffer, "sair") == 0){
            voltar = 1;
        } else {
            printf("Erro: comando %s nao encontrado \n", buffer);
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
    // char buffer[255] = {0};
    Array array = inicializar_array(32);
    imprimir_comandos();
    loop_programa(&array);
    return 0;
}