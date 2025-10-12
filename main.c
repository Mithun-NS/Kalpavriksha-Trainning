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
    fgets(str,sizeof(str),stdin);
    str[strcspn(str,"\n")] = '\0';
    int invalid = 0 , di = 0;

    for(int i = 0 ; str[i] != '\0' ; i++)
    {
        if(str[i] == '/' && str[i + 1] == '0')
        {
            di++;
        }
       if (!isdigit((unsigned char)str[i]) && !(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') && str[i] != ' '){
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
    int num[100];
    char ope[100];
    int ii = 0;
    int jj = 0;
   for (int i = 0; str[i] != '\0';) {
        if (isdigit((unsigned char)str[i]) || (str[i] == '-' && isdigit((unsigned char)str[i + 1]))) {
            int val = 0, sign = 1;
            if (str[i] == '-') { sign = -1; i++; }
           while (isdigit((unsigned char)str[i])) {
                val = val * 10 + (str[i] - '0');
                i++;
            }
            num[ii++] = val * sign;
        } else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
            ope[jj++] = str[i];
            i++;
        } else {
            i++;
        }
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
    int res = num[0];
    printf("Result = %d\n", res);
    return 0;
}
