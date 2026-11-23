/*
 * QUESTAO 01 - Calculadora de matrizes em linguagem C
 *
 * Operacoes: soma, subtracao, multiplicacao e divisao (A / B = A x B^-1).
 * Com 3 ou mais matrizes, as operacoes sao feitas sequencialmente,
 * da esquerda para a direita: ((A op B) op C) op D ...
 *
 * Organizacao do codigo:
 *   - Leitura:    lerInt, lerDouble, lerMatriz
 *   - Exibicao:   imprimirMatriz, mostrarMenu, exibirErro
 *   - Validacao:  mesmasDimensoes, podeMultiplicar, ehQuadrada
 *   - Operacoes:  somar, subtrair, multiplicar, inverter, dividir
 *   - Fluxo:      opcaoQuantidade, opcaoInformar, opcaoOperar, opcaoSolucao
 *   - main():     apenas coordena o menu principal
 *
 * Compilar: gcc questao1_calculadora_matrizes.c -o calculadora -lm
 * Executar: ./calculadora   (no Windows: calculadora.exe)
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_MATRIZES 10   /* maximo de matrizes informadas */
#define MAX_DIM 10        /* maximo de linhas/colunas de cada matriz */
#define EPSILON 1e-9      /* tolerancia para considerar o pivo igual a zero */

typedef struct {
    int lin, col;
    double d[MAX_DIM][MAX_DIM];
} Matriz;

/* Resultado de uma operacao: OP_OK ou o motivo do erro. */
typedef enum {
    OP_OK,
    ERRO_DIMENSAO_SOMA_SUB,   /* soma/subtracao exigem mesmas dimensoes */
    ERRO_DIMENSAO_MULT,       /* colunas da 1a diferente de linhas da 2a */
    ERRO_NAO_QUADRADA,        /* divisora nao e quadrada */
    ERRO_SINGULAR             /* divisora singular (sem inversa) */
} Status;

typedef Status (*Operacao)(const Matriz *, const Matriz *, Matriz *);

/* ---------- Prototipos ---------- */
int lerInt(const char *msg, int min, int max);
double lerDouble(const char *msg);
void lerMatriz(Matriz *m, int indice);

void imprimirMatriz(const Matriz *m);
void mostrarMenu(int qtd, int informadas, int temResultado);
void exibirErro(Status s, int etapa);

int mesmasDimensoes(const Matriz *a, const Matriz *b);
int podeMultiplicar(const Matriz *a, const Matriz *b);
int ehQuadrada(const Matriz *a);

Status somar(const Matriz *a, const Matriz *b, Matriz *r);
Status subtrair(const Matriz *a, const Matriz *b, Matriz *r);
Status multiplicar(const Matriz *a, const Matriz *b, Matriz *r);
Status inverter(const Matriz *a, Matriz *inv);
Status dividir(const Matriz *a, const Matriz *b, Matriz *r);
Status aplicarOperacao(Operacao op, const Matriz *mats, int qtd,
                       Matriz *resultado, int *etapaErro);

void opcaoQuantidade(int *qtd, int *informadas, int *temResultado);
void opcaoInformar(Matriz mats[], int qtd, int *informadas, int *temResultado);
void opcaoOperar(int opcao, const Matriz mats[], int qtd, int informadas,
                 Matriz *resultado, int *temResultado);
void opcaoSolucao(const Matriz *resultado, int temResultado);

/* ====================== LEITURA ====================== */

/* Le um inteiro entre min e max, repetindo ate o valor ser valido. */
int lerInt(const char *msg, int min, int max)
{
    char buf[64];
    int v;
    while (1) {
        printf("%s", msg);
        if (!fgets(buf, sizeof buf, stdin)) exit(0);
        if (sscanf(buf, "%d", &v) == 1 && v >= min && v <= max) return v;
        printf("Valor invalido! Digite um numero entre %d e %d.\n", min, max);
    }
}

/* Le um numero real, repetindo ate o valor ser valido. */
double lerDouble(const char *msg)
{
    char buf[64];
    double v;
    while (1) {
        printf("%s", msg);
        if (!fgets(buf, sizeof buf, stdin)) exit(0);
        if (sscanf(buf, "%lf", &v) == 1) return v;
        printf("Valor invalido!\n");
    }
}

/* Le dimensoes e elementos de uma matriz. */
void lerMatriz(Matriz *m, int indice)
{
    char msg[48];
    printf("\n--- Matriz %d ---\n", indice + 1);
    m->lin = lerInt("Numero de linhas: ", 1, MAX_DIM);
    m->col = lerInt("Numero de colunas: ", 1, MAX_DIM);
    for (int i = 0; i < m->lin; i++)
        for (int j = 0; j < m->col; j++) {
            sprintf(msg, "Elemento [%d][%d]: ", i + 1, j + 1);
            m->d[i][j] = lerDouble(msg);
        }
}

/* ====================== EXIBICAO ====================== */

void imprimirMatriz(const Matriz *m)
{
    for (int i = 0; i < m->lin; i++) {
        printf("| ");
        for (int j = 0; j < m->col; j++) printf("%9.3f ", m->d[i][j]);
        printf("|\n");
    }
}

void mostrarMenu(int qtd, int informadas, int temResultado)
{
    printf("\n========= CALCULADORA DE MATRIZES =========\n");
    printf("Matrizes: %d | Informadas: %s | Solucao: %s\n",
           qtd, informadas ? "sim" : "nao", temResultado ? "sim" : "nao");
    printf("1 - Escolher a quantidade de matrizes\n");
    printf("2 - Informar matrizes (apenas se informou a quantidade)\n");
    printf("3 - Soma de matrizes\n");
    printf("4 - Subtracao de matrizes\n");
    printf("5 - Multiplicacao de matrizes\n");
    printf("6 - Divisao de matrizes\n");
    printf("7 - Apresentar a matriz solucao\n");
    printf("0 - Sair\n");
}

/* Explica ao usuario por que a operacao nao pode ser feita.
 * 'etapa' e a posicao da matriz que causou o erro (a partir de 2). */
void exibirErro(Status s, int etapa)
{
    printf("\nErro na etapa %d (resultado parcial com a Matriz %d): ", etapa - 1, etapa);
    switch (s) {
    case ERRO_DIMENSAO_SOMA_SUB:
        printf("soma e subtracao exigem matrizes com as mesmas dimensoes.\n");
        break;
    case ERRO_DIMENSAO_MULT:
        printf("o numero de colunas da primeira matriz deve ser igual ao\n"
               "numero de linhas da segunda matriz.\n");
        break;
    case ERRO_NAO_QUADRADA:
        printf("a matriz divisora precisa ser quadrada para ter inversa.\n");
        break;
    case ERRO_SINGULAR:
        printf("a matriz divisora e SINGULAR (determinante zero) e nao possui inversa.\n");
        break;
    default:
        break;
    }
}

/* ====================== VALIDACAO ====================== */

int mesmasDimensoes(const Matriz *a, const Matriz *b)
{
    return a->lin == b->lin && a->col == b->col;
}

int podeMultiplicar(const Matriz *a, const Matriz *b)
{
    return a->col == b->lin;
}

int ehQuadrada(const Matriz *a)
{
    return a->lin == a->col;
}

/* ====================== OPERACOES ====================== */

Status somar(const Matriz *a, const Matriz *b, Matriz *r)
{
    if (!mesmasDimensoes(a, b)) return ERRO_DIMENSAO_SOMA_SUB;
    r->lin = a->lin; r->col = a->col;
    for (int i = 0; i < r->lin; i++)
        for (int j = 0; j < r->col; j++)
            r->d[i][j] = a->d[i][j] + b->d[i][j];
    return OP_OK;
}

Status subtrair(const Matriz *a, const Matriz *b, Matriz *r)
{
    if (!mesmasDimensoes(a, b)) return ERRO_DIMENSAO_SOMA_SUB;
    r->lin = a->lin; r->col = a->col;
    for (int i = 0; i < r->lin; i++)
        for (int j = 0; j < r->col; j++)
            r->d[i][j] = a->d[i][j] - b->d[i][j];
    return OP_OK;
}

Status multiplicar(const Matriz *a, const Matriz *b, Matriz *r)
{
    if (!podeMultiplicar(a, b)) return ERRO_DIMENSAO_MULT;
    Matriz t;   /* temporario: r pode ser o mesmo objeto que a ou b */
    t.lin = a->lin; t.col = b->col;
    for (int i = 0; i < t.lin; i++)
        for (int j = 0; j < t.col; j++) {
            t.d[i][j] = 0;
            for (int k = 0; k < a->col; k++)
                t.d[i][j] += a->d[i][k] * b->d[k][j];
        }
    *r = t;
    return OP_OK;
}

/* Inversa pelo metodo de Gauss-Jordan com pivoteamento parcial. */
Status inverter(const Matriz *a, Matriz *inv)
{
    if (!ehQuadrada(a)) return ERRO_NAO_QUADRADA;

    int n = a->lin;
    double aug[MAX_DIM][2 * MAX_DIM];   /* matriz aumentada [A | I] */
    double maior = 1.0;                 /* escala para a tolerancia */

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            aug[i][j] = a->d[i][j];
            aug[i][j + n] = (i == j) ? 1.0 : 0.0;
            if (fabs(a->d[i][j]) > maior) maior = fabs(a->d[i][j]);
        }

    for (int c = 0; c < n; c++) {
        int p = c;                       /* escolhe o maior pivo da coluna */
        for (int i = c + 1; i < n; i++)
            if (fabs(aug[i][c]) > fabs(aug[p][c])) p = i;
        if (fabs(aug[p][c]) < EPSILON * maior) return ERRO_SINGULAR;

        if (p != c)
            for (int j = 0; j < 2 * n; j++) {
                double t = aug[c][j]; aug[c][j] = aug[p][j]; aug[p][j] = t;
            }

        double piv = aug[c][c];
        for (int j = 0; j < 2 * n; j++) aug[c][j] /= piv;

        for (int i = 0; i < n; i++)
            if (i != c) {
                double f = aug[i][c];
                for (int j = 0; j < 2 * n; j++) aug[i][j] -= f * aug[c][j];
            }
    }

    inv->lin = inv->col = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) inv->d[i][j] = aug[i][j + n];
    return OP_OK;
}

/* Divisao: A / B = A x B^-1 (B quadrada, inversivel e compativel com A). */
Status dividir(const Matriz *a, const Matriz *b, Matriz *r)
{
    Matriz inv;
    Status s = inverter(b, &inv);
    if (s != OP_OK) return s;
    return multiplicar(a, &inv, r);
}

/* Aplica a operacao da esquerda para a direita em todas as matrizes.
 * Em caso de erro, *etapaErro recebe a posicao da matriz problematica. */
Status aplicarOperacao(Operacao op, const Matriz *mats, int qtd,
                       Matriz *resultado, int *etapaErro)
{
    *resultado = mats[0];
    for (int i = 1; i < qtd; i++) {
        Matriz tmp;
        Status s = op(resultado, &mats[i], &tmp);
        if (s != OP_OK) {
            *etapaErro = i + 1;
            return s;
        }
        *resultado = tmp;
    }
    return OP_OK;
}

/* ====================== FLUXO DO MENU ====================== */

void opcaoQuantidade(int *qtd, int *informadas, int *temResultado)
{
    char msg[64];
    sprintf(msg, "Quantidade de matrizes (2 a %d): ", MAX_MATRIZES);
    *qtd = lerInt(msg, 2, MAX_MATRIZES);
    *informadas = 0;
    *temResultado = 0;
}

void opcaoInformar(Matriz mats[], int qtd, int *informadas, int *temResultado)
{
    if (qtd == 0) {
        printf("Informe primeiro a quantidade de matrizes (opcao 1).\n");
        return;
    }
    for (int i = 0; i < qtd; i++) lerMatriz(&mats[i], i);
    *informadas = 1;
    *temResultado = 0;
}

void opcaoOperar(int opcao, const Matriz mats[], int qtd, int informadas,
                 Matriz *resultado, int *temResultado)
{
    if (!informadas) {
        printf("Informe as matrizes primeiro (opcao 2).\n");
        return;
    }

    Operacao op = (opcao == 3) ? somar :
                  (opcao == 4) ? subtrair :
                  (opcao == 5) ? multiplicar : dividir;

    int etapa = 0;
    Status s = aplicarOperacao(op, mats, qtd, resultado, &etapa);
    if (s == OP_OK) {
        *temResultado = 1;
        printf("Operacao realizada! Use a opcao 7 para ver a solucao.\n");
    } else {
        *temResultado = 0;
        exibirErro(s, etapa);
    }
}

void opcaoSolucao(const Matriz *resultado, int temResultado)
{
    if (!temResultado) {
        printf("Nenhuma solucao disponivel. Realize uma operacao antes.\n");
        return;
    }
    printf("\n--- MATRIZ SOLUCAO (%dx%d) ---\n", resultado->lin, resultado->col);
    imprimirMatriz(resultado);
}

/* ====================== PROGRAMA PRINCIPAL ====================== */

int main(void)
{
    Matriz mats[MAX_MATRIZES], resultado;
    int qtd = 0, informadas = 0, temResultado = 0, opcao;

    do {
        mostrarMenu(qtd, informadas, temResultado);
        opcao = lerInt("Opcao: ", 0, 7);

        switch (opcao) {
        case 1: opcaoQuantidade(&qtd, &informadas, &temResultado); break;
        case 2: opcaoInformar(mats, qtd, &informadas, &temResultado); break;
        case 3: case 4: case 5: case 6:
            opcaoOperar(opcao, mats, qtd, informadas, &resultado, &temResultado);
            break;
        case 7: opcaoSolucao(&resultado, temResultado); break;
        }
    } while (opcao != 0);

    printf("Encerrando...\n");
    return 0;
}
