#pragma once
#include <windows.h> 
#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>
#include <mutex>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "Utils.h"

#define BUFSIZE 512

class Servidor
{
private:
	int numThreads = 0;
	bool enviarTodos = false;
public:
	Servidor();
	~Servidor();
	int loop();

	static DWORD WINAPI InstanceThread(LPVOID lpvParam);
	static Mensagem GetAnswerToRequest(Mensagem pchRequest, Mensagem pchReply, LPDWORD pchBytes);
	static VOID MandarATodosJogadores(Mensagem pchReply, vector<Jogador> lista);
};

