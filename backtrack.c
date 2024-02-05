#include <stdlib.h>
#include <stdio.h>

// Calcula o coeficiente binomial C(N, k)
unsigned long int binomial(unsigned long int N, unsigned long int k) {
    if (k == 0 || k == N) {
        return 1;
    } else {
        return binomial(N - 1, k - 1) + binomial(N - 1, k);
    }
}

// Calcula o número de soluções possíveis B(N) para o problema das N Rainhas
unsigned long int num_solucoes_nrainhas(unsigned long int N) {
    if (N == 1) {
        return 1;
    }

    unsigned long int num_solucoes = 0;
    for (unsigned long int k = 0; k < N; k++) {
        num_solucoes += binomial(N, k) * num_solucoes_nrainhas(k);
    }

    return num_solucoes;
}


void iniciliza_tabuleiro(int **v, int n)
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			v[i][j] = 0;
		}
	}

	return;
}

void imprime_tabuleiro(int **v, int n)
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		printf("\n");
		for (j = 0; j < n; j++)
		{
			if (v[i][j] == 1)
			{
				printf("R ");
			}
			else
			{
				printf("- ");
			}
		}
	}
	printf("\n");
	return;
}

int possivel(int **v, int n, int l, int c)
{
	int i, j;

	/*Verifica se tem uma rainha na mesma coluna*/
	for (i = 0; i < n; i++)
	{

		if (v[i][c] == 1)
		{
			return 0;
		}
	}

	for (i = l, j = c; i >= 0 && j >= 0; i--, j--)
	{

		if (v[i][j] == 1)
		{
			return 0;
		}
	}

	for (i = l, j = c; i >= 0 && j < n; i--, j++)
	{

		if (v[i][j] == 1)
		{
			return 0;
		}
	}

	return 1;
}

int resolve(int **tab, int n, int l, int c)
{
	int i;
	int k = 0;

	if (l == n)
	{
		printf("\n");
		printf("SOLUCAO ENCONTRADA \n");
		imprime_tabuleiro(tab, n);
		return 1;

	}

	for (i = 0; (c + i) < n; i++)
	{

		if (possivel(tab, n, l, (c + i)) == 1)
		{

			tab[l][c + i] = 1;
			k += resolve(tab, n, l + 1, 0);
			tab[l][c + i] = 0;
		}
	}

	return k;
}

int main()
{
	int n = 0,j = 0;
	long int s = 0;
	int **v;
	char r;


	printf("Informe o Tamanho do Tabuleiro N x N: ");
    if (scanf("%d", &n) != 1) {
        printf("Entrada invalida. Por favor, digite um numero inteiro.\n");
        return 1;
    } else if (n <= 0) {
        printf("Entrada invalida. Por favor, digite um numero maior que zero\n");
        return 1;
    } else if (n > 10) {
        s = num_solucoes_nrainhas(n);
        printf("O numero de solucoes possiveis para o problema das %d Rainhas e: %lu\n", n, s);

        printf("Deseja continuar: Sim(S) - Nao(N): ");
        while (getchar() != '\n'); // Limpar o buffer do teclado

        scanf("%c", &r);
        if (r == 'N' || r == 'n') {
            return 0;
        }
    }



	// Aloca um vetor de N ponteiros para linhas
	v = malloc(n * sizeof(int *));
	if (v == NULL){
		printf("Falha ao Alocar Memoria\n");
		return 1;
	}

	// Aloca um vetor com todos os elementos da matriz
	v[0] = malloc(n * n * sizeof(int));
	if (v[0] == NULL){
		printf("Falha ao Alocar Memoria\n");
		return 1;
	}

	// Ajusta os demais ponteiros de linhas (i > 0)
	for (int i = 1; i < n; i++)
		v[i] = v[0] + i * n;

	iniciliza_tabuleiro(v, n);
	j = resolve(v, n, 0, 0);

	printf("%d Solucoes Possiveis\n",j);

	// Libera a memória da matriz
	free (v[0]) ;
	free (v) ;


	return 0;
}