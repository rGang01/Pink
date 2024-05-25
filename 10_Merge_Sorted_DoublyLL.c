#include  <stdio.h>
#include <stdlib.h>

struct node
{
    struct node*pPrev;
    int iData;
    struct node*pNext;
};

void InsertLast(struct node**ppHead,int iNo);
void Display(struct node*pHead);
void Merge_LL(struct node*pHead1,struct node*pHead2,struct node**ppHead3);

int main(void)
{
   struct node*pFirst = NULL;
   struct node*pSecond = NULL;
   struct node*pThird = NULL;

   InsertLast(&pFirst,1);
   InsertLast(&pFirst,3);
   InsertLast(&pFirst,5);
   Display(pFirst);
   InsertLast(&pSecond,2);
   InsertLast(&pSecond,4);
   InsertLast(&pSecond,6);
   Display(pSecond);


   Merge_LL(pFirst,pSecond,&pThird);
   Display(pThird);
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
    
    pNewnode->pNext = NULL;
    pNewnode->iData = iNo;

    if(NULL==*ppHead)
    {
      *ppHead = pNewnode;
      pNewnode->pPrev = NULL;
      return;
    }
    
    pTemp = *ppHead;

    while (pTemp->pNext!=NULL)
    {
        pTemp = pTemp->pNext;
    }

    pTemp->pNext = pNewnode;
    pNewnode->pPrev = pTemp;
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
    printf("\n");
}

void Merge_LL(struct node*pHead1,struct node*pHead2,struct node**ppHead3)
{
    struct node*pTemp1 = NULL;
    struct node*pTemp2 = NULL;

    pTemp1 = pHead1;
    pTemp2 = pHead2;

    while (pTemp1!=NULL && pTemp2!=NULL)
    {
        if(pTemp1->iData > pTemp2->iData)
        {
            InsertLast(ppHead3,pTemp2->iData);
            pTemp2 = pTemp2->pNext;
        }

        else if(pTemp1->iData < pTemp2->iData)
        {
            InsertLast(ppHead3,pTemp1->iData);
            pTemp1 = pTemp1->pNext;
        }

        else
        {
            InsertLast(ppHead3,pTemp1->iData);
            InsertLast(ppHead3,pTemp2->iData);
            pTemp1 = pTemp1->pNext;
            pTemp2 = pTemp2->pNext;
        }
    }

    while (pTemp1!=NULL)
    {
        InsertLast(ppHead3,pTemp1->iData);
        pTemp1 = pTemp1->pNext;
    }

    while (pTemp2!=NULL)
    {
      InsertLast(ppHead3,pTemp2->iData);
      pTemp2 = pTemp2->pNext;  
    }
}