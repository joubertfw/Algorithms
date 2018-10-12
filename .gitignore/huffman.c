#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define COUNT 16

struct Leaf
{
    char *c;
    int code;
    int frequency;

    struct Leaf *left;
    struct Leaf *right;

} typedef Leaf;

struct Node
{
    struct Node *nextNode;
    struct Leaf *root;

} typedef Node;

struct list
{
    Node *header;
    int size;
} typedef List;

Node *createNode(Leaf *value);

List *createList();

Leaf *createLeaf(char *c, int frequency);

void insertList(Leaf *lf, List *l);

void insertOrd(Leaf *lf, List *l);

void showList(List *l);

void freeList(List *l);

int isEmpty(List *l);

int *showCodes(Leaf *lf, int *codes);

void executeHuffman(List *l);

char isTerminalNode(Leaf *lf);

void setLeafCode(Leaf *lf, int code);

void print2DUtil(Leaf *lf, int space);

void print2D(Leaf *lf);

char *binaryPrint(unsigned int c);

int *fileFrequency(int *frequency, int *size, FILE *fileIn);

void frequencyToList(int *frequency, List *l);

void generateText(FILE *fileIn, int *codes, int *size);

int main()
{
    List *l;
    int *frequency, *codes, size = 0;
    char c = 0, filename[256];    
    FILE *fileIn;
    frequency = calloc(128, sizeof(int));
    codes = calloc(128, sizeof(int));
    l = createList();    

    scanf("%s", filename);
    printf("\n%s\n\n\n", filename);

    fileIn = fopen(filename, "r+");
    
    frequencyToList(fileFrequency(frequency, &size, fileIn), l);

    executeHuffman(l); 

    showList(l);
    printf("\n\n");

    setLeafCode(l->header->root, 1);
    showCodes(l->header->root, codes);
    printf("\n\n");

    printf("\nSize: %d\n", size);

    rewind(fileIn);
    generateText(fileIn, codes, &size);


    freeList(l);

    return 0;
}

Node *createNode(Leaf *value)
{
    Node *n;
    n = calloc(1, sizeof(Node));
    n->root = value;
    n->nextNode = NULL;
    return n;
}

Leaf *createLeaf(char *c, int frequency)
{
    Leaf *lf;    
    lf = calloc(1, sizeof(Leaf));

    lf->c = calloc(sizeof(c), 1);
    strcpy(lf->c,c);    
    
    lf->frequency = frequency;    
    lf->left = NULL;
    lf->right = NULL;

    return lf;
}

List *createList()
{
    List *l;
    l = calloc(1, sizeof(List));
    l->header = NULL;
    l->size = 0;
    return l;
}

void setLeafCode(Leaf *lf, int code)
{
    if (lf != NULL)
    {
        if (isTerminalNode(lf))        
            lf->code = code;            
        

        setLeafCode(lf->left, (code*2));
        setLeafCode(lf->right, (code*2)+1);

    }
}

void insertList(Leaf *lf, List *l)
{

    if (l->header == NULL)
    {
        l->header = createNode(lf);
        l->header->nextNode = NULL;
        return;
    }
    Node *temp = calloc(1, sizeof(Node));

    for (temp = l->header; temp->nextNode != NULL; temp = temp->nextNode);
    temp->nextNode = createNode(lf);
}

void insertOrd(Leaf *lf, List *l)
{

    if (l->header == NULL)
    {
        l->header = createNode(lf);
        l->header->nextNode = NULL;
        return;
    }

    Node *temp = calloc(1, sizeof(Node));
    Node *aux = calloc(1, sizeof(Node));    

    if (l->header->root->frequency > lf->frequency)
    {
        aux = l->header;
        l->header = createNode(lf);   
        l->header->nextNode = aux;                  
        return;
    }

    for (temp = l->header; temp->nextNode != NULL && temp->nextNode->root->frequency < lf->frequency; temp = temp->nextNode);

        aux = temp->nextNode;
        temp->nextNode = createNode(lf);   
        temp->nextNode->nextNode = aux;                  
}


void showList(List *l)
{
    Node *n;
    for (n = l->header; n != NULL; n = n->nextNode)
    {
        print2D(n->root);        
    }
}

void freeList (List *l)
{
    Node *temp = calloc(1, sizeof(Node));

    for (temp = l->header; temp->nextNode != NULL; temp = temp->nextNode);
        free(temp);

    free(l);
}

int isEmpty(List *l)
{
    return l->header == NULL;
}

int *showCodes(Leaf *lf, int *codes)
{
    if (lf != NULL)
    {
        showCodes(lf->left, codes);
        showCodes(lf->right, codes);

        if (isTerminalNode(lf))
        {
            printf("\n%s - ", lf->c);
            binaryPrint(lf->code);
            codes[lf->c[0]] = lf->code;
        }
    }
}

void executeHuffman(List *l)
{
    while (l->header->nextNode != NULL)
    {
        char *buffer = calloc(600, 1);

        Node *t1 = l->header;
        Node *t2 = l->header->nextNode;   

        strcpy(buffer, t1->root->c);
        strcat(buffer, "+");
        strcat(buffer, t2->root->c);        

        Leaf *lf = createLeaf(buffer, t1->root->frequency + t2->root->frequency);        
        free(buffer);

        lf->right = t1->root;
        lf->left = t2->root;
        l->header = l->header->nextNode->nextNode;

        insertOrd(lf, l);
    }
}



char isTerminalNode(Leaf *lf)
{
    return (lf->left == NULL && lf->right == NULL);
}

void print2DUtil(Leaf *lf, int space)
{    
    if (lf == NULL)
        return;
 
     space += COUNT;
 
 
    print2DUtil(lf->right, space);
 
 
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%s - %dx\t", lf->c, lf->frequency);
 
 
    print2DUtil(lf->left, space);
}
 

void print2D(Leaf *lf)
{
   print2DUtil(lf, 0);
}

char *binaryPrint(unsigned int c)
{
    unsigned int i = 128;    
    char firstOne = 0, *result;
    result = calloc(20, 1);

    while(i)
    {
        if (c&i)
        {
            firstOne = 1;
            printf("1");
            strcat(result, "1");
        }        
        else if (!(c&i) && firstOne)
        {
            printf("0");
            strcat(result, "0");
        }

        i = i/2;
    }
    return result;
}

int *fileFrequency(int *frequency, int *size, FILE *fileIn)
{
   char c = 0;

    do
    {
        c = fgetc(fileIn);
        frequency[c]++;
        *size += 8;
    } while (c != EOF);  

    *size -= 8;

    return frequency;
}

void frequencyToList(int *frequency, List *l)
{
    int i;
    char c[2];
    c[1] = '\0';

    for (i = 0; i < 128; i++)
    {
        if (frequency[i])
            printf("%c - %d\n", i, frequency[i]);
    }           

    for (i = 0; i < 128; i++)
    {        
        if (frequency[i] > 0)
        {
            c[0] = (char)i;
            insertOrd(createLeaf(c, frequency[i]), l);
        }
    }
}

void generateText(FILE *fileIn, int *codes, int *size)
{
    char c = 0, *text;    
    text = calloc(1000, 1);
    printf("\n\n\n");
    do
    {
        c = fgetc(fileIn);
        strcat(text, binaryPrint(codes[c]));                  
    } while (c != EOF);  
    printf("\n\n\n");

    printf("New Size: %d\n\n", (unsigned)strlen(text));
    printf("Aproximate Ratio: %d:1\n\n", (*size/(unsigned)strlen(text)));
}
