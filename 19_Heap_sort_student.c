#define MAX 20
#include <stdio.h>

struct node
{
  int iRollno;
  char cStudentName[MAX];
  int iMarks;
};

void Max_Heap(struct node record[],int index,int n);
void Swap(struct node*a,struct node*b);

int main(void)
{
    int n;
    struct node record[MAX];

    printf("Enter total no of records that you want to store:\n");
    scanf("%d",&n);

    printf("Enter student record:\n");

    for (int i = 1; i <= n; i++) 
    {
    printf("Enter Roll no for student %d\n", i);
    scanf("%d", &record[i].iRollno);
    printf("Enter Name of student %d\n", i);
    scanf(" %[^\n]", record[i].cStudentName); 
    printf("Enter Total marks of student %d\n", i);
    scanf("%d", &record[i].iMarks);
    }

    for(int i=n/2;i>=1;i--)
    {
        Max_Heap(record,i,n);
    }

    
    for (int i = n; i >= 1; i--)
    {
        Swap(&(record[1]), &(record[i]));
        Max_Heap(record,1,i-1);
    }

    printf("The sorted Data is:\n");

    for (int i = 1; i <=n; i++)
    {
        printf("%d", record[i].iRollno);
        printf("\t");
        printf("%s", record[i].cStudentName);
        printf("\t");
        printf("%d",record[i].iMarks);
        printf("\n");
    }
}

void Max_Heap(struct node record[],int index,int n)
{
   int iLeftchild = 2*index;
   int iRightchild = iLeftchild+1;

    while (iLeftchild<=n)
    {
      if((record[index].iRollno < record[iLeftchild].iRollno) && (record[iLeftchild].iRollno > record[iRightchild].iRollno))
      {
        Swap(&record[index],&record[iLeftchild]);
        index = iLeftchild;
      }

      else if((record[index].iRollno < record[iRightchild].iRollno) && (iRightchild<=n))
      {
        Swap(&record[index],&record[iRightchild]);
        index = iRightchild;
      }

      else
      {
        return;
      }
      
        iLeftchild = 2 * index;
        iRightchild = iLeftchild + 1;
    }
   
}

void Swap(struct node*a,struct node*b)
{
   struct node pTemp;

    pTemp = *a;
    *a = *b;
    *b = pTemp;
}