#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <time.h>

#define BUFSIZE 2048
#define TAM_LABIRINTO 50

using namespace std;

struct Mapa {
	char mapaEnv[TAM_LABIRINTO][TAM_LABIRINTO * 3];
};

struct Mensagem { //cliente para servidor
	int pid;
	char msg[BUFSIZE];
	int pidsEnviar[128];
	Mapa mapa;
};

class Jogador
{
private:
	string name;
	int pid, hp = 100, posX, posY;
	int pedras[15];
public:
	Jogador(string nome, int p, int vida);
	~Jogador();
	Jogador();
	int getPid();
	void setPos(int x, int y);
	int getX();
	int getY();
};

class Labirinto
{
private:
	int gerado; // controlo para criaçao de itens - 5%
public:
	Labirinto();
	void gerarLab();
	string mapa[TAM_LABIRINTO][TAM_LABIRINTO];
};

class Jogo {
private:
	int estado = 1;
	Labirinto* lab;
public:
	Jogo();
	~Jogo();

	string lastCommand;
	vector<Jogador> jogadores;
	void adicionarJogador(Jogador j);

	const int A_PROCURAR_CLIENTES = 1;
	const int A_INICIAR_JOGO = 2;
	const int A_JOGAR = 3;

	void setEstado(int e);
	int getEstado();

	Mapa getCMap();
};