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

Mapa Jogo::getCMap() {       
	Mapa m;
	char temp[TAM_LABIRINTO][TAM_LABIRINTO * 3];

	for (size_t i = 0; i < TAM_LABIRINTO; i++)
	{
		for (size_t j = 0; j < TAM_LABIRINTO; j++)
		{
			if (lab->mapa[i][j] == "J")
			{
				lab->mapa[i][j] = "_";
			}
			if (lab->mapa[i][j] == "M")
			{
				lab->mapa[i][j] = "_";
			}
		}
	}

	for (size_t i = 0; i < jogadores.size(); i++)
	{
		Jogador temp = jogadores[i];
		lab->mapa[temp.getX()][temp.getY()] = "J";
	}

	for (size_t i = 0; i < ms.monstrosLigados; i++)
	{
		lab->mapa[ms.monstros[i].getPosX()][ms.monstros[i].getPosY()] = "M";
	}

	for (size_t i = 0; i < TAM_LABIRINTO; i++)
	{
		string tempS;
		for (size_t j = 0; j < TAM_LABIRINTO; j++)
		{
			tempS.append(lab->mapa[i][j] + " ");
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

void Jogo::adicionarJogador(Jogador j)
{
	srand(time(NULL));
	int x = rand() % TAM_LABIRINTO;
	int y = rand() % TAM_LABIRINTO;

	j.setPos(x, y);
	jogadores.push_back(j);
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
	
}

Jogador::~Jogador()
{
}

Jogador::Jogador()
{
}

int Jogador::getPid()
{
	return pid;
}

void Jogador::setPos(int x, int y)
{
	posX = x;
	posY = y;
}

int Jogador::getX()
{
	return posX;
}

int Jogador::getY()
{
	return posY;
}

bool Jogador::getAtacaAuto() { return atacaAuto; }
void Jogador::setAtacaAuto(bool ataca) { atacaAuto = ataca; }

void Jogador::toggleAtacaAuto()
{
	if (getAtacaAuto()) setAtacaAuto(false);
	else setAtacaAuto(true);
}

bool Jogador::getPedra() { return pedra; }
bool Jogador::getMachado() { return machado; }

void Jogador::setPedra(bool p) { pedra = p; }
void Jogador::setMachado(bool m) { machado = m; }

void Jogador::togglePedra()
{
	if (getPedra() == false) setPedra(true);
	else setPedra(false);

}

void Jogador::toggleMachado()
{
	if (getMachado() == false) setMachado(true);
	else setMachado(false);
}

int Jogador::getHP(){return hp;}

void Jogador::setHP(int dano){
	hp=hp-dano; 
	//if (hp<=0) morre();
}

int Jogador::atacar(Jogador j)
{
	//FALTA verificar quem ou o que está na mesma posiçao q ele  !!!
	//
	if (getPedra()==false && getMachado()==false)
		{
			j.setHP(1);
		}	
		else if ((getPedra() == true && getMachado() == false))
		{
			j.setHP(2);
		}
		else if( (getPedra() == true && getMachado() == true) || (getPedra() == false && getMachado() == true))
		{
			//machado prevalece independentemente de pedra on ou off - tira 5 hp 
			j.setHP(5);
		}

		return 0;
} 

Jogador Jogo::verificaVizinhos(Jogador j)
{
	int x=j.getX();
	int y=j.getY();
	int x1,y1;

	for (size_t i = 0; i < jogadores.size(); i++)
	{
		Jogador temp = jogadores[i];
		x1=temp.getX();
		y1=temp.getY();
	
		if ((x1==x+1) || (x1 == x-1) || (y1 == y + 1) || (y1 == y - 1)) return temp;
	}
	return Jogador();
}


Monstro::Monstro()
{
	hp = 100;
	visible = false;
}

int Monstro::getPosX()
{
	return posX;
}

int Monstro::getPosY()
{
	return posY;
}

int Monstro::getHP()
{
	return hp;
}

bool Monstro::getVisible()
{
	return visible;
}

void Monstro::setVisible(bool v)
{
	visible = v;
}

void Monstro::setHP(int h)
{
	hp = h;
}

void Monstro::setX(int x) {
	posX = x;
}

void Monstro::setY(int y) {
	posY = y;
}
