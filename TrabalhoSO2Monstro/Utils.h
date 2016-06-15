#pragma once
#include <vector>
#include "Monstro.h"

using namespace std;

struct MemoryShare {
	Monstro monstros[128];
	int monstrosLigados;
	int tamanhoMapa;
};