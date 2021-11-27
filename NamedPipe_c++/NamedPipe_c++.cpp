

#include <windows.h>
#include <stdio.h>
#define PATH_PIPE L"\\\\.\\pipe\\MyPipe"

int main()
{
    HANDLE hPipe = CreateNamedPipe(PATH_PIPE, PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES, 200, 200, INFINITE, NULL);
    system("chcp 1251");
    printf("Сервер\n");    
    BOOL Connected;
    while (1)
    {      
        
        Connected = ConnectNamedPipe(hPipe, NULL);
        if (Connected)
        {
            printf("\nПодключение установленно\n");
            LPWSTR bufferString = (CHAR*)calloc(200, sizeof(CHAR));
            DWORD n;
            ReadFile(hPipe, bufferString, 200, &n, NULL);
            printf(bufferString);

        }
        
    }
    CloseHandle(hPipe);



}


