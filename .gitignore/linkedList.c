#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    struct Node *nextNode;
} typedef Node;

struct list
{
    Node *header;
    int size;
} typedef List;

Node *createNode (int value);

List *createList ();

void InsertList (int value, List *l);

void showList (List *l);

void InsertFirst (int value, List *l);

void freeList (List *l);

int isEmpty (List *l);

int comprimento (List *l);

int maiores (List *l, int n);

void troca (List* l, char original, char novo);

List* ultimo_x (List* l, int x);

List* retira_n (List* l, int n);

List* separa (List* l, int n);

List* merge (List* l1, List* l2);

int main()
{
  List *l;
  l = createList();
  InsertList(10, l);
  InsertList(20, l);
  InsertList(15, l);  
  InsertList(30, l); 
  InsertFirst(40, l);  

  showList(l);

  freeList (l);
 
  return 0;
}

Node *createNode (int value)
{
    Node *n;
    n = calloc(1, sizeof(Node));
    n->value = value;
    n->nextNode = NULL;
    return n;
}

List *createList ()
{
    List *l;
    l = calloc(1, sizeof(List));
    l->header = NULL;
    l->size = 0;
    return l;
}

void InsertList (int value, List *l)
{    

    if (l->header == NULL)
    {
        l->header = createNode(value);
        l->header->nextNode = NULL;
        return;
    }   
    Node *temp = calloc(1, sizeof(Node));

    for (temp = l->header; temp->nextNode != NULL; temp = temp->nextNode);
        temp->nextNode = createNode(value);        
}

void InsertFirst (int value, List *l)
{  
    Node *firstNode = createNode(value);           

    firstNode->nextNode = l->header;
    l->header = firstNode;
}

void showList (List *l)
{
  Node *n;
  for (n = l->header; n != NULL; n = n->nextNode)
  {
      printf("%d\n", n->value);
  }
}

void freeList (List *l)
{
    Node *temp = calloc(1, sizeof(Node));

    for (temp = l->header; temp->nextNode != NULL; temp = temp->nextNode);
        free(temp);

    free(l);
}

int isEmpty (List *l)
{
    return l->header == NULL;
}

//q1
int comprimento (List *l)
{
    Node *temp = calloc(1, sizeof(Node));    
    int i = 0;

    for (temp = l->header; temp->nextNode != NULL; temp = temp->nextNode);
        i++;

    return i;
}

//q2
int maiores (List *l, int n)
{
    Node *temp = calloc(1, sizeof(Node));   
    int i = 0;
    for (temp = l->header; temp->nextNode != NULL; temp = temp->nextNode);
    {
        if (temp->nextNode->value > n)
            i++;    
    }

    return i;
}

//q3
void troca (List* l, char original, char novo)
{
    Node *temp = calloc(1, sizeof(Node)); 
    for (temp = l->header; temp->nextNode != NULL; temp = temp->nextNode);
    {
        if (temp->value == original)
            temp->value = novo;
    }
}

//q4
List* ultimo_x (List* l, int x)
{
    Node *temp = calloc(1, sizeof(Node)); 
    List *temp2 = createList ();

    for (temp = l->header; temp->nextNode != NULL; temp = temp->nextNode);
    {
        if (temp->value == x)
            temp2->header = temp;
    }
    return temp2;
}

//q5
List* concatena (List* l1, List* l2)
{
    Node *temp = calloc(1, sizeof(Node)); 
    
    for (temp = l1->header; temp->nextNode != NULL; temp = temp->nextNode);

    temp->nextNode = l2->header;

    List *l = createList();
    l->header = temp;

    return l;
}

//q6
List* retira_n (List* l, int n)
{
    Node *temp = calloc(1, sizeof(Node)); 
    
    for (temp = l->header; temp->nextNode != NULL; temp = temp->nextNode)
    {
        if (temp->nextNode->value == n)
        {
            temp = temp->nextNode->nextNode;
        }
    }

    List *l1 = createList();
    l1->header = temp;    

    return l1;
}

//q7
List* separa (List* l, int n)
{
    Node *temp = calloc(1, sizeof(Node));   
    List *l1 = createList();  
    List *aux = createList();  

    for (aux->header = l->header, temp = l->header; aux->header != NULL; aux->header = aux->header->nextNode, temp = temp->nextNode)
    {
        if (aux->header->nextNode->value == n)
        {
            aux->header->nextNode = NULL;                                    
        }        
    }
    
    l1->header = temp->nextNode;

    return l1;
}

//q8
List* merge (List* l1, List* l2)
{
    Node *temp = calloc(1, sizeof(Node));   
    Node *temp2 = calloc(1, sizeof(Node));   

    Node *aux = calloc(1, sizeof(Node));   

    Node *merged = calloc(1, sizeof(Node));  
    List *result = createList();

    for (temp = l1->header, temp2 = l2->header, aux = result->header; temp->nextNode != NULL || temp2->nextNode != NULL; temp = temp->nextNode, temp2 = temp2->nextNode, aux = aux->nextNode)
    {
        merged = temp;
        merged->nextNode = temp2; 
        aux = merged;               
    }

    return result;
}
