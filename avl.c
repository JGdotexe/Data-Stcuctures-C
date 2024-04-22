#include <stdio.h>  
#include <stdlib.h>
#include <time.h>

typedef struct avl{
    int info;
    int FB;
    struct avl* esq;
    struct avl* dir;
  }AVL;

void imprime_pre_ordem(AVL* a){
    if (a == NULL) {
      return;
    }

    printf("%d\n", a->info);
    imprime_pre_ordem(a->esq);
    imprime_pre_ordem(a->dir);
  }

void imprime_em_ordem(AVL *a){
    if (a == NULL) {
      return; 
    }

    imprime_em_ordem(a->esq);
    printf("%d\n", a->info);
    imprime_em_ordem(a->dir);
  }

void imprime_pos_ordem(AVL *a){
    if (a == NULL) {
      return; 
    }

    imprime_pos_ordem(a->esq);
    imprime_pos_ordem(a->dir);  
    printf("%d\n", a->info);
  }

void imprimefolha_menor(AVL* a, int x){
    if (a == NULL) return;
    
    if (a->info < x) {
      
      if (a->esq == NULL && a->dir== NULL) {
        printf("\n %d ", a->info);
      }

      imprimefolha_menor(a->esq, x);
      imprimefolha_menor(a->dir,x);
    }else {
      imprimefolha_menor(a->esq, x);
    }
  }

AVL* lerarvore(FILE * arq){
    char c;
    int num;

    fscanf(arq, "%c", &c);
    fscanf(arq, "%d", &num);

    if (num == -1) {
      fscanf(arq,"%c",&c);
      return NULL;
    }

    AVL* a = (AVL*)malloc(sizeof(AVL));
    a->info = num;
    a->esq= lerarvore(arq);
    a->dir= lerarvore(arq);
    fscanf(arq, "%c", &c);
    return a;
  }

int altura(AVL* a){
    if (a == NULL) {
      return 0;
    }
    
    int hl = altura(a->esq);
    int hr = altura(a->dir);
    if (hl > hr) {
      return hl+1;
    }else {
      return hr+1;
    }
  }

void imprime_nivel(AVL* a, int nivel_atual, int nivel_desejado) {
    if (a == NULL) return;

    if (nivel_atual == nivel_desejado) {
      printf("%d ", a->info);
    } else {
      imprime_nivel(a->esq, nivel_atual + 1, nivel_desejado);
      imprime_nivel(a->dir, nivel_atual + 1, nivel_desejado);
    }
  }

void imprime_em_largura(AVL* a){
    if (a == NULL) return;

    int h = altura(a);
    for (int i = 0; i < h; i++) {
      printf("Nivel %d: ", i);
      imprime_nivel(a, 0, i);
      printf("\n");
    }
  }

void imprime_nivel_no(AVL* a, int data, int nivel){
    if (a ==  NULL) return;
    
    if (a->info == data) printf("\n nivel %d\n", nivel);
    
    if (data < a->info) {
      imprime_nivel_no(a->esq, data, nivel+1); 
    }else {
      imprime_nivel_no(a->dir, data, nivel+1);
    }
  }

void ajustarFB(AVL* a) {
    if (a == NULL) return;
    
    int he = altura(a->esq);
    int hd = altura(a->dir);
    a->FB = hd-he;
    ajustarFB(a->esq);
    ajustarFB(a->dir);
  }

AVL* lerAVL(FILE* arq) {
    AVL* a = lerarvore(arq);
    ajustarFB(a);
    return a;
  }

int existe(AVL* a, int x) {
    if (a == NULL) {
      return 0; 
    }else if (x == a->info) {
      return 1;
    }else if (x < a->info) {
      return existe(a->esq, x);
    }else {
      return existe(a->dir, x);
    }
  }

AVL *RotacaoEsqSimples (AVL *r) {
//Os nós a e b serão aqueles com FB modificados.
    AVL *a = r;
    AVL *b=a->dir;
    a->dir = b->esq;
    b->esq = a;
    if (b->FB == 1) {
      a->FB = 0;
      b->FB = 0;
    }else {
      a->FB = 1;
      b->FB = -1;
    }
    r = b;
    return r;
  }

AVL *RotacaoEsqDupla(AVL *r) {
//Os nós a, b, c serão aqueles com FBs modificados
    AVL *a = r;
    AVL *c = a->dir;
    AVL *b = c->esq; //O nó b será a nova raiz
    c->esq = b->dir;
    a->dir = b->esq;
    b->esq = a;
    b->dir = c;
    //Setando os valores dos FBs de acordo
    //com FB da nova raiz.
    switch(b->FB) {
      case -1:
        a->FB = 0;
        c->FB = 1;
      break;
      case 0:
        a->FB = 0;
        c->FB = 0;
      break;
      case +1:
        a->FB = -1;
        c->FB = 0;
      break;
    }
    b->FB = 0;
    r = b;
    return r;
  }

//Rotação a esquerda geral
AVL *RotacaoEsq (AVL *r) {
    if (r->dir->FB == -1){
      r = RotacaoEsqDupla(r);
    }else{
      r = RotacaoEsqSimples(r);
    }
    return r;
  }

//Rotação a direita simples
AVL *RotacaoDirSimples (AVL *r) {
    //Os nós a e b serão aqueles com FB modificados.
    AVL *a = r->esq;
    AVL *b = r;
    b->esq = a->dir;
    a->dir = b;
    if (a->FB == -1) {
      a->FB = 0;
      b->FB = 0;
    }
    else{
      a->FB = 1;
      b->FB = -1;
    }
    r = a;
    return r;
  }

AVL *RotacaoDirDupla(AVL *r) {
    //Os nós a, b, c serão aqueles com FBs modificados
    AVL *c = r;
    AVL *a = c->esq;
    AVL *b = a->dir;
    c->esq = b->dir;
    a->dir = b->esq;
    b->esq = a;
    b->dir = c;
    //Setando os valores dos FBs de acordo
    //com FB da nova raiz.
    switch(b->FB) {
      case -1:
        a->FB = 0;
        c->FB = 1;
      break;
      case 0:
        a->FB = 0;
        c->FB = 0;
      break;
      case +1:
        a->FB = -1;
        c->FB = 0;
      break;
    }
    b->FB = 0;
    r = b;
    return r;
  }


//Rotação a direita geral
AVL *RotacaoDir (AVL *r) {
    if (r->esq->FB == 1)
      r = RotacaoDirDupla(r); 
    else
      r = RotacaoDirSimples(r);
    
    return r;
  }


AVL *Inserir(AVL *r, int x, int *hMudou) {
    if (r == NULL) {
      r = (AVL*) malloc (sizeof(AVL));
      r->info = x;
      r->esq = NULL;
      r->dir = NULL;
      r->FB = 0;
      *hMudou = 1;
    }else {
      if (x <= r->info) {
        r->esq = Inserir (r->esq,x,hMudou);
        if (*hMudou == 1) {
          switch (r->FB) {
            case -1:
              r = RotacaoDir(r);
              *hMudou = 0;
            break;
            case 0:
              r->FB = -1;
              *hMudou = 1;
            break;
              case +1:
              r->FB = 0;
              *hMudou = 0;
            break;
          }
        }
      }else{
        r->dir = Inserir (r->dir,x,hMudou);
        if (*hMudou == 1) {
          switch (r->FB) {
            case -1:
              r->FB = 0;
              *hMudou = 0;
            break;
            case 0:
              r->FB = +1;
              *hMudou = 1;
            break;
            case +1:
              r = RotacaoEsq (r);
              *hMudou = 0;
            break;
          }
        }
      }
    }
    return r;
  }

AVL *Remover (AVL *r, int x, int *hMudou) {
    if (r != NULL) {
      if (r->info == x) {
        //Verificar se é folha
        if (r->esq == NULL && r->dir == NULL) {
          free (r);
          *hMudou = 1;
          return NULL;
        }
        //Verificar se um dos filhos é nulo
        else if (r->esq == NULL || r->dir == NULL) {
          AVL *aux;
          if (r->esq == NULL)
            aux = r->dir;
          else
            aux = r->esq;
          free(r);
          *hMudou = 1;
          return aux;
        }else{ //Nenhum filho nulo
          AVL *maiorEsq = r->esq;
          while (maiorEsq->dir != NULL)
            maiorEsq = maiorEsq->dir;
          
          r->info = maiorEsq->info;
          r->esq = Remover(r->esq,r->info,hMudou);
           
          if (*hMudou == 1) {
            switch(r->FB) {
              case -1:
                r->FB = 0;
                *hMudou = 1;
              break;
              case 0:
                r->FB = 1;
                *hMudou = 0;
              break;
              case +1:
              {
                int aux = r->dir->FB;
                r = RotacaoEsq(r);
                if (aux == 0)
                  *hMudou = 0;
                else
                  *hMudou = 1;
                break;
              }
            }
          }
        }
      }else if (x < r->info) {
        r->esq = Remover(r->esq, x, hMudou);
        if (*hMudou == 1){
          switch(r->FB) {
            case -1:
              r->FB = 0;
              *hMudou = 1;
            break;
            case 0:
              r->FB = 1;
              *hMudou = 0;
            break;
            case +1:
            {
              int aux = r->dir->FB;
              r = RotacaoEsq(r);
              if (aux == 0)
              *hMudou = 0;
              else
              *hMudou = 1;
            break;
            }
          }
        }
      }else {
        r->dir = Remover(r->dir, x, hMudou);
        if (*hMudou == 1) {
          switch(r->FB) {
            case +1:
              r->FB = 0;
              *hMudou = 1;
            break;
            case 0:
              r->FB = -1;
              *hMudou = 0;
            break;
            case -1:
            {
              int aux = r->esq->FB;
              r = RotacaoDir(r);
              if (aux == 0)
              *hMudou = 0;
              else
              *hMudou = 1;
            break;
            } 
          }
        }
      }
    }
    return r;
  }

AVL* destruir(AVL* a){
    if (a != NULL) {
      a->esq= destruir(a->esq);
      a->dir= destruir(a->dir);
      free(a);
    }
    return NULL;
  }

int main(){
  AVL* a; 
  int x_folhamenor, nivel, opcoes, numero, number, quantos, balanceada, remocao, insercao;
  int hMudou = 0;
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
      Inserir(a, 10, &hMudou);
    break;
    
    case 7:
      puts("Digite um nó para remover");
      scanf("%d", &remocao);
      Remover(a, remocao, &hMudou);
    break;

    case 8:
      destruir(a);
    break;
  }

  }while (opcoes != 8);

}
