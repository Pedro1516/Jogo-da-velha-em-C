#include <stdio.h>
#include <stdlib.h>

int pontos_x = 0;
int pontos_o = 0;
int cor_x = 31;
int cor_o = 32;

void imprime_jogo(int tab[][3]);
void limpa_tabuleiro(int tab[][3]);
void update(int tab[][3], int jogador);
void marca_tabuleiro(int tab[][3], int line, int col, int player);
int teste_vitoria(int tab[][3], int ultima_jog[2]);
int loop_jogo(int tab[][3]);

int main(int argc, char *argv[])
{
	int tabuleiro[3][3];
	int escolha;
	int vencedor;

	while (1)
	{
		vencedor = loop_jogo(tabuleiro);
		if (vencedor == 0)
		{
			pontos_o++;
		}
		else
		{
			pontos_x++;
		}

		update(tabuleiro, 1);

		printf("\n\nDeseja jogar novamente?\n [0]Sim [1]Nao\n");
		scanf("%d", &escolha);

		if (escolha)
		{
			break;
		}
	}

	return 0;
}

void imprime_jogo(int tab[3][3])
{
	char caractere;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (j > 0)
			{
				printf("|");
			}
			if (tab[i][j] == 0)
			{
				caractere = 'O';
			}
			else if (tab[i][j] == 1)
			{
				caractere = 'X';
			}
			else
			{
				caractere = ' ';
			}
			printf(" \033[%dm %c \033[00m ", (caractere == 'O') ? cor_o : cor_x, caractere);
		}
		printf("\n");
		if (i < 2)
		{
			for (int j = 0; j < 17; j++)
			{
				printf("-");
			}
		}
		printf("\n");
	}
}

void marca_tabuleiro(int tab[3][3], int line, int col, int player)
{
	if (tab[line - 1][col - 1] == -1)
	{
		tab[line - 1][col - 1] = player;
	}
}

int teste_vit_coluna(int tab[3][3], int ultima_jog[2])
{
	int aux = 0;
	for (int i = 0; i < 2; i++)
	{
		if (tab[i][ultima_jog[1]] == tab[i + 1][ultima_jog[1]])
		{
			aux++;
		}
	}
	if (aux == 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int teste_vit_linha(int tab[3][3], int ultima_jog[2])
{
	int aux = 0;
	for (int i = 0; i < 2; i++)
	{
		if (tab[ultima_jog[0]][i] == tab[ultima_jog[0]][i + 1])
		{
			aux++;
		}
	}
	if (aux == 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int teste_vit_diag(int tab[3][3], int ultima_jog[2])
{
	int aux = 0;
	//testa diagonal principal
	for (int i = 0; i < 2; i++)
	{
		if (tab[i][i] == tab[i + 1][i + 1] && tab[i + 1][i + 1] != -1)
		{
			aux++;
		}
	}

	if (aux == 2)
	{
		return 1;
	}

	//testa diagonal secundária
	//tab[0][2] == -1 garante q quando a diagonal está vazia, ela não de um falso positivo
	if (tab[0][2] == -1 || tab[0][2] != tab[1][1] || tab[1][1] != tab[2][0])
	{
		return 0;
	}
	else
	{
		return 1;
	}

	return 0;
}

int teste_vitoria(int tab[3][3], int ultima_jog[2])
{
	if (ultima_jog[0] == 0 || ultima_jog[0] == 2)
	{
		if (teste_vit_coluna(tab, ultima_jog))
		{
			return 1;
		}
		else if (teste_vit_linha(tab, ultima_jog))
		{
			return 1;
		}
		//testa as casas laterais da primeira linha
		if (ultima_jog[1] != 1)
		{
			if (teste_vit_diag(tab, ultima_jog))
			{
				return 1;
			}
		}
	}
	else
	{
		if (teste_vit_coluna(tab, ultima_jog))
		{
			return 1;
		}
		else if (teste_vit_linha(tab, ultima_jog))
		{
			return 1;
		}
		//testa a casa central do tabuleiro
		if (ultima_jog[1] == 1)
		{
			if (teste_vit_diag(tab, ultima_jog))
			{
				return 1;
			}
		}
	}

	return 0;
}

void limpa_tabuleiro(int tab[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tab[i][j] = -1;
		}
	}
}

int loop_jogo(int tab[][3])
{
	int ultima_jog[2];
	int col, line;

	limpa_tabuleiro(tab);

	//marca quem vai jogar X ou O
	int vez_jogador = 1;
	update(tab, vez_jogador);

	while (1)
	{
		printf("\nDigite linha e coluna: ");
		//loop para pegar posições válidas
		while (1)
		{
			scanf("%d %d", &line, &col);
			if ((line <= 3 && line >= 1) && (col <= 3 && col >= 1) && tab[line - 1][col - 1] == -1)
			{
				break;
			}
			else
			{
				update(tab, vez_jogador);
				printf("\nDigite uma posição valida: ");
			}
		}

		//marca X ou O no tabuleiro
		marca_tabuleiro(tab, line, col, vez_jogador);

		//marca a ultima jogada
		ultima_jog[0] = line - 1;
		ultima_jog[1] = col - 1;

		//Verifica se alguém ganhou
		if (teste_vitoria(tab, ultima_jog))
		{
			printf("\nJogador %c Ganhou!\n", vez_jogador ? 'X' : 'O');
			if (vez_jogador == 0)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}

		// troca valor de vez_jogador de 0 pra 1 e vice versa
		vez_jogador = (vez_jogador == 1) ? 0 : 1;

		update(tab, vez_jogador);
	}
}

void update(int tab[3][3], int jogador)
{
	system("clear");

	printf("Pontuação \033[%dm X: \033[0m %d \033[%dm O: \033[0m %d \n\n", cor_x, pontos_x, cor_o, pontos_o);
	printf("\nVez do jogador %c\n\n", jogador ? 'X' : 'O');
	imprime_jogo(tab);
}