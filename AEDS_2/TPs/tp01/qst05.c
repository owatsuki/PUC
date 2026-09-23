#include <stdio.h>

int soma_num(int num)
{
	int soma = 0; 				//variavel para guardar somatorio dos algarismos
	while(num>=10)
	{
		soma += num % 10;		//operação para extrair unidades de num
		num /= 10;				//reatribui num removendo ultimo digito
	}
	return soma + num;			//retorna o soma + a unidade restante
}

int main()
{
	int n, flag = 0;
	while(flag < 50)
	{
		scanf("%d", &n);
		printf("%d\n",(soma_num(n)));
	}
	return 0;
}
