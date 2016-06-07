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
				mapa[0][0] = "*";
			}
		}
	}
}


Jogo::Jogo() 
{
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

Jogador::Jogador(string nome, int p)
{
	name = nome;
	pid = p;
}

Jogador::~Jogador()
{
}

int Jogador::getPid()
{
	return pid;
}