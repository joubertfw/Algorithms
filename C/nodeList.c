#include <stdio.h>
#include <stdlib.h>

struct node
{
    char data;
    struct node* next;
}typedef Node;
 
void init(Node* head)
{
    head = NULL;
}
 
Node* push(Node* head, char data)
{
    Node* tmp = (struct node*)malloc(sizeof(struct node));

    if(tmp == NULL)
    {
        exit(0);
    }

    tmp->data = data;
    tmp->next = head;
    head = tmp;

    return head;
}

Node* pop(Node* head, char *element)
{
    Node* tmp = head;
    *element = head->data;
    head = head->next;
    free(tmp);
    return head;
}

int empty(Node* head)
{
    return head == NULL ? 1 : 0;
}
 

void display(Node* head)
{
    Node* current;
    current = head;
    if(current!= NULL)
    {
        printf("Stack: ");
        do
        {
            printf("%c",current->data);
            current = current->next;
        }
        while (current!= NULL);
        printf("\n");
    }
    else
    {
        printf("The Stack is empty\n");
    }
 
}

int main()
{
    Node* train = NULL;
    Node* objective = NULL;
    int counter = 0;
    char element;    
  
    init(train);
    
    scanf("%d", &size);

    while(size != 0)
    {
        scanf(" %c", &element);

        train = push(train, element);        
        
        counter++;        
        scanf("%d", &size);
    }
 
    printf("\n---------------------------------------- \n");
    while(empty(train) == 0)
    {
        train = pop(train,&element);
        printf("Pop %c from stack\n",element);
        display(train);
    }
 
    return 0;
}
