# Árvores Binárias de Busca

## Remoção

Para a remoção de elementos na ABB temos 3 casos a considerar.
 
1. Nó a ser removido é folha
2. Nó a ser removido possui 1 filho nulo 
3. Nó a ser removido não possui filhos nulos 

#### Caso 1 

O nó irá ser somente ser removido, ja que isso não implica desordenação da arvore.

#### Caso 2 

Juntasse o filho não nulo ao filho pai.

#### Caso 3 

Encontrase o maior elemento, y,da subarvore esquerda de x, substituir x por y, e remover o nó y da subarvore da esquerda de x.

## Função de Remoção 

```C
arvore* remover(arvore* a, int x){
    if (a != NULL) {                //enquanto a != NULL
      if (a->info == x){            //se o nó for encontrado
        if (a->left == NULL && a->right == NULL) { //verifica se os dois nós filhos são nulos 
          free(a);                                  //se sim apaga o nó
          return NULL;
        }else if (a->left == NULL) {                //se algum dos nós filhos não é nulo, é o esquerdo que é nulo?
          arvore* aux = a->right;                   //guarda o nó a direita num nó auxiliar
          free(a);
          return aux;                               //retorna aux 
        }else if (a->right == NULL) {
          arvore* aux = a->left;                    // mesma coisa pro outro lado
          free(a);
          return aux;
        }else {                                     //se os dois nós filhos forem nulos
          arvore* aux = a->left;                    //aux =  a->left 
          while (aux->right != NULL) {              //procura o nó mais a direita do nó a esquerda, que no caso é o nó antecessor de a
            aux = aux->right;                       //aux = nó antecessor de a
          }
          a->info = aux->info;                      //substitui a por aux
          a->left = remover(a->left, aux->info);    //remove o tal nó antecessor de a
          return a;
        }
      }else if (x < a->info){                       //percorre a arvore inteira 
        a->left = remover(a->left, x);
      }else {
        a->right = remover(a->right, x);
      }
    }
    return a;
  }
```

