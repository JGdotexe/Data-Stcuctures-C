#include <math.h>
#include <stdio.h>
int totalElementos = 0;

int indiceFilhoEsq(int x){
    int indice = (2*x)+1;
    if (x >= totalElementos || indice >=totalElementos) {
      return -1;
    }else {
      return indice;
    }
  }

int indiceFilhoDir(int x){
    int indice = (2*x)+2;
    if (x >= totalElementos || indice >= totalElementos) {
      return -1;
    }else {
      return indice;
    }
  }

int indicePai(int x){
    int indice = (int) floor((x-1)/2);
    if (x <= 0 || x>= totalElementos) { 
      return -1;
    }else {
      return indice;
    } 
  }

void ajustarSubindo(int* heap, int pos){
    if (pos != -1) {
      int pai = indicePai(pos);
      if (pai != -1) {
        if (heap[pos] > heap[pai]) {
          int aux = heap[pos];
          heap[pos] = heap[pai];
          heap[pai] = aux;
          ajustarSubindo(heap, pai);
        }
      } 
    } 
  }

void inserir(int* heap, int x){
    heap[totalElementos] = x; 
    totalElementos++;
    
    ajustarSubindo(heap, totalElementos-1);
  }

void ajustarDescendo(int* heap, int pos){
    if (pos != -1 && indiceFilhoEsq(pos) != -1) {
      //Descobrindo o maior filho
      int indiceMaiorFilho = indiceFilhoEsq(pos);
      if (indiceFilhoDir(pos) != -1 && heap[indiceFilhoDir(pos)] > heap[indiceMaiorFilho]) {
        indiceMaiorFilho = indiceFilhoDir(pos);
      }   
        //Verificando se existe filho maior que o nó atual
      if (heap[indiceMaiorFilho] > heap[pos]) {
        int aux = heap[pos];
        heap[pos] = heap[indiceMaiorFilho];
        heap[indiceMaiorFilho] = aux;
        ajustarDescendo(heap, indiceMaiorFilho);
      }
    }
  }

int remover(int* heap){
    if (totalElementos == 0) {
      return -1;
    }else {
      int retorno = heap[0];
      heap[0] = heap[totalElementos-1];
      totalElementos--;
      ajustarDescendo(heap,0);
      return retorno;
    }
  }

void imprimir(int heap[]){
    for (int i = 0; i <= 50;i++) {
      printf("[ %d ] ", heap[i]); 
    }
  }

int main(){ 
    int heap[50] = {0}; 
    int opcoes;
    int insercao;
    do {
      puts("1.Inserir um elemento x na heap");
      puts("2.Remover um elemento");
      puts("3.Imprimir a heap");
      puts("4.Sair");
      puts("Escolha uma opcao: "); 
      scanf("%d", &opcoes);
      switch (opcoes) {
        case 1:
          puts("Digite um numero para inserir");
          scanf("%d", &insercao);
          inserir(heap, insercao);
        break;
        
        case 2:
          int retorno = remover(heap);
          printf("%d", retorno);
        break;
        
        case 3:
         imprimir(heap); 
        break;

        case 4:
        break;  
      }
    }while (opcoes != 4);  
  }
