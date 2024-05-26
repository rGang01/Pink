#define MAX 20
#include <stdio.h>

struct node
{
  int iEmpno;
  char cEmpName[MAX];
  int iSalary;
};

int iCount = 0;

void Quicksort(struct node record[],int l,int h);
int Partition(struct node record[],int l,int h);
void Swap(struct node*a,struct node*b);

int main(void)
{
    int n,l,h;
    struct node record[MAX];

    printf("Enter total no records that you want to store:\n");
    scanf("%d",&n);

    l = 0;
    h = n-1;

    printf("Enter Records:\n");

    for(int i=0;i<n;i++)
    {
        printf("Enter EmpNo for %d Employee\n",i+1);
        scanf("%d",&record[i].iEmpno);
        printf("Enter Name of %d Employee\n",i+1);
        scanf(" %[^\n]",record[i].cEmpName);
        printf("Enter Salary for %d Employee",i+1);
        scanf("%d",&record[i].iSalary);
    }

    Quicksort(record,l,h);
    
    
    printf("The sorted Data is:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d", record[i].iEmpno);
        printf("\t");
        printf("%s", record[i].cEmpName);
        printf("\t");
        printf("%d",record[i].iSalary);
        printf("\n");
    }
    
    printf("The Total no of swapped performed are %d\n",iCount);
}

void Quicksort(struct node record[],int l,int h)
{
    int j;

    if(l < h)
    {
       j = Partition(record,l,h);
       Quicksort(record,l,j-1);
       Quicksort(record,j+1,h);
    }
}

int Partition(struct node record[],int l,int h)
{
    int pivot,i,j;
    pivot = record[l].iEmpno;
    i = l;
    j = h;

    while (i<j)
    {
        while (record[i].iEmpno <= pivot)
        {
           i++;
        }

        while (record[j].iEmpno > pivot)
        {
            j--;
        }

        if(i < j)
        {
            Swap(&record[i],&record[j]);
        }
        
    }

    Swap(&record[l],&record[j]);
    return j;
}

void Swap(struct node*a,struct node*b)
{
   struct node pTemp;

    pTemp = *a;
    *a = *b;
    *b = pTemp;

    iCount++;
}