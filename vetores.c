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
    array.vetores = NULL;
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

}

void imprimir_comandos(){
    printf("Comandos:\n");
    printf("    listar       - Listar atuais vetores\n");
    printf("    inserir      - Inserir um vetor de n dimensoes\n");
    printf("    remover      - Remover um vetor por indice\n");
    printf("    sair         - Sair do programa\n");
}


void loop_programa(){
    int sair = 0;
    char buffer[256] = {0};
    while (!sair){
        imprimir_comandos();
        fgets(buffer, 256, stdin);
        arrumar_string(buffer);

        if (strcmp(buffer, "listar") == 0){

        } else if (strcmp(buffer, "inserir") == 0){

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
    loop_programa();
    return 0;
}