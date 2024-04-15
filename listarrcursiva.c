#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
  int data;
  struct Node *next;
}Node;

Node* new_item(int c){
  Node* node = (Node*)malloc(sizeof(Node));
  node->data = c;
  node->next = NULL;
  return node;
}

Node* pushfront(Node* head,int c){
  Node* new_head = new_item(c);
  new_head->next = head;
  return new_head;
} 

void print_lista(Node *head){
  if (head == NULL) {
    return;
  }

  printf("%d ", head->data);
  
  if (head->next != NULL) {
    print_lista(head->next);
  }
}

int soma_elementos(Node *head){
  if (head == NULL) {
    return 0;
  }
  return head->data+soma_elementos(head->next); 
}

int howmany(Node *head, int querry)
{
  if (head == NULL) {
    return 0;
  }
  int contador;
  if (head->data == querry){
    return 1+howmany(head->next,querry);
  }
  return howmany(head->next,querry);
}

Node* remove_item(Node *head, int item){
  if (head == NULL) {
    return NULL;
  }
  
  if (head->data == item) {
    Node *result = head->next;
    free(head);
    return result;
  }
  head->next = remove_item(head->next,item);
  return head;
}

int main()
{
  Node* head = NULL;
  head = pushfront(head, 1);
  head = pushfront(head, 2);      
  head = pushfront(head, 2);  
  head = pushfront(head, 4);  
  head = pushfront(head, 6);  
  head = pushfront(head, 8);
  
  // print_lista(head);
  // int soma = soma_elementos(head);
  // printf("Soma: %d", soma);
  int result = howmany(head,2);
  printf("there's: %d",result);
}
