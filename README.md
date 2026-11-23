 - Calculadora de Matrizes

## 1. Descricao do projeto

Este projeto consiste no desenvolvimento de uma calculadora de matrizes utilizando a linguagem de programacao C.

O programa permite que o usuario escolha a quantidade de matrizes, informe suas dimensoes e elementos e realize operacoes matematicas, apresentando ao final a matriz resultante.

## 2. Objetivo

Desenvolver um programa em linguagem C utilizando funcoes, estruturas de repeticao, matrizes, estruturas condicionais e modularizacao.

## 3. Funcionalidades

O sistema apresenta as seguintes opcoes:

1. Escolher a quantidade de matrizes.
2. Informar as dimensoes e os elementos das matrizes.
3. Realizar soma de matrizes.
4. Realizar subtracao de matrizes.
5. Realizar multiplicacao de matrizes.
6. Realizar divisao elemento por elemento.
7. Apresentar a matriz solucao.

## 4. Tecnologias utilizadas

- Linguagem C
- Online GDB
- GitHub

## 5 Como executar

**Requisito:** ter um compilador C instalado (por exemplo, GCC).

1. Baixe ou clone o repositório e abra a pasta no terminal.
2. Compile o programa:

   gcc calculadora.c -o calculadora -lm

3. Execute:

   - Linux ou Mac: `./calculadora`
   - Windows: `calculadora.exe`

4. Use o menu na ordem:
   - Opção 1: informe a quantidade de matrizes (mínimo 2).
   - Opção 2: informe as dimensões e os elementos de cada matriz.
   - Opções 3 a 6: escolha a operação (soma, subtração, multiplicação ou divisão).
   - Opção 7: veja novamente a matriz solução.
   - Opção 0: encerrar.

**Alternativa sem instalar nada:** copie o código do `calculadora.c` em um compilador online, como o onlinegdb.com, escolha a linguagem C e clique em Run.
## 6. Observacoes

- Para soma e subtracao, as matrizes precisam possuir as mesmas dimensoes.
- Para multiplicacao, as dimensoes precisam ser compativeis.
- A divisao e realizada elemento por elemento.
- O programa possui verificacao para evitar divisao por zero.

## 7. Arquivo do projeto

- calculadora.c: contem o codigo-fonte da calculadora de matrizes.
