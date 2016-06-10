#include "Utils.h"

Labirinto::Labirinto()
{
	gerarLab();
}

void Labirinto::gerarLab()
{

	for (size_t i = 0; i < TAM_LABIRINTO; i++)
	{
		for (size_t j = 0; j < TAM_LABIRINTO; j++)
		{
			if (i == 0 && j == 0)
			{
				mapa[i][j] = "*";
			}
			if (i == TAM_LABIRINTO - 1 && j == 0)
			{
				mapa[i][j] = "*";
			}
			if (i == 0 && j == TAM_LABIRINTO - 1)
			{
				mapa[i][j] = "*";
			}
			if (i == TAM_LABIRINTO - 1 && j == TAM_LABIRINTO - 1)
			{
				mapa[i][j] = "*";
			}
			gerado = rand() % 100;
			if (gerado <= 5)
			{
				gerado = rand() % 100;
				if (gerado <= 50) mapa[i][j] = "P";
				else if (gerado>50 && gerado <= 80) mapa[i][j] = "V";
				else if (gerado>81 && gerado <= 90) mapa[i][j] = "O";
				else if (gerado>91 && gerado <= 99) mapa[i][j] = "C";
				else if (gerado = 100) mapa[i][j] = "M";
			}

			mapa[i][j] = "_";
		}
	}
}


char** Jogo::getCMap() { //converte string C++ pra C 
	char **temp;
	temp = (char**)malloc(sizeof(char *) * TAM_LABIRINTO);
	for (size_t i = 0; i < TAM_LABIRINTO; i++)
	{
		temp[i] = (char *)malloc(sizeof(char) * TAM_LABIRINTO);
	}

	for (size_t i = 0; i < TAM_LABIRINTO; i++)
	{
		for (size_t j = 0; j < TAM_LABIRINTO; j++)
		{
			strcpy(&temp[i][j], lab->mapa[i][j].c_str());
		}
	}

	return temp;
}


Jogo::Jogo()
{
	lab = new Labirinto();
}

Jogo::~Jogo()
{
}

void Jogo::setEstado(int e)
{
	estado = e;
}

int Jogo::getEstado()
{
	return estado;
}

Jogador::Jogador(string nome, int p, int vida)
{
	name = nome;
	pid = p;
	hp = vida;
	//
}



Jogador::~Jogador()
{
}

int Jogador::getPid()
{
	return pid;
}


