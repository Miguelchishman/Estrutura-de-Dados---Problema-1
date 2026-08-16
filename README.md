Aplicação capaz de armazenar e manipular vetores de números reais utilizando arrays como estrutura de dados.


### Compilar programa

```console
gcc programa.c array.c vetor.c -o programa.exe
```

### Executar o programa após a compilação
```console
programa.exe
```


## Execução
Aplicação de terminal que implementa a biblioteca matematica de vetores e utiliza arrays para armazena-los. Permite o usuário inserir vetores e seus valores reais, remove-los do array por indice, listar todos os vetores do array e buscar vetores para realizar operações matemáticas sobre eles.
### Comandos
```console
Comandos:
    comandos     - Exibir os comandos disponiveis
    listar       - Listar atuais vetores
    inserir      - Inserir um vetor de n dimensoes
    remover      - Remover um vetor por indice
    buscar       - Buscar um vetor por indice e realizar operacoes matematicas nele
    sair         - Sair do programa
```

### Operações matemáticas
Ao buscar um vetor, é possível calcular a sua norma, calcular a sua soma com outro vetor, calcular a sua multiplicação por um escalar, calcular o produto escalar entre ele e outro vetor e calcular a similaridade de cosseno dele com outro vetor.

```console
Operacoes:
    operacoes               - Exibe as operacoes disponiveis
    norma                   - Calcular a norma do vetor
    soma                    - Calcular a soma entre esse vetor e outro
    multiplicar_escalar     - Calcular multiplicacao por escalar 
    produto_escalar         - Calcular o produto escalar entre esse vetor e outro
    similaridade            - Calcular a similaridade de cosseno entre esse vetor e outro
    sair                    - Voltar para a tela de comandos
```

### Exemplos
Inserir um vetor:

```console
Inserir a dimensao do vetor: 4
Inserir os valores do vetor de 4 dimensoes
Valor 1: 0.5
Valor 2: 3
Valor 3: 13
Valor 4: 94
Vetor: {0.500000, 3.000000, 13.000000, 94.000000} adicionado
```

Calcular a similaridade de cosseno entre dois vetores:
```console
----------VETORES----------
0: Vetor[4] = {0.500000, 3.000000, 13.000000, 94.000000}
1: Vetor[4] = {0.500000, 23.000000, 13.000000, -3.000000}
---------------------------
Digite o indice do vetor: 0
Operacoes:
    operacoes               - Exibe as operacoes disponiveis
    norma                   - Calcular a norma do vetor
    soma                    - Calcular a soma entre esse vetor e outro
    multiplicar_escalar     - Calcular multiplicacao por escalar 
    produto_escalar         - Calcular o produto escalar entre esse vetor e outro
    similaridade            - Calcular a similaridade de cosseno entre esse vetor e outro
    sair                    - Voltar para a tela de comandos
Vetor: {0.500000, 3.000000, 13.000000, 94.000000}
Digite 'operacoes' para listar as operacoes.
Digite uma operacao: similaridade
----------VETORES----------
0: Vetor[4] = {0.500000, 3.000000, 13.000000, 94.000000}
1: Vetor[4] = {0.500000, 23.000000, 13.000000, -3.000000}
---------------------------
Digite o indice do segundo vetor: 1
v1: {0.500000, 3.000000, 13.000000, 94.000000}
v2: {0.500000, 23.000000, 13.000000, -3.000000}
Sim(v1, v2) = -0.017327
```