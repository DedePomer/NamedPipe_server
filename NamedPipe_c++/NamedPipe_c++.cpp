
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <math.h>
#define PATH_PIPE L"\\\\.\\pipe\\MyPipe"

DWORD LpwstrToDword(LPWSTR);
BOOL ItsNumber(LPSTR);

int main()
{   
    system("chcp 1251");
    printf("Сервер\n");    
    BOOL Connected;
    HANDLE hPipe;
    DWORD n, kv;
    LPSTR bufferString = (CHAR*)calloc(200, sizeof(CHAR));
    LPSTR mass = (CHAR*)calloc(200, sizeof(CHAR));
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
                if (ItsNumber(bufferString))
                {
                    kv = pow((float)LpwstrToDword(bufferString),2);
                    sprintf(mass, "%d", kv);
                    WriteFile(hPipe, mass, 200, &n, NULL);
                    mass = "";
                }
                else
                {
                    mass = "Ничего";
                    WriteFile(hPipe, mass, 200, &n, NULL);
                    mass = "";
                }                
            }
        }
        CloseHandle(hPipe);
    }
    



}

DWORD LpwstrToDword(LPSTR str)
{
    DWORD dw = 0;
    for (size_t i = 0; i < wcslen(str); i++)
    {
        dw += (str[i] - '0');
        dw *= 10;
    }
    return dw / 10;
}

BOOL ItsNumber(LPSTR str)
{
    int i = 0, c = 0;
    while (1)
    {
        if (str[i]=='\0')
        {
            break;
        }
        switch (str[i])
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            c++;
            break;
        }
        i++;
    }
    if (c == strlen(str))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    
}


