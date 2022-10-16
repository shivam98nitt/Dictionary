#include <stdio.h>
#include <stdlib.h>

struct dict
{
  struct dict *left, *right;
  char word[10], meaning[20];
} *root = NULL;

typedef struct dict dictionary;

int check(char[], char[]);
void insert(dictionary *);
void Search();
void view(dictionary *);

void WriteToFile(dictionary *);
void printInorder(dictionary *);



int check(char a[], char b[])
{
  int i, j, c;
  for (i = 0, j = 0; a[i] != '\0' && b[j] != '\0'; i++, j++)
  {
    if (a[i] > b[j])
    {
      c = 1;
      break;
    }
    else if (b[j] > a[i])
    {
      c = -1;
      break;
    }
    else
      c = 0;
  }
  if (c == 1)
    return 1;
  else if (c == -1)
    return -1;
  else
    return 0;
}

void Search()
{
  int flag = 0;
  dictionary *ptr;
  ptr = root;
  char w[10];
  printf("\nEnter word");
  scanf("%s", w);
  while (ptr != NULL && flag == 0)
  {
    if (check(w, ptr->word) > 0)
      ptr = ptr->right;
    else if (check(w, ptr->word) < 0)
      ptr = ptr->left;
    else if (check(w, ptr->word) == 0)
    {
      flag = 1;
      printf("\n%s", ptr->meaning);
    }
  }
  if (flag == 0)
    printf("\nWord not found");
}

void insert(dictionary *temp)
{
  int flag = 0;
  dictionary *ptr, *par;
  ptr = root;

  if (root == NULL)
    root = temp;
  else
  {
    while (ptr != NULL)
    {
      if (check(temp->word, ptr->word) > 0)
      {
        par = ptr;
        ptr = ptr->right;
      }

      else if (check(temp->word, ptr->word) < 0)
      {
        par = ptr;
        ptr = ptr->left;
      }
      else if (check(temp->word, ptr->word) == 0)
      {
        flag = 1;
        printf("\nWord exists!!");
        break;
      }
    }
    if (flag == 0 && ptr == NULL)
    {

      if (check(par->word, temp->word) == 1)
        par->left = temp;
      else if (check(par->word, temp->word) == -1)
        par->right = temp;
    }
  }
}

void view(dictionary *ptr)
{
  if (root == NULL)
    printf("\nEmpty dictionary\n");

  else if (ptr != NULL)
  {
    view(ptr->left);

    printf("\n%s--->", ptr->word);
    printf("%s\n", ptr->meaning);

    view(ptr->right);
  }
}

int main(int argc, char const *argv[])
{
  int ch;
  dictionary *temp;
  while (ch != 4)
  {
    printf("\n1.Search\n2.Insert\n3.View\n4.Exit\nYour choice please..");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
      Search();
      break;
    case 2:
      temp = (dictionary *)malloc(sizeof(dictionary));
      temp->left = NULL;
      temp->right = NULL;
      printf("\nInsert word:\n");
      scanf("%s", temp->word);
      printf("\nInsert meaning:\n");
      scanf("%s", temp->meaning);
      insert(temp);
      //WriteListToFile(temp);
      break;
    case 3:
      view(root);
      break;
    case 4:
    {
      FILE *fp;
	    fp = fopen("dictionary.txt", "w");
      fclose(fp);
      fp=NULL;
      printInorder(root);
      //printPreorder(root);
      //printPostorder(root);
      exit(0);
    }
      
    }
  }
  return 0;
}

void WriteToFile(dictionary *temp) {
	FILE *fp;
	fp = fopen("dictionary.txt", "a");

  fprintf(fp,temp->word);
  fprintf(fp,"---->");
  fprintf(fp,temp->meaning);
  fprintf(fp,"\n");
	
	fclose(fp);
	fp = NULL;
	
}


void printInorder(dictionary *temp) 
{ 
     if (temp == NULL) 
          return; 
  
     /* first recur on left child */
     printInorder(temp->left); 
  
     /* then print the data of temp */
    // printf("%d ", temp->data);  
    WriteToFile(temp); 
  
     /* now recur on right child */
     printInorder(temp->right); 
}
