#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node*pLeft;
    int lBit;
    int iData;
    int rBit;
    struct node*pRight;
};

void InOrder(struct node *pHead);
void PreOrder(struct node *pHead);
void Insert_TBT(struct node**ppHead,int iNo);

void main()
{
    struct node*pHead = NULL;

    pHead = (struct node*)malloc(sizeof(struct node));

    pHead->lBit = 0;
    pHead->rBit = 1;
    pHead->pLeft = pHead->pRight = pHead;

    if(NULL==pHead)
    {
        printf("The Memory Allocation Failed:\n");
        return;
    }

    Insert_TBT(&pHead,15);
    Insert_TBT(&pHead,6);
    Insert_TBT(&pHead,14);
    Insert_TBT(&pHead,17);
    Insert_TBT(&pHead,20);
    Insert_TBT(&pHead,1);

    InOrder(pHead);
}

void Insert_TBT(struct node**ppHead,int iNo)
{
    struct node*pNewnode = NULL;
    struct node*pTemp = NULL;
    int iCount = 0;

    pNewnode = (struct node*)malloc(sizeof(struct node));

    pNewnode->lBit = pNewnode->rBit = 0;
    pNewnode->iData = iNo;

    if(pNewnode==NULL)
    {
        printf("The Memory Allocation Failed:\n");
        return;
    }

    if ((*ppHead)->lBit == 0)
    {
        pNewnode->pLeft = pNewnode->pRight = *ppHead;
        (*ppHead)->pLeft = pNewnode;
        (*ppHead)->lBit = 1;
        return;
    }
    pTemp = (*ppHead)->pLeft;

    while(1)
    {
        if(pTemp->iData > iNo && pTemp->lBit==1)
        {
            pTemp = pTemp->pLeft;
            iCount = 1;
        }

        else if(pTemp->iData < iNo && pTemp->rBit==1)
        {
            pTemp = pTemp->pRight;
            iCount = 2;
        }

        else
        {
           break;
        }
    }

    if(iCount==1)
    {
        pTemp->lBit = 1;
        pNewnode->pLeft = pTemp->pLeft;
        pTemp->pLeft = pNewnode;
        pNewnode->pRight = pTemp;
        
    }

    else // right
    {
        pTemp->rBit = 1;
        pNewnode->pRight = pTemp->pRight;
        pTemp->pRight = pNewnode;
        pNewnode->pLeft = pTemp;
    }
}

void InOrder(struct node *pHead)
{
    int iCount;
    struct node *pTemp = NULL;

    pTemp = pHead->pLeft;

    if (pTemp->lBit == 0)
    {
        printf("%d\t", pTemp->iData);
    }

    while (1)
    {

        if (iCount == 2)
        {
            break;
        }

        else if (pTemp->lBit == 1)
        {
            while (pTemp->lBit == 1)
            {
                pTemp = pTemp->pLeft;
            }
            printf("%d\t", pTemp->iData);
        }

        else if (pTemp->rBit == 0)
        {

            iCount = 0;
            while (pTemp->rBit == 0)
            {
                pTemp = pTemp->pRight;
                if (pTemp == pHead)
                {
                    iCount = 2;
                    break;
                }
                if (pTemp->rBit == 1)
                {
                    iCount = 1;
                }
                printf("%d\t", pTemp->iData);
            }
            pTemp = pTemp->pRight;
            if (iCount == 1 && pTemp->lBit == 0)
            {
                printf("%d\t", pTemp->iData);
            }
        }

        else if (pTemp->rBit == 1)
        {
            pTemp = pTemp->pRight;
            if (pTemp->lBit == 0)
            {
                printf("%d\t", pTemp->iData);
            }
        }
    }
}

void PreOrder(struct node *pHead)
{
    struct node *pTemp = NULL;

    pTemp = pHead->pLeft;

    while (pTemp != pHead)
    {
        printf("%d\t", pTemp->iData);

        if (pTemp->lBit == 1)
        {
            pTemp = pTemp->pLeft;
        }

        else if (pTemp->rBit == 0)
        {
            while (pTemp->rBit == 0)
            {
                pTemp = pTemp->pRight;
            }
            pTemp = pTemp->pRight;
        }

        else if (pTemp->rBit == 1)
        {
            pTemp = pTemp->pRight;
        }
    }
}
