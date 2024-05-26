// //Without replacement

// #include <stdio.h>

// void Insert_HashTable(int arr[],int iKey,int chain[]);
// void Display_HashTable(int arr[],int chain[]);

// int count = 0;

// int main(void)
// {
//     int arr[10];
//     int chain[10];
//     int iKey;

//     for(int i=0;i<10;i++)
//     {
//         arr[i] = -1;
//         chain[i] = -1;
//     }

//     printf("Enter Data:\n");

//     for(int i=0;i<10;i++)
//     {
//         scanf("%d",&iKey);
//         Insert_HashTable(arr,iKey,chain);
//     }

//     Display_HashTable(arr,chain);
//     printf("Count %d",count);

// }

// void Insert_HashTable(int arr[],int iKey,int chain[])
// {
//     int iPos;

//     iPos = iKey%10;

//     if(arr[iPos]==-1)
//     {
//         arr[iPos] = iKey;
//         return;
//     }

//     for(int i=0;i<10;i++)
//     {
//         count++;
//         if(arr[(iPos+i)%10]==-1)
//         {
//             arr[(iPos+i)%10] = iKey;
//             for(int j=0;j<10;j++)
//             {
//                 if((arr[j]!=iKey) && (arr[j]%10==iKey%10) && (chain[j]==-1))
//                 {
//                    chain[j] = (iPos+i)%10;
//                    return;
//                 }
//             }
//         }
//     }
// }

// void Display_HashTable(int arr[],int chain[])
// {
//     for(int i=0;i<10;i++)
//     {
//         if(arr[i]!=-1)
//         {
//            printf("[%d]  %d->%d\n",i,arr[i],chain[i]);
//         }

//     }
// }


// with replacement

#include <stdio.h>

void Insert_HashTable(int arr[],int iKey,int chain[]);
void Display_HashTable(int arr[],int chain[]);

int count = 0;

int main(void)
{
    int arr[10];
    int chain[10];
    int iKey;

    for(int i=0;i<10;i++)
    {
        arr[i] = -1;
        chain[i] = -1;
    }

    printf("Enter Data:\n");

    for(int i=0;i<10;i++)
    {
        scanf("%d",&iKey);
        Insert_HashTable(arr,iKey,chain);
    }

    Display_HashTable(arr,chain);
    printf("Count %d",count);

}

void Insert_HashTable(int arr[],int iKey,int chain[])
{
    int iPos;

    iPos = iKey%10;

    if(arr[iPos]==-1)
    {
        arr[iPos] = iKey;
        return;
    }

    if(arr[iPos]!=-1 && arr[iPos]%10!=iPos)
    {
        for(int i=0;i<10;i++)
        {
            count++;
            if(arr[(iPos+i)%10]==-1)
            {
                arr[(iPos+i)%10] = arr[iPos];
                arr[iPos] = iKey;
                for(int j=0;j<10;j++)
                {
                    if(chain[j]==iPos)
                    {
                        printf("%d\t",iPos);
                        if(chain[iPos]!=-1)
                        {
                           chain[j] = chain[iPos];
                           chain[iPos] = -1;
                        }
                       chain[chain[j]] = (iPos+i)%10;
                       return;
                        
                    }
                }
            }
        }
    }

    for(int i=0;i<10;i++)
    {
        count++;
        if(arr[(iPos+i)%10]==-1)
        {
            arr[(iPos+i)%10] = iKey;
            for(int j=0;j<10;j++)
            {
                if((arr[j]!=iKey) && (arr[j]%10==iKey%10) && (chain[j]==-1))
                {
                   chain[j] = (iPos+i)%10;
                   return;
                }
            }
        }
    }

}

void Display_HashTable(int arr[],int chain[])
{
    for(int i=0;i<10;i++)
    {
        if(arr[i]!=-1)
        {
           printf("[%d]  %d->%d\n",i,arr[i],chain[i]);
        }

    }
}
