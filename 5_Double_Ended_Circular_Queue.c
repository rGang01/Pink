#define MAX 5
#include <stdio.h>

void Enque_R(int*,int);
int Deque_F(int*);
void Display(int*);
int isFull(void);
int isEmpty(void);
void Enque_F(int*,int);
int Deque_R(int*);

int iRear = -1;
int iFront = 0;

int main(void)
{
    int Queue[MAX] = {0};

    Enque_R(Queue,10);
    Enque_R(Queue,20);
    Enque_F(Queue,30);
    Enque_F(Queue,40);
    Display(Queue);

    int iDeldata = Deque_R(Queue);

    if(iDeldata!=-1)
    {
        printf("The deleted data is %d\n",iDeldata);
    }
    Display(Queue);
}

void Enque_F(int*pQueue,int iNo)
{
    if(isFull())
    {
        printf("The Queue is Full:\n");
        return;
    }

    if(isEmpty())
    {
        iRear = iFront = MAX-1;
        pQueue[iFront] = iNo;
        return;
    }

    if(iFront == 0)
    {
        iFront = MAX-1;
        pQueue[iFront] = iNo;
        return;
    }

    iFront--;
    pQueue[iFront] = iNo;

}

void Enque_R(int*pQueue,int iNo)
{
    if(isFull())
    {
        printf("The Queue is Full:\n");
        return;
    }

    if(iRear==MAX-1)
    {
        iRear = 0;
        pQueue[iRear] = iNo;
        return;
    }

   iRear++;
   pQueue[iRear] = iNo;
}

int Deque_F(int*pQueue)
{
    if(isEmpty())
    {
        printf("The Queue is Empty:\n");
        return -1;
    }

    int iDel;
    iDel = pQueue[iFront];

    if(iFront==iRear)
    {
        iFront = 0;
        iRear = -1;
        return iDel;
    }

    if(iFront==MAX-1)
    {
        iFront = 0;
        return iDel;
    }

    iFront++;
    return iDel;

}

int Deque_R(int*pQueue)
{
    if(isEmpty())
    {
        printf("The Queue is Empty:\n");
        return -1;
    }

    int iDel;
    iDel = pQueue[iRear];

    if(iFront==iRear)
    {
      iRear = -1;
      iFront = 0;
      return iDel;
    }
    
    if(iRear==0)
    {
        iRear = MAX-1;
        return iDel;
    }
     iRear--;
     return iDel;

}

int isFull(void)
{
    if((iRear==MAX-1 && iFront==0)||(iRear==iFront-1 && iRear!=-1))
    {
       return 1;
    }
    return 0;
}

int isEmpty(void)
{
    if(iRear==-1)
    {
        return 1;
    }
    return 0;
}

void Display(int*pQueue)
{
    if(iRear<iFront)
    {
        for(int i=iFront;i<=MAX-1;i++)
        {
            printf("%d\n",pQueue[i]);
        }
        for(int i=0;i<=iRear;i++)
        {
            printf("%d\n",pQueue[i]);
        }
    }

    else
    {
         for(int i=iFront;i<=iRear;i++)
         {
             printf("%d\n",pQueue[i]);
         }
    }
}