#include <stdio.h>
#include <stdlib.h>

int isFim(char str[])
{
    if((str[0] == 'F' || str[0] == 'f') && (str[1] == 'I' || str[1] == 'i') && (str[2] == 'M' || str[2] == 'm') && (str[3] == '\0' || str[3] == '\r')) return 1;
    return 0;
}

void cifra_rec(char str[], int i)
{
    if(str[i] == '\0' || str[i] == '\r') return;
    str[i] = (char)(str[i] + 3);
    cifra_rec(str, i + 1);
}

int main()
{
    char linha[1000];
    int flag = 1;
    while(flag && scanf(" %[^\n]", linha) == 1)
    {
        if(isFim(linha)) flag = 0;
        else
        {
            cifra_rec(linha, 0);
            printf("%s\n", linha);
        }
    }
    return 0;
}
