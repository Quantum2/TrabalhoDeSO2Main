#pragma once
#include <windows.h> 
#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>
#include <signal.h>
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
};

