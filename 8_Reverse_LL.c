#include <stdio.h>
#include <stdlib.h>

struct node
{
    int iData;
    struct node*pNext;
};

void InsertLast(struct node**ppHead,int iNo);
void Display(struct node*pHead);
void Physical_Reverse(struct node**ppHead);

int main(void)
{  
    struct node*pFirst = NULL;

   InsertLast(&pFirst,10);
   InsertLast(&pFirst,20);
   InsertLast(&pFirst,30);
   InsertLast(&pFirst,40);
   InsertLast(&pFirst,50);

   Display(pFirst);
   Physical_Reverse(&pFirst);
   Display(pFirst);

}

void InsertLast(struct node**ppHead,int iNo)
{
    struct node*pNewnode = NULL;
    struct node*pTemp = NULL;

    pNewnode = (struct node*)malloc(sizeof(struct node));

    if(NULL==pNewnode)
    {
        printf("Memory Allocation Failed");
        return;
    }
    pNewnode->iData = iNo;
    pNewnode->pNext = NULL;

    if(NULL==*ppHead)
    {
       *ppHead = pNewnode;
       return;
    }
    
    pTemp = *ppHead;
    while (pTemp->pNext!=NULL)
    {
        pTemp = pTemp->pNext;
    }

    pTemp->pNext = pNewnode;
}

void Display(struct node*pHead)
{
    if(NULL==pHead)
    {
        printf("List is Empty");
        return;
    }

    while(pHead!=NULL)
    {
        printf("|%d|->",pHead->iData);
        pHead = pHead->pNext;
    }
}

void Physical_Reverse(struct node**ppHead)
{
    struct node*pNext = NULL;
    struct node*pPrev = NULL;
    struct node*pCurrent = *ppHead;
    
    while (pCurrent!=NULL)
    {
     pNext = pCurrent->pNext;
     pCurrent->pNext = pPrev;
     pPrev = pCurrent;
     pCurrent = pNext;
    }

    *ppHead = pPrev;
    
}
