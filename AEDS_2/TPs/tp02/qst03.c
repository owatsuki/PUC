#include <stdio.h>
#include <string.h>

char* LeitorCsv()
{
	
}

int main()
{
	char buffer[100];
	FILE* veic = fopen("veiculos.csv", "r");
	FILE* arq = fopen("pub.in", "r");
	if (arq == NULL) return 1;

	while(fgets(buffer, sizeof(buffer), arq) != NULL)
	{
		
	}
	fclose(veic);
	fclose(arq);
}
