#include <stdio.h>
struct variable
{
    int count;
    int num[5];
    char tac[5][5];
    int gen[10];
    int kill[10];
    int in[7];
    int out[7];
    int prev_out[7];
} var[10];
int main()
{
    int n, i, d_no = 1, k, j, l, in_no, adj[6][6], a, b, l_no, flag = 0, pass = 2;
    printf("\nEnter the number of blocks:");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\nEnter the number of equations in block %d:", i + 1);
        scanf("%d", &var[i].count);
        for (k = 0; k < var[i].count; k++)
        {
            var[i].num[k] = d_no;
            d_no++;
            printf("\nEnter the tac sequence %d:", k + 1);
            scanf("%s", var[i].tac[k]);
        }
    }
    for (i = 0; i < n; i++)
    {
        for (k = 0; k < d_no - 1; k++)
        {
            var[i].gen[k] = 0;
            var[i].in[k] = 0;
            var[i].out[k] = 0;
            var[i].prev_out[k] = 0;
        }
        for (k = 0; k < var[i].count; k++)
        {
            var[i].gen[var[i].num[k] - 1] = 1;
        }
    }
    printf("\nGEN SET");
    for (i = 0; i < n; i++)
    {
        printf("\n");
        for (k = 0; k < d_no - 1; k++)
            printf("%d", var[i].gen[k]);
    }
    for (i = 0; i < n; i++)
    {
        for (k = 0; k < d_no - 1; k++)
            var[i].kill[k] = 0;
        for (k = 0; k < var[i].count; k++)
        {
            for (j = 0; j < n; j++)
            {
                if (j != i)
                {
                    for (l = 0; l < var[j].count; l++)
                    {
                        if (var[i].tac[k][0] == var[j].tac[l][0])
                        {
                            var[i].kill[var[j].num[l] - 1] = 1;
                        }
                    }
                }
            }
        }
    }
    printf("\nKILL SET");
    for (i = 0; i < n; i++)
    {
        printf("\n");
        for (k = 0; k < d_no - 1; k++)
            printf("%d", var[i].kill[k]);
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            adj[i][j] = 0;
    }
    printf("\nEnter the number of links:");
    scanf("%d", &l_no);
    for (i = 0; i < l_no; i++)
    {
        printf("\nEnter the link %d:", i + 1);
        scanf("%d%d", &a, &b);
        adj[a - 1][b - 1] = 1;
    }
    printf("\nAdjacency Matrix");
    for (i = 0; i < n; i++)
    {
        printf("\n");
        for (j = 0; j < n; j++)
            printf("%d", adj[i][j]);
    }
    for (i = 0; i < n; i++)
    {
        if (adj[i][0] == 1)
        {
            for (j = 0; j < d_no - 1; j++)
                var[0].in[j] = var[i].gen[j] | var[0].in[j];
        }
    }
    for (i = 0; i < d_no - 1; i++)
    {
        a = var[0].in[i] | var[0].gen[i];
        b = var[0].in[i] & var[0].kill[i];
        var[0].out[i] = a - b;
    }
    /*printf("\nIn of first block:");
    for(i=0;i<d_no-1;i++)
    {
    printf("%d",var[0].in[i]);
    }
    printf("\nOut of first block:");
    for(i=0;i<d_no-1;i++)
    {
    printf("%d",var[0].out[i]);
    }*/
    for (i = 1; i < n; i++)
    {
        for (k = 0; k < n; k++)
        {
            if (adj[k][i] == 1)
            {
                for (j = 0; j < d_no - 1; j++)
                    var[i].in[j] = var[k].out[j] | var[i].in[j];
            }
        }
        for (j = 0; j < d_no - 1; j++)
        {
            a = var[i].in[j] | var[i].gen[j];
            b = var[i].in[j] & var[i].kill[j];
            var[i].out[j] = a - b;
        }
    }
    for (i = 0; i < n; i++)
    {
        printf("\n");
        for (j = 0; j < d_no - 1; j++)
            printf("%d", var[i].in[j]);
        printf("\t");
        for (j = 0; j < d_no - 1; j++)
            printf("%d", var[i].out[j]);
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < d_no - 1; j++)
            var[i].prev_out[j] = var[i].out[j];
    }
    while (flag == 0)
    {
        for (i = 0; i < n; i++)
        {
            for (k = 0; k < n; k++)
            {
                if (adj[k][i] == 1)
                {
                    for (j = 0; j < d_no - 1; j++)
                        var[i].in[j] = var[k].prev_out[j] |
                                       var[i].in[j];
                }
            }
            for (j = 0; j < d_no - 1; j++)
            {
                a = var[i].in[j] | var[i].gen[j];
                b = var[i].in[j] & var[i].kill[j];
                var[i].out[j] = a - b;
            }
        }
        printf("\nPass:%d", pass++);
        for (i = 0; i < n; i++)
        {
            printf("\n");
            for (j = 0; j < d_no - 1; j++)
                printf("%d", var[i].in[j]);
            printf("\t");
            for (j = 0; j < d_no - 1; j++)
                printf("%d", var[i].out[j]);
        }
        flag = 1;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < d_no - 1; j++)
            {
                if (var[i].out[j] != var[i].prev_out[j])
                {
                    break;
                }
            }
        }
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < d_no - 1; j++)
                var[i].prev_out[j] = var[i].out[j];
        }
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < d_no - 1; j++)
            {
                var[i].in[j] = 0;
                var[i].out[j] = 0;
            }
        }
    }
    return 0;
}

/* gcc cfg.c
./a.out
Enter the number of blocks:5
Enter the number of equations in block 1:2
Enter the tac sequence 1:i=2
Enter the tac sequence 2:i+1
Enter the number of equations in block 2:1
Enter the tac sequence 1:i=1
Enter the number of equations in block 3:1
Enter the tac sequence 1:j=j+1
Enter the number of equations in block 4:1
Enter the tac sequence 1:j=j-4
Enter the number of equations in block 5:0
GEN SET
11000
00100
00010
00001
00000
KILL SET
00100
11000
00001
00010
00000
Enter the number of links:7
Enter the link 1:1 2
Enter the link 2:2 3
Enter the link 3:2 1
Enter the link 4:3 4
Enter the link 5:3 5
Enter the link 6:4 5
Enter the link 7:5 2
Adjacency Matrix
01000
10100
00011
00001
01000
00100 11000
11000 00100
00100 00110
00110 00101
00111 00111
Pass:2
00100 11000
11111 00111
00100 00110
00110 00101
00111 001111 */