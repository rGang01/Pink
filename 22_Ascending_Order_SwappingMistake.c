#define MAX 20
#include <stdio.h>

void Check(int arr[],int n);

int main(void)
{
    int n;
    int arr[MAX];

    printf("Enter total no of elements in array that you want:\n");
    scanf("%d",&n);

    printf("Enter elements:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }

    Check(arr,n);
}

void Check(int arr[],int n)
{
    int First = -1;
    int Second = -1;

    for(int i=0;i<n-1;i++)
    {
        if(arr[i]>arr[i+1] && First==-1)
        {
           First = i;
        }

        else if(arr[i] > arr[i+1])
        {
            Second = i+1;
            break;
        }
    }

    printf("The elements which are not swapped properly are %d and %d\n",arr[First],arr[Second]);
}