#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node*pLeft;
    int iData;
    struct node*pRight;
    struct node*pParent;
};

struct queue
{
    struct node *pTree;
    struct queue *pNext;
};

void Insert_AVL(struct node**ppRoot,int iNo);
void Balance_Factor(struct node**ppRoot,struct node*pInsertedNode,int iPosition);
int Height(struct node*pRoot);
void LeftRotation(struct node**ppRoot,struct node*pPivotNode);
void RightRotation(struct node **ppRoot, struct node *pPivotNode);
void LeftRightRotation(struct node **ppRoot, struct node *pPivotNode);
void RightLeftRotation(struct node **ppRoot, struct node *pPivotNode);
void Level_Order_Traversal(struct node *pRoot);
void Enqueue(struct queue **ppHead, struct node *pRoot);
struct node *Dequeue(struct queue **ppHead);

int main(void)
{
    struct node*pRoot = NULL;
    int iNo;
    int iChoice;

    while (1)
    {
        printf("Enter Data in AVL tree that you want:\n");
        scanf("%d",&iNo);
        Insert_AVL(&pRoot,iNo);
        printf("Do you want to continue then press 1 Either press 0:\n");
        scanf("%d",&iChoice);
        if(iChoice==0)
        {
            break;
        }
    }
    
    printf("The Level order Traversal is\n");
    Level_Order_Traversal(pRoot);

}

void Insert_AVL(struct node**ppRoot,int iNo)
{
    struct node*pPtr = NULL;
    struct node*pNewnode = NULL;
    struct node*pParent  = NULL;
    int iCount = 0;

    pPtr = *ppRoot;

    while (pPtr!=NULL)
    {
        pParent = pPtr;
        if(pPtr->iData > iNo)
        {
            pPtr = pPtr->pLeft;
            iCount = 1;
        }

        else if(pPtr->iData < iNo)
        {
            pPtr =  pPtr->pRight;
            iCount = 2;
        }

        else
        {
            return;
        }
    }

    pNewnode = (struct node*)malloc(sizeof(struct node));
    pNewnode->iData = iNo;
    pNewnode->pParent = pNewnode->pLeft = pNewnode->pRight = NULL;

    if(*ppRoot==NULL)
    {
        *ppRoot = pNewnode;
        return;
    }

    pNewnode->pParent = pParent;

    if(iCount==1)
    {
      pParent->pLeft = pNewnode;
    }

    else
    {
      pParent->pRight = pNewnode;
    }
    
    Balance_Factor(ppRoot,pNewnode,iCount);

    // iCount == 1 [Left]
    // iCount == 2 [Right]
}

void Balance_Factor(struct node**ppRoot,struct node*pInsertedNode,int iPosition)
{

    while (pInsertedNode!=NULL)
    {
        if(Height(pInsertedNode->pLeft)-Height(pInsertedNode->pRight)==2 && iPosition==1)
        {
            //RR
            RightRotation(ppRoot,pInsertedNode);
        }

        else if(Height(pInsertedNode->pLeft)-Height(pInsertedNode->pRight)==-2 && iPosition==2)
        {
            //LL
            LeftRotation(ppRoot,pInsertedNode);
        }

        else if(Height(pInsertedNode->pLeft)-Height(pInsertedNode->pRight)==2 && iPosition==2)
        {
           //LR
           LeftRightRotation(ppRoot,pInsertedNode);
        }

        else if(Height(pInsertedNode->pLeft)-Height(pInsertedNode->pRight)==-2 && iPosition==1)
        {
            //RL
            RightLeftRotation(ppRoot,pInsertedNode);
        }

        pInsertedNode = pInsertedNode->pParent;
    }
    
}

int Height(struct node*pRoot)
{
    int iLeftHeight,iRightHeight;

    if(pRoot==NULL)
    {
        return 0;
    }

    iLeftHeight = Height(pRoot->pLeft);
    iRightHeight = Height(pRoot->pRight);

    if(iLeftHeight > iRightHeight)
    {
        return iLeftHeight+1;
    }

    return iRightHeight+1;
}

void LeftRotation(struct node**ppRoot,struct node*pPivotNode)
{
    struct node *pTemp1 = pPivotNode->pParent;
    struct node *pTemp2 = pPivotNode->pRight;
    struct node *pTemp3 = pTemp2->pLeft;

    if (pTemp1 != NULL)
    {
        if (pTemp1->pRight == pPivotNode)
        {
            pTemp1->pRight = pTemp2;
        }
        else
        {
            pTemp1->pLeft = pTemp2;
        }
    }
    else
    {
        *ppRoot = pTemp2;
    }

    pTemp2->pParent = pTemp1;
    pPivotNode->pRight = pTemp3;

    if (pTemp3 != NULL)
    {
        pTemp3->pParent = pPivotNode;
    }
    pTemp2->pLeft = pPivotNode;
    pPivotNode->pParent = pTemp2;
}

void RightRotation(struct node **ppRoot, struct node *pPivotNode)
{
    struct node *pTemp1 = pPivotNode->pParent;
    struct node *pTemp2 = pPivotNode->pLeft;
    struct node *pTemp3 = pTemp2->pRight;

    if (pTemp1 != NULL)
    {
        if (pTemp1->pRight == pPivotNode)
        {
            pTemp1->pRight = pTemp2;
        }
        else
        {
            pTemp1->pLeft = pTemp2;
        }
    }
    else
    {
        *ppRoot = pTemp2;
    }

    pTemp2->pParent = pTemp1;
    pPivotNode->pLeft = pTemp3;

    if (pTemp3 != NULL)
    {
        pTemp3->pParent = pPivotNode;
    }
    pTemp2->pRight = pPivotNode;
    pPivotNode->pParent = pTemp2;
}

void LeftRightRotation(struct node **ppRoot, struct node *pPivotNode)
{
    LeftRotation(ppRoot, pPivotNode->pLeft);
    RightRotation(ppRoot, pPivotNode);
}

void RightLeftRotation(struct node **ppRoot, struct node *pPivotNode)
{
    RightRotation(ppRoot, pPivotNode->pRight);
    LeftRotation(ppRoot, pPivotNode);
}

void Level_Order_Traversal(struct node *pRoot)
{
    struct queue *pQueue = NULL;
    struct node *pPtr = NULL;

    Enqueue(&pQueue, pRoot);

    while ((pPtr = Dequeue(&pQueue)) != NULL)
    {
        printf("%d\t", pPtr->iData);

        if (pPtr->pLeft != NULL)
        {
            Enqueue(&pQueue, pPtr->pLeft);
        }

        if (pPtr->pRight != NULL)
        {
            Enqueue(&pQueue, pPtr->pRight);
        }
    }
}

void Enqueue(struct queue **ppHead, struct node *pRoot)
{
    struct queue *pNewnode = NULL;
    struct queue *pTemp = NULL;

    pNewnode = (struct queue *)malloc(sizeof(struct queue));

    if (NULL == pNewnode)
    {
        printf("The Memory Allocation Failed:\n");
        return;
    }

    pNewnode->pTree = pRoot;
    pNewnode->pNext = NULL;

    if (*ppHead == NULL)
    {
        *ppHead = pNewnode;
        return;
    }

    pTemp = *ppHead;
    while (pTemp->pNext != NULL)
    {
        pTemp = pTemp->pNext;
    }

    pTemp->pNext = pNewnode;
}

struct node *Dequeue(struct queue **ppHead)
{
    struct queue *pTemp = NULL;
    struct node *pValue = NULL;

    if (*ppHead == NULL)
    {
        return NULL;
    }

    pTemp = *ppHead;

    pValue = pTemp->pTree;
    *ppHead = pTemp->pNext;
    pTemp->pNext = NULL;
    free(pTemp);
    pTemp = NULL;
    return pValue;
}