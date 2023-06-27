#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void enviarComando(HANDLE hSerial, const char* comando)
{
    DWORD bytesWritten;
    if (!WriteFile(hSerial, comando, strlen(comando), &bytesWritten, NULL))
    {
        printf("Erro ao escrever na porta serial.\n");
        CloseHandle(hSerial);
        exit(1);
    }
    printf("Comando enviado.\n");
}

void lerEstadoLED(HANDLE hSerial, char* buffer, DWORD* bytesRead)
{
    if (!ReadFile(hSerial, buffer, sizeof(buffer), bytesRead, NULL))
    {
        printf("Erro ao ler o estado do LED.\n");
        CloseHandle(hSerial);
        exit(1);
    }
    else if (buffer[0] == '9')
    {
        printf("Leitura do LDR: %s\n", buffer + 1);
    }
}

void exibirEstadoLED(HANDLE hSerial, const char* buffer, DWORD bytesRead)
{
    if (bytesRead > 0)
    {
        if (buffer[0] == '1')
        {
            printf("O LED está ligado.\n");
        }
        else if (buffer[0] == '0')
        {
            printf("O LED está desligado.\n");
        }
    }
    while (bytesRead > 0 && buffer[bytesRead - 1] != '\n')
    {
        if (!ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL))
        {
            printf("Erro ao ler o estado do LED.\n");
            CloseHandle(hSerial);
            exit(1);
        }
    }
}

typedef enum {
    VERMELHO = '1',
    VERDE = '2',
    AZUL = '3',
    NENHUM = '4',
    AMARELO = '5',
    ROSA = '6',
    CIANO = '7'
} CorRGB;

void exibirCorRGB(CorRGB cor)
{
    switch (cor)
    {
        case VERMELHO:
            printf("Cor: Vermelho.\n");
            break;
        case VERDE:
            printf("Cor: Verde.\n");
            break;
        case AZUL:
            printf("Cor: Azul.\n");
            break;
        case NENHUM:
            printf("Cor: Nenhum.\n");
            break;
        case AMARELO:
            printf("Cor: Amarelo.\n");
            break;
        case ROSA:
            printf("Cor: Rosa.\n");
            break;
        case CIANO:
            printf("Cor: Ciano.\n");
            break;
        default:
            printf("Cor desconhecida.\n");
            break;
    }
}

int main()
{
    HANDLE hSerial;
    char portName[] = "COM5";  // Substitua pela porta serial correta do seu Arduino
    char buffer[2];
    DWORD bytesRead;

    // Abre a porta serial
    hSerial = CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE)
    {
        printf("Erro ao abrir a porta serial.\n");
        return 1;
    }

    // Configura os parâmetros da porta serial
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        printf("Erro ao obter os parâmetros da porta serial.\n");
        CloseHandle(hSerial);
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600;  // Defina a taxa de transmissão correta
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams))
    {
        printf("Erro ao configurar os parâmetros da porta serial.\n");
        CloseHandle(hSerial);
        return 1;
    }

    while (1)
    {
        // Lê o input do usuário
        char userInput[2];
        printf("Digite:\n");
        printf("  1 - Para ligar o LED\n");
        printf("  2 - Para desligar o LED\n");
        printf("  3 - Para ler o estado do LED\n");
        printf("  4 - Para colocar o RGB como Vermelho\n");
        printf("  5 - Para colocar o RGB como Verde\n");
        printf("  6 - Para colocar o RGB como Azul\n");
        printf("  7 - Para exibir a cor do RGB\n");
        printf("  8 - Para mudar a cor RGB pelo potenciometro\n");
        printf("  9 - Para solicitar a leitura do LDR\n");

        fgets(userInput, sizeof(userInput), stdin);

        // Remove o caractere de nova linha (\n) da string de input
        userInput[strcspn(userInput, "\n")] = '\0';

        // Verifica a opção selecionada pelo usuário
        if (strcmp(userInput, "1") == 0)
        {
            enviarComando(hSerial, "1");
        }
        else if (strcmp(userInput, "2") == 0)
        {
            enviarComando(hSerial, "2");
        }
        else if (strcmp(userInput, "3") == 0)
        {
            enviarComando(hSerial, "3");
            lerEstadoLED(hSerial, buffer, &bytesRead);
            exibirEstadoLED(hSerial, buffer, bytesRead);
        }
        else if (strcmp(userInput, "4") == 0)
        {
            enviarComando(hSerial, "4");
        }
        else if (strcmp(userInput, "5") == 0)
        {
            enviarComando(hSerial, "5");
        }
        else if (strcmp(userInput, "6") == 0)
        {
            enviarComando(hSerial, "6");
        }
        else if (strcmp(userInput, "7") == 0)
        {
            enviarComando(hSerial, "7");
            lerEstadoLED(hSerial, buffer, &bytesRead);
            CorRGB cor = buffer[0];
            exibirCorRGB(cor);
        }
        else if (strcmp(userInput, "9") == 0)
        {
            enviarComando(hSerial, "9");
            lerEstadoLED(hSerial, buffer, &bytesRead);
        }
        else if (strcmp(userInput, "8") == 0)
        {
            enviarComando(hSerial, "8");
        }
        else
        {
            printf("Comando nao disponivel.\n");
        }
        // Limpa o buffer de entrada (stdin)
        clearInputBuffer();
    }

    // Fecha a porta serial (esse trecho nunca será alcançado porque o loop é infinito)
    CloseHandle(hSerial);

    return 0;
}
