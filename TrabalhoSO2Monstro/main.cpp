#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <time.h>
#include "Utils.h"
#pragma comment(lib, "user32.lib")

#define BUF_SIZE 1024
TCHAR szName[] = TEXT("Local\\MyFileMappingObject");

int nSteps;

void startMonstro(LPCTSTR pBuf) {
	Monstro m;
	MemoryShare *share;
	int id;
	int stepsDados = 0;

	HANDLE ghWriteEvent = CreateEvent(
		NULL,               // default security attributes
		FALSE,               // manual-reset event
		FALSE,              // initial state is nonsignaled
		TEXT("WriteEvent")  // object name
		);

	share = (MemoryShare *)pBuf;
	id = share->monstrosLigados;
	share->monstrosLigados++;
	share->monstros[id].setVisible(true);

	srand(time(NULL));
	share->monstros[id].setX(rand() % share->tamanhoMapa);
	share->monstros[id].setY(rand() % share->tamanhoMapa);

	while (true)
	{
		int r = rand() % 100;
		string dir = "C";

		if (r < 75 && stepsDados >= nSteps)
		{
			r = rand() % 100;
			stepsDados = 0;
			if (r < 25)
			{
				share->monstros[id].setX(share->monstros[id].getPosX() + 1);
				cout << "Monstro com ID " << id << " anda para X:" << share->monstros[id].getPosX() << " Y:" << share->monstros[id].getPosY() << endl;
				dir = "D";
			}
			if (r > 25 && r < 50)
			{
				share->monstros[id].setX(share->monstros[id].getPosX() - 1);
				cout << "Monstro com ID " << id << " anda para X:" << share->monstros[id].getPosX() << " Y:" << share->monstros[id].getPosY() << endl;
				dir = "E";
			}
			if (r > 50 && r < 75)
			{
				share->monstros[id].setY(share->monstros[id].getPosY() - 1);
				cout << "Monstro com ID " << id << " anda para X:" << share->monstros[id].getPosX() << " Y:" << share->monstros[id].getPosY() << endl;
				dir = "C";
			}
			if (r > 75)
			{
				share->monstros[id].setY(share->monstros[id].getPosY() + 1);
				cout << "Monstro com ID " << id << " anda para X:" << share->monstros[id].getPosX() << " Y:" << share->monstros[id].getPosY() << endl;
				dir = "B";
			}
		}
		else
		{
			if (dir == "D")
			{
				share->monstros[id].setX(share->monstros[id].getPosX() + 1);
				cout << "Monstro com ID " << id << " anda para X:" << share->monstros[id].getPosX() << " Y:" << share->monstros[id].getPosY() << endl;
			}
			if (dir == "B")
			{
				share->monstros[id].setY(share->monstros[id].getPosY() + 1);
				cout << "Monstro com ID " << id << " anda para X:" << share->monstros[id].getPosX() << " Y:" << share->monstros[id].getPosY() << endl;
			}
			if (dir == "E")
			{
				share->monstros[id].setX(share->monstros[id].getPosX() - 1);
				cout << "Monstro com ID " << id << " anda para X:" << share->monstros[id].getPosX() << " Y:" << share->monstros[id].getPosY() << endl;
			}
			if (dir == "C")
			{
				share->monstros[id].setY(share->monstros[id].getPosY() - 1);
				cout << "Monstro com ID " << id << " anda para X:" << share->monstros[id].getPosX() << " Y:" << share->monstros[id].getPosY() << endl;
			}
			stepsDados++;
		}

		if (share->monstros[id].getPosX() >= share->tamanhoMapa - 1)
		{
			share->monstros[id].setX(share->monstros[id].getPosX() - 1);
		}
		if (share->monstros[id].getPosX() <= 0)
		{
			share->monstros[id].setX(share->monstros[id].getPosX() + 1);
		}
		if (share->monstros[id].getPosY() <= 0)
		{
			share->monstros[id].setY(share->monstros[id].getPosY() + 1);
		}
		if (share->monstros[id].getPosY() >= share->tamanhoMapa - 1)
		{
			share->monstros[id].setY(share->monstros[id].getPosY() - 1);
		}

		SetEvent(ghWriteEvent);
		_sleep(1500);
	}
}

int main(int argc, char* argv[]) {
	HANDLE hMapFile;
	LPCTSTR pBuf;

	if (argc == 1)
	{
		nSteps = atoi(argv[0]);
	}
	else
	{
		nSteps = 3;
	}

	hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,   // read/write access
		FALSE,                 // do not inherit the name
		szName);               // name of mapping object

	if (hMapFile == NULL)
	{
		_tprintf(TEXT("Could not open file mapping object (%d).\n"),
			GetLastError());
		return 1;
	}

	pBuf = (LPTSTR)MapViewOfFile(hMapFile, // handle to map object
		FILE_MAP_ALL_ACCESS,  // read/write permission
		0,
		0,
		BUF_SIZE);

	if (pBuf == NULL)
	{
		_tprintf(TEXT("Could not map view of file (%d).\n"),
			GetLastError());

		CloseHandle(hMapFile);
		return 1;
	}

	startMonstro(pBuf);

	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);

	return 0;
}