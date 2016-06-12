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


Mapa Jogo::getCMap() { //converte string C++ pra C 
	Mapa m;
	char temp[TAM_LABIRINTO][TAM_LABIRINTO * 3];

	for (size_t i = 0; i < TAM_LABIRINTO; i++)
	{
		string tempS;
		for (size_t j = 0; j < TAM_LABIRINTO; j++)
		{
			tempS.append(lab->mapa[i][j] + "\n");
		}
		strcpy_s(temp[i], tempS.c_str());
	}

	for (size_t i = 0; i < TAM_LABIRINTO; i++)
	{
		strcpy_s(m.mapaEnv[i], temp[i]);
	}

	return m;
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


