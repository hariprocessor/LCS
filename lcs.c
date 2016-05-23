#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _node
{
  char data;
  struct _node * next;
  struct _node * prev;
} node;

typedef struct _stack
{
  int count;
  node * top;
} stack;

typedef node * node_ptr;

node * pop(stack * s)
{
  node * temp_node = s->top;

  if (s->count == 0)
    return NULL;
  else if (s->count == 1)
    {
      s->top = NULL;
      s->count = 0;
      return temp_node;
    }
  else
    {
      s->top = s->top->prev;
      s->top->next = NULL;
      s->count--;
      return temp_node;
    }
}

void push(stack * s, char data)
{
  node * n;
  n = (node *) malloc(sizeof(node));
  memset(n, 0, sizeof(node));
  n->data = data;
  if (s->top == NULL)
    {
      n->prev = NULL;
      n->next = NULL;
      s->top = n;
      s->count++;
    }
  else
    {
      n->prev = s->top;
      n->next = NULL;
      s->top->next = n;
      s->top = n;
      s->count++;
    }
}

void init_stack(stack * s)
{
  s->count = 0;
  s->top = NULL;
}
int lcs(stack x, stack y, int i, int j, int* c[])
{
  int max1, max2;
  node * temp_node;
  if(c[i][j] == 0)
    {
      if(x.top->data == y.top->data)
	{
	  pop(&x);
	  pop(&y);
	  c[i][j] = lcs(x, y, i-1, j-1, c) +1;
	}
      else
	{
	  temp_node = pop(&x);
	  max1 = lcs(x, y, i-1, j, c);
	  push(&x, temp_node->data);
	  pop(&y);
	  max2 = lcs(x, y, i, j-1, c);
	}
    }
}

void print_c(int * c[], int x, int y)
{
  int i, j;
  //printf("%d\n", c[0][0]);
  /*
  for (i = 0; i < x; i++)
    {
      for(j = 0; j < y; j++)
	{
	  printf("%d ", c[i][j]);
	}
      printf("\n");
    }
  */
}

int main (int argc, char **argv)
{
  int ** c;
  stack x;
  stack y;
  int i, j;

  if(argc != 3)
    {
      printf("+---------------------------------------+\n");
      printf("|  Please enter like this :D\t\t|\n");
      printf("|  ./[file_name] [string1] [string2]\t|\n");
      printf("|  Thank you!\t\t\t\t|\n");
      printf("+---------------------------------------+\n");
      return 0;
    }
  c = (int **) malloc(sizeof(int *)*strlen(argv[1]));
  for (i = 0; i < strlen(argv[1]); i++)
    c[i] = (int *) malloc(sizeof(int)*strlen(argv[2]));

  init_stack(&x);
  init_stack(&y);


  //  s = (stack *) malloc(sizeof(stack));

  for (i = 0; i < strlen(argv[1]); i++)
    push(&x, *(argv[1]+i));
  for (i = 0; i < strlen(argv[2]); i++)
    push(&y, *(argv[2]+i));

  lcs(x, y, strlen(argv[1]), strlen(argv[2]), c);
  //print_c(c, strlen(argv[1]), strlen(argv[2]));
  return 0;
}

