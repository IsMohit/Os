// Banker's Algorithm
#include <stdio.h>

int main()
{
    int np, nr, i, j, k; // Added comma to separate np and nr

    printf("Enter no. of processes:");
    scanf("%d", &np);
    printf("Enter no of Resources:");
    scanf("%d", &nr);

    int inst[nr];
    for (i = 0; i < nr; i++)
    {
        printf("Enter instances of resource R%d:", i + 1);
        scanf("%d", &inst[i]);
    }

    int avail[nr]; // Added array to store available resources

    int finish[np], ans[np], ind = 0;
    int need[np][nr], all[np][nr], max[np][nr];

    // initially no one process is finished so 0
    for (k = 0; k < np; k++)
    {
        finish[k] = 0;
    }

    printf("\nEnter the allocation matrix :: \n");
    for (i = 0; i < np; i++)
    {
        for (j = 0; j < nr; j++)
        {
            scanf("%d", &all[i][j]);
        }
    }

    printf("\nEnter the max matrix :: \n");
    for (i = 0; i < np; i++)
    {
        for (j = 0; j < nr; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    // Available Resources
   // Available Resources
for (j = 0; j < nr; j++)
{
    int csum = 0;
    for (i = 0; i < np; i++)
    {
        csum = csum + all[i][j];
    }
    avail[j] = inst[j] - csum;
}


    for (i = 0; i < np; i++)
    {
        for (j = 0; j < nr; j++)
        {
            need[i][j] = max[i][j] - all[i][j];
        }
    }

    int y = 0;
    for (k = 0; k < np; k++) // Changed loop condition to use np
    {
        for (i = 0; i < np; i++)
        {
            if (finish[i] == 0)
            {
                int flag = 0;
                for (j = 0; j < nr; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (y = 0; y < nr; y++)
                        avail[y] += all[i][y];
                    finish[i] = 1;
                }
            }
        }
    }

   	printf("\n--------------------------------------------\n");

	printf("\nALLOCATION MATRIX :: \n");
    for (i = 0; i < np; i++)
    {
        for (j = 0; j < nr; j++)
        {
            printf("%d\t", all[i][j]);
        }
        printf("\n");
    }
    	printf("\nMAX MATRIX :: \n");
    for (i = 0; i < np; i++)
    {
        for (j = 0; j < nr; j++)
        {
            printf("%d\t", max[i][j]);
        }
         printf("\n");
    }
    	printf("\nNEED MATRIX :: \n");
    for (i = 0; i < np; i++)
    {
        for (j = 0; j < nr; j++)
        {
            printf("%d\t", need[i][j]);
        }
         printf("\n");
    }
//    printf("\nAVAILABLE MATRIX :: \n");
//for (j = 0; j < nr; j++)
//{
//    printf("%d\t", avail[j]);
//}


 int flag = 1;
    for (i = 0; i < np; i++)
    {
        if (finish[i] == 0)
        {
            flag = 0;
            printf("The following sequence is NOT SAFE");
            break;
        }
    }
    if (flag == 1)
    {
        printf("Following is the SAFE Sequence\n");
        for (i = 0; i < np - 1; i++)
            printf(" P%d ->", ans[i]);
        printf(" P%d", ans[np - 1]);
    }
    
    
    return (0);
}

