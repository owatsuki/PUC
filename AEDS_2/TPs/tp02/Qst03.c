#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int id;
    char marca[100];
    char modelo[100];
    int ano;
    char categoria[100];
    char combustivel[100];
    int cilindros;
    double cilindrada;
    char transmissao[100];
    char tracao[100];
    double consumoCidade;
    double consumoEstrada;
    double co2;
    bool turbo;
    Data dataRegistro;
} Veiculo;

Data parseData(char *s)
{
    Data d;
    int ano, mes, dia;

    sscanf(s, "%d-%d-%d", &ano, &mes, &dia);

    d.ano = ano;
    d.mes = mes;
    d.dia = dia;

    return d;
}

void formatData(Data d, char *buffer)
{
    sprintf(buffer, "%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

Veiculo parseVeiculo(char *s)
{
    Veiculo v;
    char *token;

    token = strtok(s, ",");
    v.id = atoi(token);

    token = strtok(NULL, ",");
    strcpy(v.marca, token);

    token = strtok(NULL, ",");
    strcpy(v.modelo, token);

    token = strtok(NULL, ",");
    v.ano = atoi(token);

    token = strtok(NULL, ",");
    strcpy(v.categoria, token);

    token = strtok(NULL, ",");
    strcpy(v.combustivel, token);

    token = strtok(NULL, ",");
    v.cilindros = atoi(token);

    token = strtok(NULL, ",");
    v.cilindrada = atof(token);

    token = strtok(NULL, ",");
    strcpy(v.transmissao, token);

    token = strtok(NULL, ",");
    strcpy(v.tracao, token);

    token = strtok(NULL, ",");
    v.consumoCidade = atof(token);

    token = strtok(NULL, ",");
    v.consumoEstrada = atof(token);

    token = strtok(NULL, ",");
    v.co2 = atof(token);

    token = strtok(NULL, ",");
    v.turbo = (strcmp(token, "true") == 0);

    token = strtok(NULL, ",");
    v.dataRegistro = parseData(token);

    return v;
}

void formatVeiculo(Veiculo v, char *buffer)
{
    char comb[50];

    strcpy(comb, v.combustivel);

    for (int i = 0; comb[i] != '\0'; i++)
    {
        if (comb[i] == ';')
        {
            comb[i] = ',';
        }
    }

    char dataStr[20];

    formatData(v.dataRegistro, dataStr);

    sprintf(buffer,
            "[%d ## %s ## %s ## %d ## %s ## [%s] ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %s ## %s]",
            v.id,
            v.marca,
            v.modelo,
            v.ano,
            v.categoria,
            comb,
            v.cilindros,
            v.cilindrada,
            v.transmissao,
            v.tracao,
            v.consumoCidade,
            v.consumoEstrada,
            v.co2,
            v.turbo ? "true" : "false",
            dataStr);
}

Veiculo* lerCsv(char *caminhoArquivo, int *n)
{
    FILE *arq = fopen(caminhoArquivo, "r");

    if (arq == NULL)
    {
        return NULL;
    }

    char linha[500];

    *n = 0;

    fgets(linha, 500, arq);

    while (fgets(linha, 500, arq) != NULL)
    {
        (*n)++;
    }

    fclose(arq);

    Veiculo *vet = (Veiculo*) malloc((*n) * sizeof(Veiculo));

    arq = fopen(caminhoArquivo, "r");

    fgets(linha, 500, arq);

    int i = 0;

    while (fgets(linha, 500, arq) != NULL)
    {
        linha[strcspn(linha, "\r\n")] = 0;

        vet[i] = parseVeiculo(linha);

        i++;
    }

    fclose(arq);

    return vet;
}

char minusculo(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        c = c + ('a' - 'A');
    }

    return c;
}

int compararModelo(char a[], char b[])
{
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0')
    {
        char ca = minusculo(a[i]);
        char cb = minusculo(b[i]);

        if (ca < cb)
        {
            return -1;
        }

        if (ca > cb)
        {
            return 1;
        }

        i++;
    }

    if (a[i] == '\0' && b[i] == '\0')
    {
        return 0;
    }

    if (a[i] == '\0')
    {
        return -1;
    }

    return 1;
}

void selectionSort(Veiculo *vet, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int menor = i;

        for (int j = i + 1; j < n; j++)
        {
            if (compararModelo(vet[j].modelo, vet[menor].modelo) < 0)
            {
                menor = j;
            }
        }

        if (menor != i)
        {
            Veiculo aux = vet[i];
            vet[i] = vet[menor];
            vet[menor] = aux;
        }
    }
}

int main()
{
    int n;

    Veiculo *todos = lerCsv("/tmp/veiculos.csv", &n);

    if (todos == NULL)
    {
        return 0;
    }

    Veiculo *selecionados = (Veiculo*) malloc(n * sizeof(Veiculo));

    int qtd = 0;
    int id;

    while (scanf("%d", &id) == 1)
    {
        if (id == -1)
        {
            break;
        }

        for (int i = 0; i < n; i++)
        {
            if (todos[i].id == id)
            {
                selecionados[qtd] = todos[i];
                qtd++;

                break;
            }
        }
    }

    selectionSort(selecionados, qtd);

    char buffer[500];

    for (int i = 0; i < qtd; i++)
    {
        formatVeiculo(selecionados[i], buffer);

        printf("%s\n", buffer);
    }

    free(todos);
    free(selecionados);

    return 0;
}