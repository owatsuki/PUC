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

void formatData(Data d, char *buffer) {
    sprintf(buffer, "%02d/%02d/%04d", d.dia, d.mes, d.ano);
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

void formatVeiculo(Veiculo v, char *buffer) {
    char dataStr[20];
    formatData(v.dataRegistro, dataStr);
    
    char comb[100];
    strcpy(comb, v.combustivel);
    for (int i = 0; comb[i]; i++) {
        if (comb[i] == ';') comb[i] = ',';
    }
    
    sprintf(buffer, "[%d ## %s ## %s ## %d ## %s ## [%s] ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %s ## %s]",
        v.id, v.marca, v.modelo, v.ano, v.categoria, comb,
        v.cilindros, v.cilindrada, v.transmissao, v.tracao,
        v.consumoCidade, v.consumoEstrada, v.co2, v.turbo ? "true" : "false",
        dataStr);
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

void countingSort(Veiculo *vet, int n) {
    int maxCil = 20;
    int count[21];
    for (int i = 0; i <= maxCil; i++) {
        count[i] = 0;
    }
    
    for (int i = 0; i < n; i++) {
        count[vet[i].cilindros]++;
    }
    
    for (int i = 1; i <= maxCil; i++) {
        count[i] += count[i-1];
    }
    
    Veiculo *saida = (Veiculo*) malloc(n * sizeof(Veiculo));
    
    for (int i = n - 1; i >= 0; i--) {
        int cil = vet[i].cilindros;
        saida[count[cil] - 1] = vet[i];
        count[cil]--;
    }
    
    for (int i = 0; i < n; i++) {
        vet[i] = saida[i];
    }
    
    free(saida);
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
    
    countingSort(selecionados, m);
    
    char buffer[500];
    for (int i = 0; i < m; i++) {
        formatVeiculo(selecionados[i], buffer);
        printf("%s\n", buffer);
    }
    
    free(todos);
    return 0;
}