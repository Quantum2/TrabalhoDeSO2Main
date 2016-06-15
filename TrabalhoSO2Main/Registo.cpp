#include "Registo.h"

Registo::Registo()
{
}

Registo::~Registo()
{
}

void Registo::abreChave(string nome, int passos, int pontos)
{
	HKEY hKey;
	LPWSTR nChave = TEXT("StuffStuffStuffStuffStuffStuffStuffStuffStuff");
	MultiByteToWideChar(CP_UTF8, 0, nome.c_str(), -1, nChave, 0);

	RegCreateKeyEx(HKEY_CURRENT_USER, REG_SW_GROUP_I_WANT, NULL, nChave, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);	RegSetValueEx(hKey, L"Pontos", NULL, REG_DWORD, (LPBYTE)pontos, sizeof(pontos));
	RegSetValueEx(hKey, L"Passos", NULL, REG_DWORD, (LPBYTE)passos, sizeof(passos));

	RegCloseKey(hKey);
}

int Registo::lerChavePassos(string nomeJogador)
{
	HKEY hKey;
	LPWSTR nChave = TEXT("StuffStuffStuffStuffStuffStuffStuffStuffStuff");
	int temp;
	DWORD bufSize = 8192;

	MultiByteToWideChar(CP_UTF8, 0, nomeJogador.c_str(), -1, nChave, 0);

	RegCreateKeyEx(HKEY_CURRENT_USER, REG_SW_GROUP_I_WANT, NULL, nChave, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (RegQueryValueEx(hKey, L"Passos", NULL, NULL, (LPBYTE)&temp, &bufSize) == ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return temp;
	}
	else
	{
		RegCloseKey(hKey);
		return -1;
	}
}

int Registo::lerChavePontos(string nomeJogador)
{
	HKEY hKey;
	LPWSTR nChave = TEXT("StuffStuffStuffStuffStuffStuffStuffStuffStuff");
	int temp;
	DWORD bufSize = 8192;

	MultiByteToWideChar(CP_UTF8, 0, nomeJogador.c_str(), -1, nChave, 0);

	RegCreateKeyEx(HKEY_CURRENT_USER, REG_SW_GROUP_I_WANT, NULL, nChave, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (RegQueryValueEx(hKey, L"Pontos", NULL, NULL, (LPBYTE)temp, &bufSize) == ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return temp;
	}
	else
	{
		RegCloseKey(hKey);
		return -1;
	}
}