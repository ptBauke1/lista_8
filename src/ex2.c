/* 
 * Enunciado: 
 *    Repita o exercício anterior, mas agora utilize como entrada o arquivo
 *    notas.csv. A quantidade de alunos pode ser diferente de 3.
 *
 * Exemplo de linha:
 *    Rodrigo,1,2,3,4
 *
 *    Note que o separador utilizado é a vírgula
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define MAX 100

typedef struct {
  char nome[MAX];
  float notas[4];
  float media;
} Aluno;

typedef struct SLista {
  Aluno aluno;
  struct SLista* prox;
} TLista;

/* Funções recomendadas */
Aluno ler_aluno(FILE *file);
void exibe_aluno(Aluno a);
float calcula_media(float* notas);

TLista* cria_lista();
TLista* destroi_lista(TLista* alunos);
void insere_no_fim(TLista *alunos, Aluno aluno);

/* Funções para uso livre */
void exibe_lista(TLista* alunos); // exibe uma lista de alunos
void ler_string(char* s); // le uma string de forma "segura"

void lerLinha(char linha[MAX], FILE *arq);

int main (int argc, char *argv[])
{
  system("cls");

  TLista *lista_alunos;
  lista_alunos = cria_lista();

  Aluno aluno;
  FILE *file;

  file = fopen("../../notas.csv", "r");
  if (file == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  do {
  aluno = ler_aluno(file);

  insere_no_fim(lista_alunos, aluno);

  } while (!feof(file));

  fclose(file);
  exibe_lista(lista_alunos);
  system("pause");
  lista_alunos = destroi_lista(lista_alunos);

  return EXIT_SUCCESS;
}

Aluno ler_aluno(FILE *file) {
  char token[MAX];
  Aluno aux;
  lerLinha(token, file);
  strcpy(aux.nome, strtok(token, ","));

  for(int i = 0; i < 4; i++) {
    aux.notas[i] = atof(strtok(NULL, ","));
  }

  aux.media = calcula_media(aux.notas);
  return aux;
}

float calcula_media(float* notas) {
  float media = 0;
  for (int i = 0; i < 4; i++) {
    media += notas[i];
  }
  return media/4;
}

TLista* cria_lista() {
  TLista *p;
  p = (TLista*) malloc(sizeof(TLista));
  if (p == NULL) {
    printf("Não pode criar a lista");
    exit(EXIT_FAILURE);
  }

  p->prox = NULL;
  return p;
}

TLista* destroi_lista(TLista* alunos) {
  TLista *aux;
  aux = alunos;
  while(aux->prox != NULL) {
    aux = aux->prox;
    free(alunos);
    alunos = aux;
  }
  free(alunos);
  return NULL;
}

void insere_no_fim(TLista *alunos, Aluno aluno) {
  TLista* novo;
  novo = (TLista*) malloc(sizeof(TLista));
  if (novo == NULL) {
    printf("Nao foi possivel alocar memoria!");
    exit(EXIT_FAILURE);
  }

  novo->aluno = aluno;
  TLista *aux;
  aux = alunos;
  while(aux->prox != NULL)
    aux = aux->prox;

  novo->prox = NULL;
  aux->prox = novo;
}

void exibe_aluno(Aluno a) {
  printf("(%s | %.2f)", a.nome, a.media);
}

void exibe_lista(TLista* alunos) {
  TLista *aux = alunos->prox;
  while(aux != NULL) {
    exibe_aluno(aux->aluno);
    if( aux->prox != NULL ) printf(" -> ");
    aux = aux->prox;
  }
  printf("\n");
}

void ler_string(char* s) {
  scanf("\n");
  fgets(s, MAX, stdin);
  size_t tam = strlen(s);
  if( s[tam-1] == '\n' ) s[tam-1] = '\0';
}

void lerLinha(char linha[MAX], FILE *arq){
fgets(linha, MAX, arq);
if(linha[strlen(linha)-1] == '\n')
linha[strlen(linha)-1] = '\0';
}
