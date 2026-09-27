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

typedef struct Celula {
    Veiculo elemento;
    struct Celula* prox;
} Celula;

typedef struct {
    Celula* inicio;
    Celula* fim;
    int n;
} Lista;

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

Celula* novaCelula(Veiculo v) {
    Celula* c = (Celula*) malloc(sizeof(Celula));
    c->elemento = v;
    c->prox = NULL;
    return c;
}

void listaInit(Lista* l) {
    l->inicio = NULL;
    l->fim = NULL;
    l->n = 0;
}

void inserirInicio(Lista* l, Veiculo v) {
    Celula* c = novaCelula(v);
    c->prox = l->inicio;
    l->inicio = c;
    if (l->n == 0) {
        l->fim = c;
    }
    l->n++;
}

void inserirFim(Lista* l, Veiculo v) {
    Celula* c = novaCelula(v);
    if (l->n == 0) {
        l->inicio = c;
        l->fim = c;
    } else {
        l->fim->prox = c;
        l->fim = c;
    }
    l->n++;
}

void inserir(Lista* l, Veiculo v, int pos) {
    if (pos <= 0) {
        inserirInicio(l, v);
        return;
    }
    if (pos >= l->n) {
        inserirFim(l, v);
        return;
    }
    Celula* ant = l->inicio;
    for (int i = 0; i < pos - 1; i++) {
        ant = ant->prox;
    }
    Celula* c = novaCelula(v);
    c->prox = ant->prox;
    ant->prox = c;
    l->n++;
}

Veiculo removerInicio(Lista* l) {
    Veiculo r = l->inicio->elemento;
    Celula* tmp = l->inicio;
    l->inicio = l->inicio->prox;
    if (l->inicio == NULL) {
        l->fim = NULL;
    }
    free(tmp);
    l->n--;
    return r;
}

Veiculo removerFim(Lista* l) {
    Veiculo r = l->fim->elemento;
    if (l->n == 1) {
        free(l->inicio);
        l->inicio = NULL;
        l->fim = NULL;
    } else {
        Celula* ant = l->inicio;
        while (ant->prox != l->fim) {
            ant = ant->prox;
        }
        free(l->fim);
        l->fim = ant;
        l->fim->prox = NULL;
    }
    l->n--;
    return r;
}

Veiculo remover(Lista* l, int pos) {
    if (pos <= 0) {
        return removerInicio(l);
    }
    if (pos >= l->n - 1) {
        return removerFim(l);
    }
    Celula* ant = l->inicio;
    for (int i = 0; i < pos - 1; i++) {
        ant = ant->prox;
    }
    Celula* tmp = ant->prox;
    Veiculo r = tmp->elemento;
    ant->prox = tmp->prox;
    free(tmp);
    l->n--;
    return r;
}

void mostrar(Lista* l) {
    char buffer[500];
    Celula* c = l->inicio;
    while (c != NULL) {
        formatVeiculo(c->elemento, buffer);
        printf("%s\n", buffer);
        c = c->prox;
    }
}

int main() {
    int n;
    Veiculo *todos = lerCsv("/tmp/veiculos.csv", &n);

    if (todos == NULL || n == 0) {
        return 0;
    }

    Lista lista;
    listaInit(&lista);

    int id;
    while (scanf("%d", &id) == 1) {
        if (id == -1) break;
        for (int i = 0; i < n; i++) {
            if (todos[i].id == id) {
                inserirFim(&lista, todos[i]);
                break;
            }
        }
    }

    int q;
    scanf("%d", &q);

    for (int k = 0; k < q; k++) {
        char cmd[10];
        scanf("%s", cmd);
        if (strcmp(cmd, "II") == 0) {
            int idIns;
            scanf("%d", &idIns);
            for (int i = 0; i < n; i++) {
                if (todos[i].id == idIns) {
                    inserirInicio(&lista, todos[i]);
                    break;
                }
            }
        } else if (strcmp(cmd, "IF") == 0) {
            int idIns;
            scanf("%d", &idIns);
            for (int i = 0; i < n; i++) {
                if (todos[i].id == idIns) {
                    inserirFim(&lista, todos[i]);
                    break;
                }
            }
        } else if (strcmp(cmd, "I*") == 0) {
            int pos, idIns;
            scanf("%d %d", &pos, &idIns);
            for (int i = 0; i < n; i++) {
                if (todos[i].id == idIns) {
                    inserir(&lista, todos[i], pos);
                    break;
                }
            }
        } else if (strcmp(cmd, "RI") == 0) {
            if (lista.n > 0) {
                Veiculo r = removerInicio(&lista);
                printf("(R)%s %s\n", r.marca, r.modelo);
            }
        } else if (strcmp(cmd, "RF") == 0) {
            if (lista.n > 0) {
                Veiculo r = removerFim(&lista);
                printf("(R)%s %s\n", r.marca, r.modelo);
            }
        } else if (strcmp(cmd, "R*") == 0) {
            int pos;
            scanf("%d", &pos);
            if (lista.n > 0) {
                Veiculo r = remover(&lista, pos);
                printf("(R)%s %s\n", r.marca, r.modelo);
            }
        }
    }

    mostrar(&lista);
    free(todos);
    return 0;
}