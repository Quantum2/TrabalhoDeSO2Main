#pragma once
#include <Windows.h>
#include <iostream>

using namespace std;

class Registo
{
private:
	const LPCTSTR REG_SW_GROUP_I_WANT = L"SOFTWARE\\ISEC\\SO2\\RR";
	const string REG_KEY_I_WANT = "Main Key";
public:
	Registo();
	~Registo();

	void abreChave(string nome, int passos, int pontos);
	int lerChavePontos(string nomeJogador);
	int lerChavePassos(string nomeJogador);
};

