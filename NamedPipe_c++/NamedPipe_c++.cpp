
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define PATH_PIPE L"\\\\.\\pipe\\MyPipe"

DWORD LpwstrToDword(LPWSTR);
BOOL ItsNumber(LPSTR);
LPSTR DwordToLpstr(DWORD);
LPSTR ReverseStr(LPSTR);

int main()
{   
    system("chcp 1251");
    printf("Сервер\n"); 
    time_t rawtime;
    struct tm* timeinfo;        
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
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            printf("Подключение установленно %s\n", asctime(timeinfo));
            if (ReadFile(hPipe, bufferString, 200, &n, NULL))
            {
                if (ItsNumber(bufferString))
                {
                    kv = pow((float)LpwstrToDword(bufferString),2);
                    if (kv == 0 )
                    {
                        mass = "0";
                    }
                    else
                    {
                        mass = DwordToLpstr(kv);
                    }    
                    WriteFile(hPipe, mass, 200, &n, NULL);
                    mass = "0";
                }
                else
                {
                    mass = "Ничего";
                    WriteFile(hPipe, mass, 200, &n, NULL);
                    mass = "0";
                }                
            }
            else
            {
                printf("Пользователь отключился\n");
            }
        }
        else
        {
            printf("Канал исчез\n");
        }
        CloseHandle(hPipe);
    }
    



}

DWORD LpwstrToDword(LPSTR str)
{
    DWORD dw = 0;
    if (str[0] != '-')
    {
        for (size_t i = 0; i < strlen(str); i++)
        {
            dw += (str[i] - '0');
            dw *= 10;
        }
        return dw / 10;
    }
    else
    {
        for (size_t i = 1; i < strlen(str); i++)
        {
            dw += (str[i] - '0');
            dw *= 10;
        }
        return dw / 10;
    }   
}

LPSTR DwordToLpstr(DWORD num)
{
    LPSTR str = calloc(200, sizeof(CHAR));
    char c = ' ';
    DWORD n = num, m = 0;
    int y = 0;
    for (int i = 10; num % (i/10) != num; i *= 10)
    {
        m = n % i;
        m = m / (i / 10);
        c = 48 + m;
        str[y] = c;
        y++;
    }
    return ReverseStr(str);
}

LPSTR ReverseStr (LPSTR str)
{
    LPSTR strBuff = calloc(200, sizeof(CHAR));
    int y = 0;
    for (int i = strlen(str)-1; i >= 0; i--)
    {
        strBuff[y] = str[i];
        y++;
    }
    return strBuff;
}

BOOL ItsNumber(LPSTR str)
{
    int i = 0, c = 0,m = 1;
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
        case '-':
            if (i==0)
            {
                m = 1;
            }
            else
            {
                m = -1;
            }
            c++;
            break;
        }
        i++;
    }
    if (c == strlen(str) && m == 1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    
}


