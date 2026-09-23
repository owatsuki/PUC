
#include <stdio.h>
#include <stdlib.h>

int isFim(char str[])
{
    if((str[0] == 'F' || str[0] == 'f') && (str[1] == 'I' || str[1] == 'i') && (str[2] == 'M' || str[2] == 'm') && (str[3] == '\0' || str[3] == '\r')) return 1;
    return 0;
}

int maiorSubstring(char str[])
{
    int maior_vet[256];
    for(int i = 0; i < 256; i++) maior_vet[i] = -1;
    int max_tam = 0;
    int posi_ini = 0;
    for(int i = 0; str[i] != '\0' && str[i] != '\r'; i++)
    {
        int char_atual = (int)str[i];
        if(maior_vet[char_atual] >= posi_ini) posi_ini = maior_vet[char_atual] + 1;
        maior_vet[char_atual] = i;
        int atual_tam = i - posi_ini + 1;
        if(atual_tam > max_tam) max_tam = atual_tam;
    }
    return max_tam;
}

int main()
{
    char linha[1000];
    int flag = 1;
    while(flag && scanf(" %[^\n]", linha) == 1)
    {
        if(isFim(linha)) flag = 0;
        else printf("%d\n", maiorSubstring(linha));
    }
    return 0;
}
