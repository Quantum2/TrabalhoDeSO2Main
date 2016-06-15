#pragma once
#include <Windows.h>
#include <iostream>
#include "Utils.h"

using namespace std;

class Registo
{
private:
	const LPCTSTR REG_SW_GROUP_I_WANT = L"SOFTWARE\\ISEC\\SO2\\RR\\";
public:
	Registo();
	~Registo();

	void abreChave(string nome, int passos, int pontos);
	int lerChavePontos(string nomeJogador);
	int lerChavePassos(string nomeJogador);
};

