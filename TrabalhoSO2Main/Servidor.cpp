#include "Servidor.h"

static Jogo jogo;
static mutex mtx;
static bool enviarTodos = false;
static Mensagem globalM;

Servidor::Servidor()
{
}

Servidor::~Servidor()
{
}

int Servidor::loop() {
	BOOL   fConnected = FALSE;
	DWORD  dwThreadId = 0;
	HANDLE hPipe = INVALID_HANDLE_VALUE, hPipeGeral = INVALID_HANDLE_VALUE, hThread = NULL, hThread2 = NULL;
	LPTSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe");

	// The main loop creates an instance of the named pipe and 
	// then waits for a client to connect to it. When the client 
	// connects, a thread is created to handle communications 
	// with that client, and this loop is free to wait for the
	// next client connect request. It is an infinite loop.
	for (;;)
	{
		_tprintf(TEXT("\nPipe Server: Main thread awaiting client connection on %s\n"), lpszPipename);
		hPipe = CreateNamedPipe(
			lpszPipename,             // pipe name 
			PIPE_ACCESS_DUPLEX,       // read/write access 
			PIPE_TYPE_MESSAGE |       // message type pipe 
			PIPE_READMODE_MESSAGE |   // message-read mode 
			PIPE_WAIT,                // blocking mode 
			PIPE_UNLIMITED_INSTANCES, // max. instances  
			BUFSIZE,                  // output buffer size 
			BUFSIZE,                  // input buffer size 
			0,                        // client time-out 
			NULL);                    // default security attribute 

		if (hPipe == INVALID_HANDLE_VALUE)
		{
			_tprintf(TEXT("CreateNamedPipe failed, GLE=%d.\n"), GetLastError());
			return -1;
		}

		// Wait for the client to connect; if it succeeds, 
		// the function returns a nonzero value. If the function
		// returns zero, GetLastError returns ERROR_PIPE_CONNECTED. 
		fConnected = ConnectNamedPipe(hPipe, NULL) ?
			TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

		if (fConnected)
		{
			printf("Client connected, creating a processing thread.\n");

			// Create a thread for this client. 
			hThread = CreateThread(
				NULL,              // no security attribute 
				0,                 // default stack size 
				InstanceThread,    // thread proc
				(LPVOID)hPipe,    // thread parameter 
				0,                 // not suspended 
				&dwThreadId);      // returns thread ID 

			if (hThread == NULL)
			{
				_tprintf(TEXT("CreateThread failed, GLE=%d.\n"), GetLastError());
				return -1;
			}
			else CloseHandle(hThread);
		}
		else
			// The client could not connect, so close the pipe. 
			CloseHandle(hPipe);
	}

	return 0;
}

DWORD WINAPI Servidor::InstanceThread(LPVOID lpvParam)
// This routine is a thread processing function to read from and reply to a client
// via the open pipe connection passed from the main loop. Note this allows
// the main loop to continue executing, potentially creating more threads of
// of this procedure to run concurrently, depending on the number of incoming
// client connections.
{
	HANDLE hHeap = GetProcessHeap();
	Mensagem pchRequest, pchReply, pchGlobal;
	strcpy(pchReply.msg, "empty");
	strcpy(pchGlobal.msg, "empty");

	DWORD cbBytesRead = 0, cbReplyBytes = 0, cbWritten = 0;
	BOOL fSuccess = FALSE;
	HANDLE hPipe = NULL;

	// Do some extra error checking since the app will keep running even if this
	// thread fails.
	if (lpvParam == NULL)
	{
		printf("\nERROR - Pipe Server Failure:\n");
		printf("   InstanceThread got an unexpected NULL value in lpvParam.\n");
		printf("   InstanceThread exitting.\n");
		//if (pchReply != NULL) HeapFree(hHeap, 0, pchReply);
		return (DWORD)-1;
	}

	// Print verbose messages. In production code, this should be for debugging only.
	printf("InstanceThread created, receiving and processing messages.\n");

	// The thread's parameter is a handle to a pipe object instance. 
	hPipe = (HANDLE)lpvParam;

	// Loop until done reading
	while (1)
	{
		// Read client requests from the pipe. This simplistic code only allows messages
		// up to BUFSIZE characters in length.
		fSuccess = ReadFile(
			hPipe,        // handle to pipe 
			&pchRequest,    // buffer to receive data 
			sizeof(Mensagem), // size of buffer 
			&cbBytesRead, // number of bytes read 
			NULL);        // not overlapped I/O 

		if (!fSuccess || cbBytesRead == 0)
		{
			if (GetLastError() == ERROR_BROKEN_PIPE)
			{
				_tprintf(TEXT("InstanceThread: client disconnected.\n"), GetLastError());
			}
			else
			{
				_tprintf(TEXT("InstanceThread ReadFile failed, GLE=%d.\n"), GetLastError());
			}
			break;
		}

		// Process the incoming message.
		pchReply = GetAnswerToRequest(pchRequest, pchReply, &cbReplyBytes);

		// Write the reply to the pipe. 
		fSuccess = WriteFile(
			hPipe,        // handle to pipe 
			&pchReply,     // buffer to write from 
			cbReplyBytes, // number of bytes to write 
			&cbWritten,   // number of bytes written 
			NULL);        // not overlapped I/O 

		if (!fSuccess || cbReplyBytes != cbWritten)
		{
			_tprintf(TEXT("InstanceThread WriteFile failed, GLE=%d.\n"), GetLastError());
			break;
		}
	}

	// Flush the pipe to allow the client to read the pipe's contents 
	// before disconnecting. Then disconnect the pipe, and close the 
	// handle to this pipe instance. 

	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);

	//HeapFree(hHeap, 0, pchRequest);
	//HeapFree(hHeap, 0, pchReply);

	printf("InstanceThread exitting.\n");
	return 1;
}

Mensagem Servidor::GetAnswerToRequest(Mensagem pchRequest, Mensagem pchReply, LPDWORD pchBytes)
// This routine is a simple function to print the client request to the console
// and populate the reply buffer with a default data string. This is where you
// would put the actual client request processing code that runs in the context
// of an instance thread. Keep in mind the main thread will continue to wait for
// and receive other client connections while the instance thread is working.
{
	printf("Client Request String:\"%s\"\n", pchRequest.msg);
	string entrada(pchRequest.msg);
	string temp = "Comando não reconhecido";

	istringstream iss(entrada);
	vector<string> tokens{ istream_iterator<string>{iss},               //Separador super elegante pls http://stackoverflow.com/questions/236129/split-a-string-in-c
		istream_iterator<string>{} };

	if (tokens.size() == 0)
		tokens.push_back("empty string");

	if (tokens[0] == "login") {
		if (jogo.getEstado() == jogo.A_PROCURAR_CLIENTES) {
			temp = "A fazer login...";
			Jogador* temp_jogar = new Jogador(tokens[1], pchRequest.pid);
			jogo.jogadores.push_back(*temp_jogar);
		}
		else {
			temp = "O servidor já tem um jogo a decorrer ou a iniciar";
		}
	}
	if (tokens[0] == "jogar") {
		bool encontrado = false;

		for (int i = 0; i < jogo.jogadores.size(); i++) {
			if (jogo.jogadores[i].getPid() == pchRequest.pid)
				encontrado = true;
		}

		if (encontrado) {
			temp = "A iniciar jogo...";
			strcpy_s(globalM.msg, "EM FASE DE JOGO!!!");
			for (int i = 0; i < jogo.jogadores.size(); i++) {
				globalM.pidsEnviar[i] = jogo.jogadores[i].getPid();
			}
			enviarTodos = true;
			jogo.setEstado(jogo.A_JOGAR);
		}
		else {
			temp = "Jogador não logado";
		}
	}
	if (tokens[0] == "terminar") {
		temp = "A terminar jogo...";
		strcpy_s(globalM.msg, "EM FASE DE SAIR!!!");
		enviarTodos = true;
	}
	if (tokens[0] == "actualizar") {
		temp = "A actualizar mapa";
		pchReply.mapa = jogo.getCMap();
	}

	strcpy_s(pchReply.msg, temp.c_str());
	*pchBytes = sizeof(pchReply);

	return pchReply;
}
