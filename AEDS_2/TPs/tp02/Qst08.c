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

Data parseData(char *s) {
    Data d;
    int ano, mes, dia;
    sscanf(s, "%d-%d-%d", &ano, &mes, &dia);
    d.ano = ano;
    d.mes = mes;
    d.dia = dia;
    return d;
}

Veiculo parseVeiculo(char *s) {
    Veiculo v;
    char *token;
    char *rest = s;

    token = strtok(rest, ",");
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

Veiculo* lerCsv(char *caminho, int *n) {
    FILE *arq = fopen(caminho, "r");
    if (arq == NULL) {
        *n = 0;
        return NULL;
    }

    char linha[500];
    if (fgets(linha, sizeof(linha), arq) == NULL) {
        fclose(arq);
        *n = 0;
        return NULL;
    }

    int count = 0;
    while (fgets(linha, sizeof(linha), arq) != NULL) {
        count++;
    }

    Veiculo *vet = (Veiculo*) malloc(count * sizeof(Veiculo));

    rewind(arq);
    fgets(linha, sizeof(linha), arq);

    int i = 0;
    while (fgets(linha, sizeof(linha), arq) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';
        if (strlen(linha) > 0) {
            vet[i] = parseVeiculo(linha);
            i++;
        }
    }

    fclose(arq);
    *n = i;
    return vet;
}

void selectionSort(Veiculo *vet, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(vet[j].modelo, vet[min].modelo) < 0) {
                min = j;
            }
        }
        if (min != i) {
            Veiculo aux = vet[i];
            vet[i] = vet[min];
            vet[min] = aux;
        }
    }
}

int buscaBinaria(Veiculo *vet, int n, char *chave) {
    int esq = 0, dir = n - 1;
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        int cmp = strcmp(vet[meio].modelo, chave);
        if (cmp == 0) return 1;
        else if (cmp < 0) esq = meio + 1;
        else dir = meio - 1;
    }
    return 0;
}

int main() {
    int n;
    Veiculo *todos = lerCsv("/tmp/veiculos.csv", &n);

    if (todos == NULL || n == 0) {
        return 0;
    }

    Veiculo selecionados[10000];
    int m = 0;

    int id;
    while (scanf("%d", &id) == 1) {
        if (id == -1) break;
        for (int i = 0; i < n; i++) {
            if (todos[i].id == id) {
                selecionados[m] = todos[i];
                m++;
                break;
            }
        }
    }

    selectionSort(selecionados, m);

    char linha[200];
    fgets(linha, sizeof(linha), stdin);

    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';
        if (strcmp(linha, "FIM") == 0) break;
        if (buscaBinaria(selecionados, m, linha)) {
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }
    }

    free(todos);
    return 0;
}