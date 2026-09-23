#include <stdio.h>

int count(char str[])				//recursao para contagem percorrendo array 
{
	if(*str == '\0')return 0;						//condicao de parada recursiva
	else return (1 + count(str + 1));
}
void swap(char *str, int i, int posi_f) 			//funcao para trocar os elementos de posicao
{													//manipulacao de ponteiros para percorrer string
	
	char temp = *(str + i);
	*(str + i) = *(str + posi_f);
	*(str + posi_f) = temp;
}

char *inverte(int tam, char str[])
{
	int i = 0;
	for(i; i <= tam/2; i++)							//condiciona para metade do array para nao trocar posicoes equidistantes duas vezes (ficaria como a string original)
	{
		swap(str, i, tam - i);						//chama a funcao passando valores de posicoes equidistantes para troca
	}
	return str;
}
int main()
{
	//declaração de variáveis
	char string[100];
 	int n;
 	int flag = 1; 
// 	printf("Iniciando iteracao...\n");
// 	printf("Digite uma palavra ou frase(ou fim para interromper):\n");
	while(flag != 0)
	{
		scanf(" %[^\n]", string);	
	 	if((string [0] == 'f' || string[0] == 'F') && (string[1] == 'i' || string[1] == 'I') && (string[2] == 'm' || string[2] == 'M')) flag = 0;	 //verifica se string inserida é "fim"
	 	else
	 	{
			n = count(string)- 1;				//faz chamada da recursao para contagem do tamanho de string
 			printf("%s\n", inverte(n, string));		//printa a string ivertida retornada pela função iterativa
	 	}
 		
 	}
// 	printf("Finalizando iteracao...");
	return 0;

}
