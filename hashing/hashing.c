#include <stdio.h>
#include <string.h>
#define N 17 

typedef struct registro{
    int matricula;
    char nome[50];
    char curso[50];
    int disponibilidade;
  }registro;

void inicializar(char* nomeArq){
    FILE* arq = fopen(nomeArq, "wb");
    registro a;
    int i;
    a.disponibilidade = 1;
    for (i = 0; i<N;i++) {
      fwrite(&a, sizeof(registro), 1,arq);
    }
    fclose(arq);
  }

int hash(int key){
    key = key % 1000;
    return key % N;
  }

int achar_posicao(char* nomeArq, int matricula) {
    int pos = hash(matricula);
    registro a;
    FILE* arq = fopen(nomeArq, "rb");
    fseek(arq, pos*sizeof(registro), SEEK_SET);
    fread(&a, sizeof(registro), 1, arq);
    while (a.disponibilidade == 0) {
      pos = (pos+1)%N;
      fseek(arq, pos*sizeof(registro), SEEK_SET);
      fread(&a, sizeof(registro), 1, arq);
    }
    fclose(arq);
    return pos; 
  }

void inserir(char* nomeArq,int matricula, char nome[], char curso[]){
    int pos = achar_posicao(nomeArq,matricula);
    FILE* arq = fopen(nomeArq, "r+b");
    registro a;
    a.matricula = matricula;
    strcpy(a.nome, nome);
    strcpy(a.curso, curso);
    a.disponibilidade = 0;
    fseek(arq, pos*sizeof(registro), SEEK_SET);
    fwrite(&a, sizeof(registro), 1, arq);
    fclose(arq); 
  }

void print_registro(char* nomeArq, int matricula){
    int pos = achar_posicao(nomeArq, matricula);
    registro a;
    FILE* arq = fopen(nomeArq, "rb");
    fseek(arq, pos*sizeof(registro), SEEK_SET);
    fread(&a, sizeof(registro), 1, arq);
    fclose(arq);
    printf("| %d |", a.matricula);
    printf("| %s |", a.nome);
    printf("| %s |", a.curso);
  }

 void imprime(char* nomeArq, int matricula){
    FILE* arq = fopen(nomeArq, "rb");
    int pos = hash(matricula);
    registro a;
    fseek(arq, pos*sizeof(registro), SEEK_SET);
    fread(&a, sizeof(registro), 1, arq);
    int pos_inicial = pos;
    while (a.matricula != matricula && a.matricula != 0) {
      puts("ocupado");
      pos = (pos+1)%N;
      fseek(arq, pos*sizeof(registro), SEEK_SET);
      fread(&a, sizeof(registro), 1, arq);
      if (pos == pos_inicial) {
        puts("aluno nao encontrado");
        fclose(arq);
        return;
      }
    }
    if (a.matricula == matricula) {
      printf("| %d | | %s | | %s | \n ", a.matricula, a.nome, a.curso);
    }
    fclose(arq);
  }

void imprime_tabela(char* nomeArq){
    FILE* arq = fopen(nomeArq, "rb");
    registro a;
    for (int i = 0; i<N; i++) {
      fread(&a, sizeof(registro), 1, arq);
      printf("Posicao: %d | Matricula: %d | Nome: %s | Curso: %s \n ", i, a.matricula, a.nome, a.curso);
    }
    fclose(arq);
  }

int main() {  
    int opcoes, matricula, matricula_print;
    char nome[50];
    char curso[50];
    char *arquivo = "arq";
    inicializar(arquivo);
    do {
      puts("1.inserir um novo aluno(matricula, nome, curso)");
      puts("2.imprimir as informacoes");
      puts("3.imprimir a tabela de hash");
      puts("4.Sair");
      puts("Escolha uma opcao: "); 
      scanf("%d", &opcoes);
      switch (opcoes) {
        case 1:
          puts("Digite metricula nome e curso *RESPECTIVAMENTE*");
          scanf("%d %49s %49s", &matricula, nome, curso);
          inserir(arquivo, matricula, nome, curso); 
        break;
          
        case 2:
          puts("digite a matricula");
          scanf("%d", &matricula_print);
          imprime(arquivo, matricula_print);
        break;
        
        case 3:
          imprime_tabela(arquivo);
        break;

        case 4:
        break; 
      }
    }while (opcoes != 4);  
  }
