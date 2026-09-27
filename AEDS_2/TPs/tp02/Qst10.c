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

typedef struct {
    Veiculo vet[5];
    int inicio;
    int fim;
    int n;
} Fila;

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

    token = strtok(rest, ","); v.id = atoi(token);
    token = strtok(NULL, ","); strcpy(v.marca, token);
    token = strtok(NULL, ","); strcpy(v.modelo, token);
    token = strtok(NULL, ","); v.ano = atoi(token);
    token = strtok(NULL, ","); strcpy(v.categoria, token);
    token = strtok(NULL, ","); strcpy(v.combustivel, token);
    token = strtok(NULL, ","); v.cilindros = atoi(token);
    token = strtok(NULL, ","); v.cilindrada = atof(token);
    token = strtok(NULL, ","); strcpy(v.transmissao, token);
    token = strtok(NULL, ","); strcpy(v.tracao, token);
    token = strtok(NULL, ","); v.consumoCidade = atof(token);
    token = strtok(NULL, ","); v.consumoEstrada = atof(token);
    token = strtok(NULL, ","); v.co2 = atof(token);
    token = strtok(NULL, ","); v.turbo = (strcmp(token, "true") == 0);
    token = strtok(NULL, ","); v.dataRegistro = parseData(token);

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

void filaInit(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->n = 0;
}

void filaInserir(Fila *f, Veiculo v) {
    if (f->n == 5) {
        Veiculo r = f->vet[f->inicio];
        printf("(R)%s %s\n", r.marca, r.modelo);
        f->inicio = (f->inicio + 1) % 5;
        f->n--;
    }
    f->vet[f->fim] = v;
    f->fim = (f->fim + 1) % 5;
    f->n++;
}

Veiculo filaRemover(Fila *f) {
    Veiculo r = f->vet[f->inicio];
    f->inicio = (f->inicio + 1) % 5;
    f->n--;
    return r;
}

void filaMostrar(Fila *f) {
    char buffer[500];
    int i = f->inicio;
    for (int k = 0; k < f->n; k++) {
        formatVeiculo(f->vet[i], buffer);
        printf("%s\n", buffer);
        i = (i + 1) % 5;
    }
}

int main() {
    int n;
    Veiculo *todos = lerCsv("/tmp/veiculos.csv", &n);

    if (todos == NULL || n == 0) {
        return 0;
    }

    Fila fila;
    filaInit(&fila);

    int id;
    while (scanf("%d", &id) == 1) {
        if (id == -1) break;
        for (int i = 0; i < n; i++) {
            if (todos[i].id == id) {
                filaInserir(&fila, todos[i]);
                break;
            }
        }
    }

    int q;
    scanf("%d", &q);

    for (int k = 0; k < q; k++) {
        char cmd[10];
        scanf("%s", cmd);
        if (strcmp(cmd, "I") == 0) {
            int idIns;
            scanf("%d", &idIns);
            for (int i = 0; i < n; i++) {
                if (todos[i].id == idIns) {
                    filaInserir(&fila, todos[i]);
                    break;
                }
            }
        } else if (strcmp(cmd, "R") == 0) {
            if (fila.n > 0) {
                Veiculo r = filaRemover(&fila);
                printf("(R)%s %s\n", r.marca, r.modelo);
            }
        }
    }

    filaMostrar(&fila);

    free(todos);
    return 0;
}