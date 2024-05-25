#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node*pLeft;
    int iData;
    struct node*pRight;
};

struct Stack
{
    struct node *pTree;
    struct Stack *pNext;
};

struct Queue
{
   struct node*pTree;
   struct Queue*pNext;
};


void InsertBST(struct node**ppRoot,int iNo);
void InOrder_Recurssive(struct node *pRoot);
struct node* SearchBST(struct node*pRoot,int iNo);
int CountNodes(struct node*pRoot);
int Height(struct node*pRoot);
int LeafNodeCount(struct node*pRoot);
void Inorder_NonRecursive(struct node *pRoot);
void Push(struct Stack **ppHead, struct node *pData);
struct node* Pop(struct Stack**ppHead);
void PreOrder_NonReccursive(struct node*pRoot);
void PostOrder_NonRecuursive(struct node*pRoot);
void Level_Order_Traversal(struct node*pRoot);
void Enqueue(struct Queue**ppHead,struct node*pData);
struct node *Dequeue(struct Queue **ppHead);
void Mirror_BST(struct node*pRoot);
void NonLeafNodeCount_NonReccursive(struct node *ppRoot);
int Height_NonRecuursive(struct node*pRoot);
int CountNodes_Q(struct Queue*pQueue);
void BST_DeleteRecursive(struct node**ppRoot,int iKey);

int main(void)
{
  struct node*pRoot = NULL;
  struct node*pTemp = NULL;

  InsertBST(&pRoot,10);
  InsertBST(&pRoot,6);
  InsertBST(&pRoot,15);
  InsertBST(&pRoot,5);
  InsertBST(&pRoot,9);
  InsertBST(&pRoot,1);
  InsertBST(&pRoot,14);
  InsertBST(&pRoot,17);

  InOrder_Recurssive(pRoot);
  printf("\n");
  
  pTemp = SearchBST(pRoot,9);
  if(pTemp!=NULL)
  {
    printf("The Data Found\n");
  }

  printf("Total Nodes are %d\n",CountNodes(pRoot));
  printf("The Height is %d\n",Height(pRoot));
  printf("The Leaf node count %d\n",LeafNodeCount(pRoot));

  printf("The Postorder is:\n");
  PostOrder_NonRecuursive(pRoot);

  printf("The Level OrderTraversal is:\n");
  Level_Order_Traversal(pRoot);

  printf("\n");

//   Mirror_BST(pRoot);
//  Level_Order_Traversal(pRoot);

  NonLeafNodeCount_NonReccursive(pRoot);
  Height_NonRecuursive(pRoot);
  printf("\n");

  BST_DeleteRecursive(&pRoot,15);
  Level_Order_Traversal(pRoot);
}

void InsertBST(struct node**ppRoot,int iNo)
{
  struct node*pNewnode = NULL;
  struct node*pPtr = NULL;
  struct node*pParent = NULL;
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
    else
    {
      pPtr = pPtr->pRight;
      iCount = 2;
    }

  }

  pNewnode = (struct node*)malloc(sizeof(struct node));

  if(NULL == pNewnode)
  {
    printf("The Memory Allocation Failed\n");
    return;
  }

  pNewnode->iData = iNo;
  pNewnode->pLeft = pNewnode->pRight = NULL;

  if(NULL == *ppRoot)
  {
    *ppRoot = pNewnode;
    return;
  }

  if(iCount == 1)
  {
    pParent->pLeft = pNewnode;
    return;
  }
    pParent->pRight = pNewnode;
 
}

void InOrder_Recurssive(struct node *pRoot)
{
    if (pRoot != NULL)
    {
        InOrder_Recurssive(pRoot->pLeft);
        printf("%d\t", pRoot->iData);
        InOrder_Recurssive(pRoot->pRight);
    }
}

struct node* SearchBST(struct node*pRoot,int iNo)
{

    while (pRoot!=NULL)
    {
        if(pRoot->iData > iNo)
        {
            pRoot = pRoot->pLeft;
        }

        else if(pRoot->iData < iNo)
        {
            pRoot  = pRoot->pRight;
        }

        else
        {
            return pRoot;
        }
    }

    return NULL;
    
}

int CountNodes(struct node*pRoot)
{
    if(pRoot==NULL)
    {
        return 0;
    }

    return CountNodes(pRoot->pLeft)+CountNodes(pRoot->pRight)+1;
}

int Height(struct node*pRoot)
{
    if(pRoot==NULL)
    {
        return 0;
    }

    int iLeftHeight,iRightHeight;

    iLeftHeight = Height(pRoot->pLeft);
    iRightHeight = Height(pRoot->pRight);

    if(iLeftHeight > iRightHeight)
    {
       return iLeftHeight+1;
    }

    return iRightHeight+1;
}

int LeafNodeCount(struct node*pRoot)
{
    int static iCount = 0;

    if(NULL==pRoot)
    {
        return 0;
    }

    if(pRoot->pLeft==NULL && pRoot->pRight==NULL)
    {
        iCount++;
    }

    LeafNodeCount(pRoot->pLeft);
    LeafNodeCount(pRoot->pRight);
    return iCount;
}

void Inorder_NonRecursive(struct node *pRoot)
{
    struct Stack *pstack = NULL;

    while (pRoot != NULL)
    {
        Push(&pstack, pRoot);
        pRoot = pRoot->pLeft;
    }

    while (pstack != NULL)
    {

        pRoot = Pop(&pstack);

        if (NULL == pRoot)
        {
            printf("The Stack is empty\n");
            return;
        }

        printf("%d\t", pRoot->iData);
        pRoot = pRoot->pRight;

        while (pRoot != NULL)
        {
            Push(&pstack, pRoot);
            pRoot = pRoot->pLeft;
        }
    }
}

void Push(struct Stack **ppHead, struct node *pData)
{
    struct Stack *pNewnode = NULL;

    pNewnode = (struct Stack *)malloc(sizeof(struct Stack));

    if (NULL == pNewnode)
    {
        printf("The memory Allocation failed");
        return;
    }

    pNewnode->pTree = pData;

    if (*ppHead == NULL)
    {
        *ppHead = pNewnode;
        pNewnode->pNext = NULL;
        return;
    }

    pNewnode->pNext = *ppHead;
    *ppHead = pNewnode;
}

struct node* Pop(struct Stack**ppHead)
{
    struct Stack *pTemp = NULL;
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

void PreOrder_NonReccursive(struct node*pRoot)
{
    struct Stack*pStack = NULL;

    while (pRoot!=NULL)
    {
        printf("%d\t",pRoot->iData);
        Push(&pStack,pRoot);
        pRoot = pRoot->pLeft;
    }

    while (pStack!=NULL)
    {
        pRoot = Pop(&pStack);
        pRoot = pRoot->pRight;
        while (pRoot != NULL)
        {
            printf("%d\t", pRoot->iData);
            Push(&pStack, pRoot);
            pRoot = pRoot->pLeft;
        }
    }
       
}

void PostOrder_NonRecuursive(struct node*pRoot)
{
    struct Stack*pStack1 = NULL;
    struct Stack*pStack2 = NULL;
    struct node*pTemp = NULL;

    Push(&pStack1,pRoot);

    while (pStack1!=NULL)
    {
        pTemp = pStack1->pTree;
        Pop(&pStack1);
        Push(&pStack2,pTemp);

        if(pTemp->pLeft!=NULL)
        {
            Push(&pStack1,pTemp->pLeft);
        }        

        if(pTemp->pRight!=NULL)
        {
            Push(&pStack1,pTemp->pRight);
        }
    }

    while(pStack2!=NULL)
    {
        pTemp = Pop(&pStack2);
        printf("%d\t",pTemp->iData);
    }
}

void Level_Order_Traversal(struct node*pRoot)
{
    struct Queue*pQueue = NULL;
    struct node*pPtr = NULL;
    
    Enqueue(&pQueue,pRoot);

    while ((pPtr = Dequeue(&pQueue)) != NULL)
    {
        printf("%d\t",pPtr->iData);

        if(pPtr->pLeft!=NULL)
        {
            Enqueue(&pQueue,pPtr->pLeft);
        }

        if(pPtr->pRight!=NULL)
        {
            Enqueue(&pQueue,pPtr->pRight);
        }
    }
}

void Enqueue(struct Queue**ppHead,struct node*pData)
{
    struct Queue *pNewnode = NULL;
    struct Queue *pTemp = NULL;

    pNewnode = (struct Queue *)malloc(sizeof(struct Queue));

    if (NULL == pNewnode)
    {
        printf("The Memory Allocation Failed");
        return;
    }

    pNewnode->pTree = pData;
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

struct node *Dequeue(struct Queue **ppHead)
{
    struct Queue *pTemp = NULL;
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

void Mirror_BST(struct node*pRoot)
{
    struct Queue*pQueue = NULL;
    struct node*pTemp = NULL;
    struct node*pTemp1 = NULL;

    Enqueue(&pQueue,pRoot);

    while (pQueue!=NULL)
    {
        pTemp = Dequeue(&pQueue);

        pTemp1 = pTemp->pLeft;
        pTemp->pLeft = pTemp->pRight;
        pTemp->pRight = pTemp1;

        if(pTemp->pLeft!=NULL)
        {
           Enqueue(&pQueue,pTemp->pLeft);
        }

        if(pTemp->pRight!=NULL)
        {
            Enqueue(&pQueue,pTemp->pRight);
        }
    }
    
}

void NonLeafNodeCount_NonReccursive(struct node *ppRoot)
{
    struct Stack *pStack = NULL;
    struct node *pTemp = NULL;
    int iCount = 0;

    Push(&pStack, ppRoot);

    while (pStack != NULL)
    {
        ppRoot = Pop(&pStack);

        if (ppRoot->pLeft != NULL || ppRoot->pRight != NULL)
        {
            iCount++;
        }

        if ((ppRoot)->pLeft != NULL)
        {
            Push(&pStack, (ppRoot)->pLeft);
        }

        if ((ppRoot)->pRight != NULL)
        {
            Push(&pStack, (ppRoot)->pRight);
        }
    }

    printf("The count is %d\n",iCount);
}

void NodeCount_NonReccursive(struct node *ppRoot)
{
    struct Stack *pStack = NULL;
    struct node *pTemp = NULL;
    int iCount = 1;

    Push(&pStack, ppRoot);

    while (pStack != NULL)
    {
        ppRoot = Pop(&pStack);

        if ((ppRoot)->pLeft != NULL)
        {
            Push(&pStack, (ppRoot)->pLeft);
            iCount++;
        }

        if ((ppRoot)->pRight != NULL)
        {
            Push(&pStack, (ppRoot)->pRight);
            iCount++;
        }
    }

    printf("The count is %d\n",iCount);
}

int Height_NonRecuursive(struct node*pRoot)
{
    struct Queue*pQueue = NULL;
    struct node*pPtr = NULL;
    int iHeight = 0;
    int count = 0;
    
    Enqueue(&pQueue,pRoot);

    while (pQueue!=NULL)
    {
        count = CountNodes_Q(pQueue); 
        iHeight++;
        for(int i=0;i<count;i++)
        {
        pPtr = Dequeue(&pQueue);
        if(pPtr->pLeft!=NULL)
        {
            Enqueue(&pQueue,pPtr->pLeft);
        }

        if(pPtr->pRight!=NULL)
        {
            Enqueue(&pQueue,pPtr->pRight);
        }
        }
    }

    printf("The Height is %d\n",iHeight);
}

int CountNodes_Q(struct Queue*pQueue)
{
    int iCount = 0;
    while (pQueue!=NULL)
    {
        iCount++;
        pQueue = pQueue->pNext;
    }
    return iCount;
    
}

void BST_DeleteRecursive(struct node**ppRoot,int iKey)
{
    struct node *pTemp = NULL;
    int No;

    if(*ppRoot==NULL)
    {
        return;
    }

    else if(iKey > (*ppRoot)->iData)
    {
        BST_DeleteRecursive(&((*ppRoot)->pRight), iKey);
    }
    
    else if (iKey < (*ppRoot)->iData)
    {
        BST_DeleteRecursive(&((*ppRoot)->pLeft), iKey);
    }

    else
    {
        if((*ppRoot)->pLeft == NULL)
        {
          pTemp = (*ppRoot)->pRight;
          free(*ppRoot);
          *ppRoot = pTemp;
          return;
        }

        else if ((*ppRoot)->pRight == NULL)
        {
            pTemp = (*ppRoot)->pLeft;
            free(*ppRoot);
            *ppRoot = pTemp;
            return;
        }

        else
        {
            pTemp = ((*ppRoot)->pRight);

            while (pTemp->pLeft != NULL)
            {
                pTemp = pTemp->pLeft;
            }

            No = pTemp->iData;
            pTemp->iData = (*ppRoot)->iData;
            (*ppRoot)->iData = No;

            BST_DeleteRecursive(&((*ppRoot)->pRight), pTemp->iData);
        }
    }
}