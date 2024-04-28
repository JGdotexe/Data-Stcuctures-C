#include <stdio.h>
#include <stdlib.h>

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

void imprimefolha_menor(arvore* a, int x){
    if (a == NULL) return;
    
    if (a->info < x) {
      
      if (a->left == NULL && a->right == NULL) {
        printf("\n %d ", a->info);
      }

      imprimefolha_menor(a->left, x);
      imprimefolha_menor(a->right,x);
    }else {
      imprimefolha_menor(a->left, x);
    }
  }

int existe(arvore* a, int x){
    if (a == NULL) return 0;
    
    else if (a->info == x) return 1;
    
    if (x < a->info){
      return existe(a->left, x);
    } else {
      return existe(a->right, x);
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
    
    if (data < a->info) {
      imprime_nivel_no(a->left, data, nivel+1); 
    }else {
      imprime_nivel_no(a->right, data, nivel+1);
    }
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
    
    if (balanceamento(a->left) == 0 || balanceamento(a->right) == 0) {
      return 0;
    }else {
      int hl = altura(a->left);
      int hr  = altura(a->right);
      if (abs(hl-hr)>1) {
        return 0;
      }else {
        return 1;
      }
    }
  }

arvore* inserir(arvore* a, int x){
    if (a == NULL) {
      a = (arvore*)malloc(sizeof(arvore));
      a->info = x;
      a->left = NULL;
      a->right = NULL;
    }else if (x <= a->info) {
      a->left = inserir(a->left, x);
    }else {
      a->right = inserir(a->right, x);
    }
    return a;
  }

arvore* remover(arvore* a, int x){
    if (a != NULL) {
      if (a->info == x){
        if (a->left == NULL && a->right == NULL) {
          free(a);
          return NULL;
        }else if (a->left == NULL) {
          arvore* aux = a->right;
          free(a);
          return aux; 
        }else if (a->right == NULL) {
          arvore* aux = a->left;
          free(a);
          return aux;
        }else {
          arvore* aux = a->left;
          while (aux->right != NULL) {
            aux = aux->right;
          }
          a->info = aux->info;
          a->left = remover(a->left, aux->info);
          return a;
        }
      }else if (x < a->info){  
        a->left = remover(a->left, x);
      }else {
        a->right = remover(a->right, x);
      }
    }
    return a;
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

arvore* destruir(arvore* a){
    if (a != NULL) {
      a->left = destruir(a->left);
      a->right = destruir(a->right);
      free(a);
    }
    return NULL;
  }

int main(){
  arvore* a; 
  int x_folhamenor, nivel, opcoes, numero, number, quantos, balanceada, remocao, insercao; 
  FILE* arq;
  char nome_arquivo[30];
  int opcao_imprecao = 0;
  do {
  puts("\nAtividade JG");
  puts("1. Ler arvore:");
  puts("2. Imprimir");
  puts("3. Procurar elemento");
  puts("4. Imprimir nivel");
  puts("5. Imprimir nos folha menores que um valor X");
  puts("6. Inserir um elemento");
  puts("7. Remover um no da arvore");
  puts("8. Sair");

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
        }while (opcao_imprecao != 5);     
    break;
    
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
      puts("Digite o numero ");
      scanf("%d", &number);
      imprime_nivel_no(a, number, 0);
    break;              

    case 5:
      puts("Digite um número");
      scanf("%d", &x_folhamenor);
      imprimefolha_menor(a, x_folhamenor);
    break;

    case 6:
      puts("Digite um numero");
      scanf("%d", &insercao);
      inserir(a, insercao);
    break;
    
    case 7:
      puts("Digite um nó para remover");
      scanf("%d", &remocao);
      remover(a, remocao);
    break;

    case 8:
      destruir(a);
    break;
  }

  }while (opcoes != 8);

}
