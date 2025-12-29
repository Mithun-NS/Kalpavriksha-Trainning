#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include <stdlib.h>

void removeint(int arr[] , int *size , int index) {
    for (int i = index ; i < *size - 1 ; i++) {
        arr[i] =  arr[i+1];
    }
    (*size)--;
}

void removechar(char arr[], int *size , int index) {
    for (int i = index ; i < *size - 1; i++) {
        arr[i] = arr[i+1];
    }
    (*size)--;
}

int main()
{
    char str[100];
    char ref[100];
    fgets(str,sizeof(str),stdin);
    str[strcspn(str,"\n")] = '\0';
    int n = strlen(str);
    int invalid = 0 , di = 0;

    int j = 0;
    for(int i = 0 ; str[i] != '\0' ; i++)
    {
        if(str[i] != ' ' && str[i] != '\n')
        {
            ref[j] = str[i];
            j++;
        }
    }
    ref[j] = '\0';
    for(int i = 0 ; ref[i] != '\0'; i++) {
        if(ref[i] == '/' && ref[i+1] == '0') {
            di++;
        }
        if(!((ref[i] >= '0' && ref[i] <= '9') || (ref[i] == '+' || ref[i] == '-' || ref[i] == '*' || ref[i] == '/'))) {
            invalid++;
        }
    }
    if(invalid > 0)
    {
        printf("Error:Invalid Expression\n");
        return 0;
    }
    if(di > 0)
    {
        printf("Error:Divisible by zero.\n");
        return 0;
    }
    printf("\n");
    int num[100];
    char ope[100];

    char d[] = " ";
    char *pos = strtok(str , d);
    int ii = 0;
    int jj = 0;
    while(pos != NULL){
        if(isdigit(pos[0]) || (pos[0]=='-' && isdigit(pos[1]))){
            num[ii] = (atoi(pos));
            ii++;
        }
        else{
            ope[jj] = pos[0];
            jj++;
        }
        pos = strtok(NULL,d);
    }

    for (int i = 0 ; i < jj ; i++) {
        if (ope[i] == '*' || ope[i] == '/') {
            if (ope[i] == '*') {
                num[i] = num[i] * num[i+1];
            }
            else if (ope[i] == '/') {
                if (num[i+1] == 0) {
                    printf("Error:Divisible by zero.\n");
                    return 0;
                }
                num[i] = num[i]/num[i+1];
            }
            removeint(num , &ii , i + 1);
            removechar(ope , &jj , i);
            i--;
        }
    }
    for (int i = 0 ; i < jj ; i++) {
        if (ope[i] == '+' || ope[i] == '-') {
            if (ope[i] == '+') {
                num[i] = num[i] + num[i+1];
            }
            else if (ope[i] == '-') {
                num[i] = num[i] - num[i+1];
            }
            removeint(num , &ii , i + 1);
            removechar(ope , &jj , i);
            i--;
        }
    }
    printf("\n");
    int res = num[0];
    printf("Result = %d\n ", res);
}