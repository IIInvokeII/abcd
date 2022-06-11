#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
void reduce1(char[], int);
void reduce2(char[], int);
void shift(char[], int);
void accept_productions(int n);
FILE *prod, *output;
char input[20], temp_input[20], parse[20], token, rem_input[20], start[10];
int c;
void main()
{
    int i, c, n;
    clrscr();
    strcpy(parse, "");
    prod = fopen("prod.txt", "w");
    output = fopen("output.txt", "w");
    printf("Enter the number of Productions: ");
    scanf("%d", &n);
    printf("Enter the productions: ");
    accept_productions(n);
    printf("Enter the input string: ");
    scanf("%s", input);
    strcpy(temp_input, input);
    prod = fopen("prod.txt", "r");
    for (i = 0; i < strlen(input); i++)
    {
        shift(temp_input, i);
        reduce1(temp_input, i);
        reduce2(temp_input, i);
    }
    if (strcmp(rem_input, "") == 0)
    {
        if (strcmp(parse, start) == 0)
        {
            fprintf(output, "%s", "Accepted");
            printf("The given String is valid and accepted");
        }
        else
        {
            fprintf(output, "%s", "Rejected");
            printf("The given String is invalid and rejected");
        }
    }
    fclose(output);
    output = fopen("output.txt", "r");
    getch();
}
void accept_productions(int n)
{
    int i, j;
    char temp[20], left[5], right[15];
    for (i = 0; i < n; i++)
    {
        strcpy(temp, "");
        scanf("%s", temp);
        left[0] = temp[0];
        left[1] = '\0';
        if (i == 0)
            strcpy(start, left);
        for (j = 3; j < strlen(temp); j++)
            right[j - 3] = temp[j];
        right[j - 3] = '\0';
        fprintf(prod, "%s%s\n", left, right);
    }
    fflush(stdin);
    fclose(prod);
}
void shift(char string[20], int i)
{
    char t2[10];
    int j;
    token = string[i];
    c = strlen(parse);
    parse[c++] = token;
    parse[c] = '\0';
    c = 0;
    strcpy(rem_input, "");
    for (j = i + 1; j < strlen(string); j++)
        rem_input[c++] = string[j];
    rem_input[c] = '\0';
    fprintf(output, "%s\t%s\t%s\n", parse, rem_input, "SHIFT");
}
void reduce1(char string[20], int i)
{
    char production[20], t[5];
    rewind(prod);
    while (fscanf(prod, "%s %s", t, production) != EOF)
    {
        token = t[0];
        parse[strlen(parse) - 1] = token;
        fprintf(output, "%s\t%s\t%s\n", parse, rem_input, "REDUCE1");
        break;
    }
}
void reduce2(char string[20], int i)
{
    char production[20], t[5];
    rewind(prod);
    while (fscanf(prod, "%s %s", t, production) != EOF)
    {
        strcpy(parse, "");
        parse[0] = t[0];
        parse[1] = '\0';
        fprintf(output, "%s\t%s\t%s\n", parse, rem_input, "REDUCE2");
    }
}