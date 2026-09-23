#include <stdio.h>
#include <stdlib.h>

int is_fim(char str[])
{
    if((str[0] == 'F' || str[0] == 'f') && (str[1] == 'I' || str[1] == 'i') && (str[2] == 'M' || str[2] == 'm') && (str[3] == '\0' || str[3] == '\r')) return 1;
    return 0;
}

int is_vogal(char c)
{
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') return 1;
    return 0;
}

int is_letra(char c)
{
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return 1;
    return 0;
}

int so_vogais_rec(char s[], int i)
{
    if(s[i] == '\0' || s[i] == '\r') return 1;
    if(!is_vogal(s[i])) return 0;
    return so_vogais_rec(s, i + 1);
}

int so_consoantes_rec(char s[], int i)
{
    if(s[i] == '\0' || s[i] == '\r') return 1;
    if(!is_letra(s[i]) || is_vogal(s[i])) return 0;
    return so_consoantes_rec(s, i + 1);
}

int is_inteiro_rec(char s[], int i)
{
    if(s[i] == '\0' || s[i] == '\r') return 1;
    if((s[i] < '0' || s[i] > '9') && !(i == 0 && (s[i] == '-' || s[i] == '+'))) return 0;
    return is_inteiro_rec(s, i + 1);
}

int is_real_rec(char s[], int i, int qtd_pontos)
{
    if(s[i] == '\0' || s[i] == '\r') return 1;
    if(s[i] == '.' || s[i] == ',') qtd_pontos++;
    else if((s[i] < '0' || s[i] > '9') && !(i == 0 && (s[i] == '-' || s[i] == '+'))) return 0;
    if(qtd_pontos > 1) return 0;
    return is_real_rec(s, i + 1, qtd_pontos);
}

int main()
{
    char linha[1000];
    int flag = 1;
    while(flag && scanf(" %[^\n]", linha) == 1)
    {
        if(is_fim(linha)) flag = 0;
        else
        {
            if(so_vogais_rec(linha, 0)) printf("SIM ");
            else printf("NAO ");
            
            if(so_consoantes_rec(linha, 0)) printf("SIM ");
            else printf("NAO ");
            
            if(is_inteiro_rec(linha, 0)) printf("SIM ");
            else printf("NAO ");
            
            // O £ltimo tem o \n no lugar do espa‡o para quebrar a linha no Verde
            if(is_real_rec(linha, 0, 0)) printf("SIM\n");
            else printf("NAO\n");
        }
    }
    return 0;
}
