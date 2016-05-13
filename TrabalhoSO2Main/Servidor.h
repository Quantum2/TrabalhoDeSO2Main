#pragma once
#include <windows.h> 
#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>
#include "Utils.h"

#define BUFSIZE 512

DWORD WINAPI InstanceThread(LPVOID);
VOID GetAnswerToRequest(LPTSTR, LPTSTR, LPDWORD);

class Servidor
{
private:
	Jogo jogo;
public:
	Servidor();
	~Servidor();
	int loop();

	static DWORD WINAPI InstanceThread(LPVOID lpvParam);
	static VOID GetAnswerToRequest(LPTSTR pchRequest, LPTSTR pchReply, LPDWORD pchBytes);
};

