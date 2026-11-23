# Calculadora de Matrizes

## 1. Descrição do projeto

Este projeto consiste no desenvolvimento de uma calculadora de matrizes utilizando a linguagem de programação C.

O programa permite que o usuário escolha a quantidade de matrizes, informe suas dimensões e elementos e realize operações matemáticas, apresentando a matriz resultante.

## 2. Objetivo

Desenvolver um programa em linguagem C utilizando funções, estruturas de repetição, matrizes, estruturas condicionais e modularização.

## 3. Funcionalidades

O sistema apresenta as seguintes opções:

1. Escolher a quantidade de matrizes.
2. Informar as dimensões e os elementos das matrizes.
3. Realizar soma de matrizes.
4. Realizar subtração de matrizes.
5. Realizar multiplicação de matrizes.
6. Realizar divisão de matrizes.
7. Apresentar a matriz solução.
0. Sair.

## 4. Tecnologias utilizadas

- Linguagem C
- Online GDB
- GitHub

## 5. Como executar

**Requisito:** ter um compilador C instalado (por exemplo, GCC).

1. Baixe ou clone o repositório e abra a pasta no terminal.
2. Compile o programa:

   ```
   gcc calculadora.c -o calculadora -lm
   ```

3. Execute:
   - Linux ou Mac: `./calculadora`
   - Windows: `calculadora.exe`

4. Use o menu na ordem:
   - Opção 1: informe a quantidade de matrizes (mínimo 2).
   - Opção 2: informe as dimensões e os elementos de cada matriz.
   - Opções 3 a 6: escolha a operação.
   - Opção 7: veja novamente a matriz solução.
   - Opção 0: encerrar.

**Alternativa sem instalar nada:** copie o código do `calculadora.c` em um compilador online, como o onlinegdb.com, escolha a linguagem C e clique em Run.

## 6. Regras das operações

- **Soma e subtração:** as matrizes precisam ter as mesmas dimensões.
- **Multiplicação:** o número de colunas da primeira matriz deve ser igual ao número de linhas da segunda, em cada etapa.
- **Divisão:** é feita como A ÷ B = A × B⁻¹. A matriz divisora precisa ser quadrada e inversível. Se for singular (sem inversa), o programa informa o erro.
- Com três ou mais matrizes, as operações são feitas sequencialmente, da esquerda para a direita.
- Quando uma operação não pode ser realizada, o programa explica o motivo.

## 7. Limites do programa

- Até 10 matrizes.
- Cada matriz com no máximo 10 linhas e 10 colunas.

## 8. Arquivos do projeto

- `calculadora.c`: contém o código-fonte da calculadora de matrizes.
- `README.md`: descrição e instruções de execução.
