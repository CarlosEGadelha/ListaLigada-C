#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    char info[64];
    struct no * prox;
} No;

typedef struct no * link; 

typedef struct {
    link ini ;
    link fim;
} Lista;

link novo_no(char c[]) {
    link novo;
    novo = malloc(64*sizeof(char));
    strcpy(novo->info, c);
    novo->prox = NULL;
    return novo;
}

Lista insere_inicio(Lista lista, char nome[]) {
    link novo = novo_no(nome);
    if (lista.ini == NULL) 
        lista.fim = novo;
    else 
        novo->prox = lista.ini;

    lista.ini = novo;
    return lista;
}

Lista insere_fim(Lista lista, char nome[]) {
    link novo = novo_no(nome);

    if (lista.ini == NULL)
        lista.ini = novo;
    else
        lista.fim->prox = novo;

    lista.fim = novo;
    return lista;
}

void imprime(Lista lista) {
    link p;
    for (p = lista.ini; p != NULL; p = p->prox)
        printf("%s\n", p->info);
    printf("\n");
}

void libera_rec(link ini) {
    if (ini == NULL) return;
    libera_rec(ini->prox);
    free(ini);
}

void libera(Lista lista) {
    libera_rec(lista.ini); 
}

Lista insere_ordenado(Lista lista, char nome[]) {
    if (lista.ini == NULL || strcmp(nome, lista.ini->info) < 0){
        return insere_inicio(lista, nome);
    }
    else if (strcmp(nome, lista.fim->info) > 0) {
        return insere_fim(lista, nome);
    }
    else {
        link novo = novo_no(nome);
        link p = lista.ini;
        while(strcmp(p->prox->info, nome) < 0)
            p = p->prox;

        novo->prox = p->prox;
        p->prox = novo;
    }
    return lista;
}

int main() {
    Lista lista;
    lista.ini = lista.fim = NULL;

  char string[100];
  char comando[2];
  char espaco[2];
  char nome[64];

  printf("i NOME para inserir um nome\nd NOME para deletar\np para Imprimir a lista\nq para Sair\n\n");

  do{
    printf("Digite:");
    fgets(string, 100, stdin);

    sscanf(string,"%1[^\n]%1[^\n]%64[^\n]", comando, espaco, nome);

    if(strcmp(comando, "i")==0 && strcmp(espaco, " ")==0){
      lista = insere_ordenado(lista,nome);
    }
    else if(strcmp(comando, "p")==0){
      printf("\n");
      imprime(lista);
    }
    else if(strcmp(comando, "q")!=0){
      printf("Digite um comando válido.\n");
    }
  }while(strcmp(comando, "q")!=0);

  printf("Saiu do programa");

  libera(lista);

  return 0;
}