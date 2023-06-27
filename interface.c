#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
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

    while (1) {
        // Lê o input do usuário
        char userInput[2];
        printf("Digite:\n");
        printf("  1 - Para ligar o LED\n");
        printf("  2 - Para desligar o LED\n");
        printf("  3 - Para ler o estado do LED\n");
        printf("  4 - Para colocar o RGB como Vermelho\n");
        printf("  5 - Para colocar o RGB como Azul\n");
        printf("  6 - Para colocar o RGB como Verde\n");
        prinfg("  7 - Para exibir a cor do RGB\n");
        printf("Opção: ");
        fgets(userInput, sizeof(userInput), stdin);

        // Remove o caractere de nova linha (\n) da string de input
        userInput[strcspn(userInput, "\n")] = '\0';

        // Verifica a opção selecionada pelo usuário
        if (strcmp(userInput, "1") == 0) {
            // Escreve na porta serial para ligar o LED
            char data[] = "1";
            DWORD bytesWritten;
            if (!WriteFile(hSerial, data, sizeof(data), &bytesWritten, NULL))
            {
                printf("Erro ao escrever na porta serial.\n");
                CloseHandle(hSerial);
                return 1;
            }
            printf("Comando para ligar o LED enviado.\n");
        }
        else if (strcmp(userInput, "2") == 0) {
            // Escreve na porta serial para verificar o estado do LED
            char data[] = "2";
            DWORD bytesWritten;
            if (!WriteFile(hSerial, data, sizeof(data), &bytesWritten, NULL))
            {
                printf("Erro ao escrever na porta serial.\n");
                CloseHandle(hSerial);
                return 1;
            }
            printf("Comando para verificar o estado do LED enviado.\n");
        }
        else if (strcmp(userInput, "3") == 0) {
            // Escreve na porta serial para solicitar o estado do LED
            char data[] = "3";
            DWORD bytesWritten;
            if (!WriteFile(hSerial, data, sizeof(data), &bytesWritten, NULL))
            {
                printf("Erro ao escrever na porta serial.\n");
                CloseHandle(hSerial);
                return 1;
            }
            printf("Comando para imprimir o estado do LED enviado.\n");

            // Lê o estado do LED
            if (!ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL))
            {
                printf("Erro ao ler o estado do LED.\n");
                CloseHandle(hSerial);
                return 1;
            }

            // Verifica o estado do LED e exibe na tela
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
                    return 1;
                }
            }
        }
        else if (strcmp(userInput, "4") == 0) {
            // Escreve na porta serial para verificar o estado do LED
            char data[] = "4";
            DWORD bytesWritten;
            if (!WriteFile(hSerial, data, sizeof(data), &bytesWritten, NULL))
            {
                printf("Erro ao escrever na porta serial.\n");
                CloseHandle(hSerial);
                return 1;
            }
            printf("Comando para mudar a cor do RGB enviado.\n");
        }
        else if (strcmp(userInput, "5") == 0) {
            // Escreve na porta serial para verificar o estado do LED
            char data[] = "5";
            DWORD bytesWritten;
            if (!WriteFile(hSerial, data, sizeof(data), &bytesWritten, NULL))
            {
                printf("Erro ao escrever na porta serial.\n");
                CloseHandle(hSerial);
                return 1;
            }
            printf("Comando para mudar a cor do RGB enviado.\n");
        }
        else if (strcmp(userInput, "6") == 0) {
            // Escreve na porta serial para verificar o estado do LED
            char data[] = "6";
            DWORD bytesWritten;
            if (!WriteFile(hSerial, data, sizeof(data), &bytesWritten, NULL))
            {
                printf("Erro ao escrever na porta serial.\n");
                CloseHandle(hSerial);
                return 1;
            }
            printf("Comando para mudar a cor do RGB enviado.\n");
        } else if (strcmp(userInput, "7") == 0) {
            char data[] = "7";
            DWORD bytesWritten;
            if (!WriteFile(hSerial, data, sizeof(data), &bytesWritten, NULL))
            {
                printf("Erro ao escrever na porta serial.\n");
                CloseHandle(hSerial);
                return 1;
            }
            printf("Comando para imprimir o estado do LED enviado.\n");

            // Lê o estado do LED
            if (!ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL))
            {
                printf("Erro ao ler o estado do LED.\n");
                CloseHandle(hSerial);
                return 1;
            }

            // Verifica o estado do LED e exibe na tela
            if (bytesRead > 0)
            {
                if (buffer[0] == '1')
                {
                    printf("Vermelho.\n");
                }
                else if (buffer[0] == '2')
                {
                    printf("Verde\n");
                }
                else if (buffer[0] == '3')
                {
                    printf("Azul\n");
                }
            }
            while (bytesRead > 0 && buffer[bytesRead - 1] != '\n')
            {
                if (!ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL))
                {
                    printf("Erro ao ler o estado do LED.\n");
                    CloseHandle(hSerial);
                    return 1;
                }
            }
        }
        // Limpa o buffer de entrada (stdin)
        clearInputBuffer();
    }

    // Fecha a porta serial (esse trecho nunca será alcançado porque o loop é infinito)
    CloseHandle(hSerial);

    return 0;
}
