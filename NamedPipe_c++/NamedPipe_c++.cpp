

#include <windows.h>
#include <stdio.h>
#define PATH_PIPE L"\\\\.\\pipe\\MyPipe"

int main()
{   
    system("chcp 1251");
    printf("Сервер\n");    
    BOOL Connected;
    HANDLE hPipe;
    DWORD n;
    LPWSTR bufferString = (CHAR*)calloc(200, sizeof(CHAR));
    LPWSTR mass = (CHAR*)calloc(200, sizeof(CHAR));
    while (1)
    {      
        hPipe = CreateNamedPipe(PATH_PIPE, PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            PIPE_UNLIMITED_INSTANCES, 200, 200, INFINITE, NULL);
        Connected = ConnectNamedPipe(hPipe, NULL);
        if (Connected)
        {
            printf("\nПодключение установленно\n");
            if (ReadFile(hPipe, bufferString, 200, &n, NULL))
            {
                printf("\nКлиент пишет: %s", bufferString);
                printf("\nВведите сообщение клиенту: ");
                gets(mass);
                WriteFile(hPipe, mass, 200, &n, NULL);
            }
          

        }
        CloseHandle(hPipe);
    }
    



}


