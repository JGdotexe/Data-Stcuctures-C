#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct arvore{
    int info;
    struct arvore *left;
    struct arvore *right;
}arvore;

void imprime_pre_ordem(arvore* a){
    if (a == NULL) {
      return;
    }

    printf("%d\n", a->info);
    imprime_pre_ordem(a->left);
    imprime_pre_ordem(a->right);
  }

void imprime_em_ordem(arvore *a){
    if (a == NULL) {
      return; 
    }

    imprime_em_ordem(a->left);
    printf("%d\n", a->info);
    imprime_em_ordem(a->right);
  }

void imprime_pos_ordem(arvore *a){
    if (a == NULL) {
      return; 
    }

    imprime_pos_ordem(a->left);
    imprime_pos_ordem(a->right);  
    printf("%d\n", a->info);
  }


int existe(arvore* a, int x){
    if (a == NULL) return 0;
    
    else if (a->info == x) return 1;

    else {
      int ret = existe(a->left,x);
      if (ret == 1) return 1;
      return existe(a->right,x);
    }
  }

int quantos_elementos(arvore* a){
    int contador = 0;
    if (a == NULL) return 0;
     
    return 1+quantos_elementos(a->left)+quantos_elementos(a->right);
  }

 void imprime_folhas(arvore* a){
    if (a == NULL) return ;
    
    if (a->left == NULL && a->right == NULL) {
      printf("%d\n", a->info);
      imprime_folhas(a->left);
      imprime_folhas(a->right);
    }
  }

int altura(arvore* a){
    if (a == NULL) {
      return 0;
    }

    int hl = altura(a->left);
    int hr = altura(a->right);
    if (hl > hr) {
      return hl+1;
    }else {
      return hr+1;
    }
  }

int conta_nivel(arvore* a, int cont, int n){
    if (a == NULL) {
      return 0;
    }

    if (cont == n) {
      return 1;
    }else {
      return conta_nivel(a->left, cont+1, n)+conta_nivel(a->right, cont+1, n);
    }
  }

void imprime_nivel_no(arvore* a, int data, int nivel){
    if (a ==  NULL) return;
    
    if (a->info == data) printf("\n nivel %d\n", nivel);
    
    imprime_nivel_no(a->left, data, nivel+1); 
    imprime_nivel_no(a->right, data, nivel+1);
  }

void imprime_nivel(arvore* a, int nivel_atual, int nivel_desejado) {
    if (a == NULL) return;

    if (nivel_atual == nivel_desejado) {
        printf("%d ", a->info);
    } else {
        imprime_nivel(a->left, nivel_atual + 1, nivel_desejado);
        imprime_nivel(a->right, nivel_atual + 1, nivel_desejado);
    }
}

void imprime_em_largura(arvore* a){
    if (a == NULL) return;

    int h = altura(a);
    for (int i = 0; i < h; i++) {
        printf("Nivel %d: ", i);
        imprime_nivel(a, 0, i);
        printf("\n");
    }
  }

 int balanceamento(arvore* a){
    if (a == NULL) {
      return 1;
    }
      
    int hl = altura(a->left);
    int hr = altura(a->right);
    if (abs(hl-hr)>1){
      return 0;
    }
    
    return balanceamento(a->left) && balanceamento(a->right);
  }

int esta_cheia(arvore* a){
    int quantidade = quantos_elementos(a);
    int alt = altura(a);
    if (quantidade == (pow(quantidade, alt)-1)) return 1;
    
    return 0;
  }

arvore* lerarvore(FILE * arq){
    char c;
    int num;

    fscanf(arq, "%c", &c);
    fscanf(arq, "%d", &num);

    if (num == -1) {
      fscanf(arq,"%c",&c);
      return NULL;
    }

    arvore* a = (arvore*)malloc(sizeof(arvore));
    a->info = num;
    a->left = lerarvore(arq);
    a->right = lerarvore(arq);
    fscanf(arq, "%c", &c);
    return a;
  }

int main(){
  arvore* a; 
  FILE* arq;
  int nivel;
  int opcoes;
  char nome_arquivo[30];
  int opcao_imprecao = 0;
  int numero;
  int number;
  int quantos;
  int balanceada;
  int cheia;
  do {
  puts("\nAtividade JG");
  puts("1. Ler arvore:");
  puts("2. Imprimir");
  puts("3. Procurar elemento");
  puts("4. Contar numero de elementos");
  puts("5. Imprimir nos folha");
  puts("6. Verificar balanceamento");
  puts("7. Verificar se a arvore esta cheia");
  puts("8. Imprimir nivel");
  puts("9. Sair");

  puts("Escolha uma opcao: ");
  scanf("%d", &opcoes);

  switch (opcoes) {
    
    case 1:
      puts("Digite o nome do seu arquivo .txt (ate 30 caracteres)");
      scanf("%s", nome_arquivo);
      arq = fopen(nome_arquivo,"rt");
      if (arq == NULL) {
        puts("Erro ao abrir o arquivo"); 
      } else {
        a = lerarvore(arq);
        fclose(arq);
        puts("Arquivo lido com sucesso");
      }
      break;

    case 2:
        do {
          puts("1.Imprimir pre ordem");
          puts("2.Imprimir em ordem");
          puts("3.Imprimir pos ordem");
          puts("4.Imprimir em largura");
          puts("5.Voltar para o menu principal");
        
        puts("Escolha uma opcao para impressao: ");
        scanf("%d", &opcao_imprecao);

        switch (opcao_imprecao) {
          case 1: 
            imprime_pre_ordem(a);
          break;
          
          case 2:
            imprime_em_ordem(a);
          break;
          
          case 3:
            imprime_pos_ordem(a);
          break;
          
          case 4:
            imprime_em_largura(a);
          break;

          case 5:
          break;

          default:
            puts("Opção invalida")  ;
        }
        }while (opcao_imprecao != 5);     break;
    
    case 3:
      puts("Digite o numero a ser procurado: ");
      scanf("%d", &numero);
      if (existe(a, numero) == 1) {
        puts("Esse numero existe na arvore");
      }else {
        puts("Esse numero não existe na arvore");
      }  
    break;

    case 4:
      quantos = quantos_elementos(a);
      printf("A arvore contem %d elementos", quantos);
    break;

    case 5:
      imprime_folhas(a);
    break;

    case 6:
      balanceada = balanceamento(a);
      if (balanceada == 1) {
        puts("Esta balanceada");
      }else {
        puts("Não esta balanceada");
      }
    break;
    
    case 7:
      cheia = esta_cheia(a);
      if (cheia == 1) {
        puts("Está cheia");
      }else {
        puts("Não esta cheia");
      }
    break;

    case 8:
    puts("Digite o numero ");
    scanf("%d", &number);
    imprime_nivel_no(a, number, 0);
    break;              

    case 9:
    break;
  }

  }while (opcoes != 9);

}
