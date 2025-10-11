#include<stdio.h>
struct student {
    int rollno;
    char name[50];
    float marks[3];
    float total;
    float average;
    char grade;
};

float calculatetotal(float mark1, float mark2,float mark3){
    return mark1+mark2+mark3;
}

float calculateaverage(float total){
    return total/3;
}

char assigngrade(float average){
    if (average >= 85) {
        return 'A';
    }
    else if (average >= 70 && average < 85) {
        return 'B';
    }
    else if (average >= 50 && average < 70) {
        return 'C';
    }
    else if (average >= 35 && average < 50) {
        return 'D';
    }
    else if (average < 35) {
        return 'F';
    }
}

void displayperformance(char grade) {
    printf("Performance\n");
    if (grade == 'F') {
        return;
    }
    int stars = 0;
    switch (grade) {
        case 'A' : stars = 5;
            break;
        case 'B' : stars = 4;
            break;
        case 'C' : stars = 3;
            break;
        case 'D' : stars = 2;
            break;
    }
    for (int i = 0 ; i < stars; i++) {
        printf("*");
    }
    printf("\n");
}
void printrollno(struct student s[],int index, int n) {
    if (index == n) return;
    printf("%d ",s[index].rollno);
    printrollno(s,index+1,n);
}
int main() {
    int n;
    printf("Enter no of persons to analyse : \n");
    scanf("%d",&n);
    struct student s[n];
    for (int i = 0 ; i < n ; i++) {
        printf("\nEnter Roll, Name, and 3 subject marks: ");
        scanf("%d %s %f %f %f", &s[i].rollno, s[i].name, &s[i].marks[0], &s[i].marks[1], &s[i].marks[2]);
        s[i].total = calculatetotal(s[i].marks[0],s[i].marks[1],s[i].marks[2]);
        s[i].average = calculateaverage(s[i].total);
        s[i].grade = assigngrade(s[i].average);
    }
        printf("\n");
        for (int i = 0 ; i < n ; i++) {
            printf("RollNo: %d\n",s[i].rollno);
            printf("Name: %s\n",s[i].name);
            printf("Total: %f\n",s[i].total);
            printf("Average: %f\n",s[i].average);
            printf("Grade: %c\n",s[i].grade);
            if (s[i].grade == 'F') {
                continue;
            }
            displayperformance(s[i].grade);
            printf("\n");
        }
        printf("List of roll numbers (via recursion)");
        printrollno(s,0,n);
        printf("\n");
        return 0;
    }
