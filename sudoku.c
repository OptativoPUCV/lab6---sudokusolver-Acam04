#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
   int i, j, dato;

   for (i = 0; i < 9; i++) {
      int row[10] = {0};
      for (j = 0; j < 9; j++) {
         dato = n->sudo[i][j];
         if (dato != 0) {
            if (row[dato] == 1) {
               return 0; 
            }
            row[dato] = 1;
         }
      }
   }

   for (j = 0; j < 9; j++) {
      int col[10] = {0};
      for (i = 0; i < 9; i++) {
         dato = n->sudo[i][j];
         if (dato != 0) {
            if (col[dato] == 1) {
               return 0;
            }
            col[dato] = 1;
         }
      }
   }

   for (int k = 0; k < 9; k++) {
      int sub[10] = {0};
      for (int p = 0; p < 9; p++) {
         int row = 3 * (k / 3) + (p / 3);
         int col = 3 * (k % 3) + (p % 3);
         dato = n->sudo[row][col];
         if (dato != 0) {
            if (sub[dato] == 1) {
               return 0; 
            }
            sub[dato] = 1;
         }
      }
   }

   return 1;
}
List* get_adj_nodes(Node* n){
   List* lista=createList();

   int row = -1, col = -1;

   for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
         if (n->sudo[i][j] == 0) {
            row = i;
            col = j;
            break;
            }
      }
      if (row != -1) break;
    }

    if (row == -1) return lista;

   for (int dato = 1; dato <= 9; dato++) {
      Node* newNode = copy(n);
      newNode->sudo[row][col] = dato;
      if (is_valid(newNode)) {
         pushBack(lista, newNode);
      } else {
         free(newNode);
      }
   }
   return lista;
}


int is_final(Node* n){
   for (int i = 0; i < 9; i++){
      for (int j = 0; j < 9; j++){
         if (n->sudo[i][j] == 0)
            return 0;
      }
   }
   return 1;
}

Node* DFS(Node* initial, int* cont){
   List* stack = createList(); 
   pushFront(stack, initial); 

   while (!is_empty(stack)) { 
      (*cont)++; 
      Node* current = front(stack); 
      popFront(stack); 
      if (is_final(current)) { 
         clean(stack); 
         return current; 
      }

      List* adj_nodes = get_adj_nodes(current); 
      Node* adj_node = front(adj_nodes); 

      while (adj_node != NULL) { 
         pushFront(stack, adj_node); 
         adj_node = next(adj_nodes); 
      }

      clean(adj_nodes); 
      free(current); 
   }
   return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/