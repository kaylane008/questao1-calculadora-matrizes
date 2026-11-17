
#include <stdio.h>

#define MAX_MATRIZES 10
#define MAX_LINHAS 10
#define MAX_COLUNAS 10

typedef struct {
    int linhas;
    int colunas;
    double valores[MAX_LINHAS][MAX_COLUNAS];
} Matriz;

void menu() {
    printf("\n===== CALCULADORA DE MATRIZES =====\n");
    printf("1 - Escolher quantidade de matrizes\n");
    printf("2 - Informar matrizes\n");
    printf("3 - Somar matrizes\n");
    printf("4 - Subtrair matrizes\n");
    printf("5 - Multiplicar matrizes\n");
    printf("6 - Dividir matrizes\n");
    printf("7 - Apresentar matriz solucao\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

void escolherQuantidade(int *qtd) {
    do {
        printf("Quantidade de matrizes (2 a 10): ");
        scanf("%d", qtd);

        if (*qtd < 2 || *qtd > MAX_MATRIZES) {
            printf("Quantidade invalida!\n");
        }
    } while (*qtd < 2 || *qtd > MAX_MATRIZES);
}

void informarMatrizes(Matriz m[], int qtd) {
    int i, l, c;

    for (i = 0; i < qtd; i++) {
        printf("\nMATRIZ %d\n", i + 1);

        do {
            printf("Numero de linhas (1 a 10): ");
            scanf("%d", &m[i].linhas);
        } while (m[i].linhas < 1 || m[i].linhas > 10);

        do {
            printf("Numero de colunas (1 a 10): ");
            scanf("%d", &m[i].colunas);
        } while (m[i].colunas < 1 || m[i].colunas > 10);

        for (l = 0; l < m[i].linhas; l++) {
            for (c = 0; c < m[i].colunas; c++) {
                printf("Elemento [%d][%d]: ", l + 1, c + 1);
                scanf("%lf", &m[i].valores[l][c]);
            }
        }
    }
}

int mesmasDimensoes(Matriz m[], int qtd) {
    int i;

    for (i = 1; i < qtd; i++) {
        if (m[i].linhas != m[0].linhas ||
            m[i].colunas != m[0].colunas) {
            return 0;
        }
    }

    return 1;
}

void apresentarMatriz(Matriz *r) {
    int l, c;

    for (l = 0; l < r->linhas; l++) {
        for (c = 0; c < r->colunas; c++) {
            printf("%.2lf\t", r->valores[l][c]);
        }
        printf("\n");
    }
}

int somar(Matriz m[], int qtd, Matriz *r) {
    int i, l, c;

    if (!mesmasDimensoes(m, qtd)) {
        printf("As matrizes precisam ter as mesmas dimensoes!\n");
        return 0;
    }

    r->linhas = m[0].linhas;
    r->colunas = m[0].colunas;

    for (l = 0; l < r->linhas; l++) {
        for (c = 0; c < r->colunas; c++) {
            r->valores[l][c] = 0;

            for (i = 0; i < qtd; i++) {
                r->valores[l][c] += m[i].valores[l][c];
            }
        }
    }

    return 1;
}

int subtrair(Matriz m[], int qtd, Matriz *r) {
    int i, l, c;

    if (!mesmasDimensoes(m, qtd)) {
        printf("As matrizes precisam ter as mesmas dimensoes!\n");
        return 0;
    }

    r->linhas = m[0].linhas;
    r->colunas = m[0].colunas;

    for (l = 0; l < r->linhas; l++) {
        for (c = 0; c < r->colunas; c++) {
            r->valores[l][c] = m[0].valores[l][c];

            for (i = 1; i < qtd; i++) {
                r->valores[l][c] -= m[i].valores[l][c];
            }
        }
    }

    return 1;
}

int multiplicar(Matriz m[], int qtd, Matriz *r) {
    Matriz temp = m[0];
    Matriz aux;

    int i, l, c, k;

    for (i = 1; i < qtd; i++) {

        if (temp.colunas != m[i].linhas) {
            printf("Dimensoes incompatíveis para multiplicacao!\n");
            return 0;
        }

        aux.linhas = temp.linhas;
        aux.colunas = m[i].colunas;

        for (l = 0; l < aux.linhas; l++) {
            for (c = 0; c < aux.colunas; c++) {
                aux.valores[l][c] = 0;

                for (k = 0; k < temp.colunas; k++) {
                    aux.valores[l][c] +=
                        temp.valores[l][k] * m[i].valores[k][c];
                }
            }
        }

        temp = aux;
    }

    *r = temp;
    return 1;
}

int dividir(Matriz m[], int qtd, Matriz *r) {
    int i, l, c;
    double valor;

    if (!mesmasDimensoes(m, qtd)) {
        printf("As matrizes precisam ter as mesmas dimensoes!\n");
        return 0;
    }

    r->linhas = m[0].linhas;
    r->colunas = m[0].colunas;

    for (l = 0; l < r->linhas; l++) {
        for (c = 0; c < r->colunas; c++) {

            valor = m[0].valores[l][c];

            for (i = 1; i < qtd; i++) {
                if (m[i].valores[l][c] == 0) {
                    printf("Nao e possivel dividir por zero!\n");
                    return 0;
                }

                valor /= m[i].valores[l][c];
            }

            r->valores[l][c] = valor;
        }
    }

    return 1;
}

int main() {
    Matriz matrizes[MAX_MATRIZES];
    Matriz resultado;

    int qtd = 0;
    int informadas = 0;
    int existeResultado = 0;
    int opcao;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                escolherQuantidade(&qtd);
                informadas = 0;
                existeResultado = 0;
                break;

            case 2:
                if (qtd == 0) {
                    printf("Escolha primeiro a quantidade de matrizes!\n");
                } else {
                    informarMatrizes(matrizes, qtd);
                    informadas = 1;
                    existeResultado = 0;
                }
                break;

            case 3:
            case 4:
            case 5:
            case 6:

                if (!informadas) {
                    printf("Informe as matrizes primeiro!\n");
                    break;
                }

                if (opcao == 3)
                    existeResultado = somar(matrizes, qtd, &resultado);

                else if (opcao == 4)
                    existeResultado = subtrair(matrizes, qtd, &resultado);

                else if (opcao == 5)
                    existeResultado = multiplicar(matrizes, qtd, &resultado);

                else
                    existeResultado = dividir(matrizes, qtd, &resultado);

                break;

            case 7:
                if (existeResultado) {
                    printf("\n===== MATRIZ SOLUCAO =====\n");
                    apresentarMatriz(&resultado);
                } else {
                    printf("Realize uma operacao primeiro!\n");
                }
                break;

            case 0:
                printf("Programa encerrado!\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
