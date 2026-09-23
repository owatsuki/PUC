
#include <stdio.h>
#include <stdlib.h>

int isFim(char str[])
{
    if((str[0] == 'F' || str[0] == 'f') && (str[1] == 'I' || str[1] == 'i') && (str[2] == 'M' || str[2] == 'm') && str[3] == '\0') return 1;
    return 0;
}
int isAnagrama(char str1[], char str2[])
{
    int contagem[256] = {0};
    for(int i = 0; str1[i] != '\0'; i++)
    {
        contagem[(int)str1[i]]++;
    }
    for(int i = 0; str2[i] != '\0'; i++)
    {
        contagem[(int)str2[i]]--;
    }
    for(int i = 0; i < 256; i++)
    {
        if(contagem[i] != 0) return 0; 
    }
    return 1; 
}

int main()
{
    char string1[100];
    char string2[100];
    int flag = 1;

    while(flag && scanf("%s", string1) == 1)
    {
        if(isFim(string1)) flag = 0;  
        else
        {
            scanf("%s", string2);
            if(isAnagrama(string1, string2)) printf("SIM\n");
            else printf("NAO\n");
        }
    }

    return 0;
}
