#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode()
{
   Node* n=(Node*) malloc(sizeof(Node));
   return n;
}

Node* copy(Node* n)
{
   Node* new=(Node*) malloc(sizeof(Node));
   *new = *n;
   return new;
}

Node* read_file (char* file_name)
{
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

void print_node(Node* n)
{
   int i,j;
   for(i = 0; i < 9; i++){
      for(j = 0; j < 9; j++)
         printf("%d ", n->sudo[i][j]);
      printf("\n");
   }
   printf("\n");
}

int is_valid(Node* n)
{
   /*List* l = createList();

   for (int k = 1; k <= 9; k++)
   {
      node* aux = _createNode(k);
      pushBack(l, aux);
   }
   
   int i, j;

   for (i = 0; i < 9; i++)
      for (j = 0; j < 9; j++)
      {
         if (n->sudo[i][j] != 0)
         {
            aux = front(l);
            
            while (aux != NULL)
            {
               if (aux->data == n->sudo[i][j])
                  return 0;
               aux = next(l);
            }
         }

         if (n->sudo[j][i] != 0)
         {
            aux = front(l);

            while (aux != NULL)
            {
               if (aux->data == n->sudo[j][i])
                  return 0;
               aux = next(l);
            }
         }
      }*/
   
   return 1;
}


List* get_adj_nodes(Node* n)
{
   List* list = createList();
   int i, j;

   for (i = 0; i < 9; i++)
      for (j = 0; j < 9; j++)
      {
         if (n->sudo[i][j] == 0)
         {
            Node* adj = copy(n);
            int valor;

            for (valor = 1; valor <= 9; valor++)
            {
               adj->sudo[i][j] = valor;
               
               pushBack(list, adj);
            }
         }
      }
   return list;
}


int is_final(Node* n)
{
   int i, j;

   for (i = 0; i < 9; i++)
      for (j = 0; j < 9; j++)
      {
         if (n->sudo[i][j] == 0)
            return 0;
      }
   return 1;
}

Node* DFS(Node* initial, int* cont)
{
   Stack* s = createStack();
   List* l = createList();
   push(s, initial);

   while (!is_empty(s))
   {
      *cont++;
      Node* n = top(s);
      
      pop(s);
      
      if (is_final(n))
         return n;
      
      l = get_adj_nodes(n);

      while (!is_empty(l))
      {
         push(s, popFront(l))
         
      }
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