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

void print_stack(stack * s)
{
  int i;
  node * temp_node = s->top;
  printf("*** stack : ");
  for(i = 0; i < s->count; i++){
    printf("%c ", temp_node->data);
    temp_node = temp_node->prev;
  }
  printf("\n");
}


void append(char c, char * s)
{
  int len = strlen(s);
  char * temp_string;
  int i;

  temp_string = (char *) malloc (sizeof(char) * (len+1));
  *temp_string = c;
  
  for(i = 0; i < len; i++)
      *(temp_string + 1 + i) = *(s + i);
  *(temp_string + 1 + i) = '\0';
  strncpy(s, temp_string, len+1);
}

int lcs(stack x, stack y, int i, int j, int * c[])
{
  int max1, max2;
  node * temp_node;

  if(i == 0 || j == 0)
    {
      c[i][j] = 0;
      return c[i][j];
    }

  else if(c[i][j] == -1)
    {
      if(x.top->data == y.top->data)
      	{
	  pop(&x);
	  pop(&y);
      	  c[i][j] = lcs(x, y, i-1, j-1, c) + 1;
	  return c[i][j];
      	}
      else
      	{
      	  temp_node = pop(&x);
      	  max1 = lcs(x, y, i-1, j, c);
      	  push(&x, temp_node->data);
      	  pop(&y);
      	  max2 = lcs(x, y, i, j-1, c);
	  c[i][j] = (max1 > max2)? max1 : max2;
	  return c[i][j];
      	}
    }
  else
    return c[i][j];
}

char * backtrack(char * substring, stack x, stack y, int * c[], int i, int j, int len)
{
  char * temp_string;
  temp_string = (char *) malloc(sizeof(char) * len);
  if (i == 0 || j == 0)
    return substring;
  else if (x.top->data == y.top->data)
    {
      if (substring != NULL)
	{
	  strncpy(temp_string, substring, strlen(substring));
	  append(x.top->data, temp_string);
	}
      else{
	*temp_string = x.top->data;
	*(temp_string+1) = '\0';
      }
      
      pop(&x);
      pop(&y);
      return backtrack(temp_string, x, y, c, i-1, j-1, len);
    }
  else
    {
      if(substring == NULL) temp_string = NULL;
      else strcpy(temp_string, substring);
      if (c[i-1][j] > c[i][j-1])
	{
	  pop(&x);
	  return backtrack(temp_string, x, y, c, i-1, j, len);
	}
      else
	{
	  pop(&y);
	  return backtrack(temp_string, x, y, c, i, j-1, len);
	}
    }
}

void print_c(int * c[], int x, int y)
{
  int i, j;
  for (i = 0; i < x; i++)
    {
      for(j = 0; j < y; j++)
	{
	  if (c[i][j] == -1 || c[i][j] > 9) 	  printf("%d ", c[i][j]);
	  else  	  printf(" %d ", c[i][j]);
	}
      printf("\n");
    }
}


int main (int argc, char **argv)
{
  int ** c;
  stack x, y;
  int i, j;
  int len1, len2;


  if(argc != 3)
    {
      printf("+-----------------------------------------------+\n");
      printf("|  Please enter like this :D\t\t\t|\n");
      printf("|  ./[file_name] [string1] [string2]\t\t|\n");
      printf("|  Thank you!\t\t\t\t\t|\n");
      printf("+-----------------------------------------------+\n");
      return 0;
    }
  else
    {
      len1 = strlen(argv[1]);
      len2 = strlen(argv[2]);
    }

  c = (int **) malloc(sizeof(int *) * (len1+1));
  for (i = 0; i < len1+1; i++)
    c[i] = (int *) malloc(sizeof(int) * (len2+1));

  for (i = 0; i < len1+1; i++)
    for (j = 0; j < len2+1; j++)
      c[i][j] = -1;

  init_stack(&x);
  init_stack(&y);

  for (i = 0; i < len1; i++)
    push(&x, *(argv[1]+i));
  for (i = 0; i < len2; i++)
    push(&y, *(argv[2]+i));

  lcs(x, y, len1, len2, c);
  print_c(c, len1+1, len2+1);
  printf("%s\n", backtrack(NULL, x, y, c, len1, len2, (len1 > len2)? len1: len2));
  return 0;
}

