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

int verificar(List* l)
{
   int* aux = first(l);

   for (int k = 1; k <= 9; k++)
   {
      int count = 0;
      aux = first(l);
      
      while (aux != NULL)
      {
         if (*aux == k)
            count++;

         if (count >= 2)
            return 0;

         aux = next(l);
      }
   }

   return 1;
}

int is_valid(Node* n)
{
   List* l = createList();
   int i, j;

   for (i = 0; i < 9; i++)
   {
      for (j = 0; j < 9; j++)
      {
         if (n->sudo[i][j] != 0)
            pushBack(l, &n->sudo[i][j]);
      }
      
      if (verificar(l) == 0)
      {
         clean(l);
         free(l);
         return 0;
      }
      clean(l);
   }

   for (i = 0; i < 9; i++)
   {
      for (j = 0; j < 9; j++)
      {
         if (n->sudo[j][i] != 0)
            pushBack(l, &n->sudo[i][j]);
      }
      
      if (verificar(l) == 0)
      {
         clean(l);
         free(l);
         return 0;
      }
      clean(l);
   }
   
   for (int k = 0; k < 9; k++)
   {
      for (int p = 0; p < 9; p++)
      {
         int i = 3*(k/3) + (p/3);
         int j = 3*(k%3) + (p%3);

         if (n->sudo[i][j] != 0)
            pushBack(l, &n->sudo[i][j]);
      }
      
      if (verificar(l) == 0)
      {
         clean(l);
         free(l);
         return 0;
      }
      clean(l);
   }
   clean(l);
   free(l);
   
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
            int valor;

            for (valor = 1; valor <= 9; valor++)
            {
               Node* adj = copy(n);
               adj->sudo[i][j] = valor;

               if (is_valid(adj))
                  pushBack(list, adj);
            }
            return list;
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
   push(s, initial);

   while (!is_empty(s))
   {
      (*cont)++;
      Node* n = top(s);
      pop(s);
      
      if (is_final(n))
         return n;
      
      List* l = get_adj_nodes(n);

      while (!is_empty(l))
      {
         push(s, front(l));
         popFront(l);
      }

      clean(l);
      free(l);
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