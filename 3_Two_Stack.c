#define iSize 6
#include <stdio.h>
#include <stdlib.h>

int iTop1 = -1;
int iTop2 = iSize;

void Push(int *pStack,int iNo);
int Pop(int *pStack);
int isFull();
int isEmpty();
void Display(int *pStack);

int main(void)
{
    int a,iNo,iPopped;
    int Stack[iSize];


    while(1)
    {
        printf("Enter 1 for Push\n Enter 2 for Pop\n Enter 3 for Display\n Enter 4 for Exit\n");
        scanf("%d",&a);
        switch (a)
        {
        case 1:
            printf("Enter element for Push:\n");
            scanf("%d",&iNo);
            Push(Stack,iNo);
            break;
        case 2:
            iPopped = Pop(Stack);
            if(iPopped!=-1)
            {
                printf("The Popped element is %d\n",iPopped);
            }
            break;
        case 3:
            Display(Stack);
            break;
        case 4:
          exit(0);
          break;
        }
    }
}

void Push(int *pStack,int iNo)
{ 
    if(isFull())
    {
        printf("The Both stack are Full\n");
        return;
    }

    if(iTop1==iSize/2-1)
    {
        printf("The Stack 1 is Full we are Pushing in stack 2\n");
        iTop2--;
        pStack[iTop2] = iNo;
        return;
    }

    iTop1++;
    pStack[iTop1] = iNo;
}

int Pop(int *pStack)
{
    if(isEmpty())
    {
        printf("The Both stack are Empty:\n");
        return -1;
    }
    int iPopped;

    if(iTop2==iSize)
    {
        printf("The stack2 is Empty: we are poping from stack1\n");
        iPopped = pStack[iTop1];
        iTop1--;
        return iPopped;
    }

    iPopped = pStack[iTop2];
    iTop2++;
    return iPopped;
}

int isFull()
{
    if(iTop2-iTop1==1)
    {
        return 1;
    }

    return 0;
}

int isEmpty()
{
    if(iTop1==-1 && iTop2==iSize)
    {
        return 1;
    }

    return 0;
}

void Display(int *pStack)
{
    if(isEmpty())
    {
        printf("The stack is Empty:\n");
        return;
    }

    printf("The Elements are:\n");

    if(iTop2!=iSize)
    {
        for(int i=iTop2;i<iSize;i++)
        {
            printf("%d\n",pStack[i]);
        }
    }

    for(int i=iTop1;i>=0;i--)
    {
        printf("%d\n",pStack[i]);
    }
}