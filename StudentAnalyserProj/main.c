#include<stdio.h>

#define GRADE_A 85
#define GRADE_B 70
#define GRADE_C 50
#define GRADE_D 35

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
    if (average >= GRADE_A) {
        return 'A';
    }
    else if (average >= GRADE_B) {
        return 'B';
    }
    else if (average >= GRADE_C) {
        return 'C';
    }
    else if (average >=GRADE_D) {
        return 'D';
    }
    else{
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
    printf("\n\n");
    
}
void printrollno(struct student students[],int index, int totalstudents) {
    if (index == totalstudents) return;
    printf("%d ",students[index].rollno);
    printrollno(students,index+1,totalstudents);
}
int main() {
    int totalstudents;
    printf("Enter no of students to analyse : \n");
    scanf("%d",&totalstudents);
    struct student students[totalstudents];
    for (int i = 0 ; i < totalstudents ; i++) {
        printf("\nEnter Roll, Name, and 3 subject marks: ");
        scanf("%d", &students[i].rollno);
        scanf(" %[^\n]", students[i].name);
        scanf("%f %f %f",&students[i].marks[0], &students[i].marks[1], &students[i].marks[2]);
        students[i].total = calculatetotal(students[i].marks[0], students[i].marks[1], students[i].marks[2]);
        students[i].average = calculateaverage(students[i].total);
        students[i].grade = assigngrade(students[i].average);
    }
        printf("\n");
        for (int i = 0 ; i < totalstudents ; i++) {
            printf("RollNo: %d\n",students[i].rollno);
            printf("Name: %s\n",students[i].name);
            printf("Total: %f\n",students[i].total);
            printf("Average: %f\n",students[i].average);
            printf("Grade: %c\n",students[i].grade);
            if (students[i].grade == 'F') {
                continue;
            }
            displayperformance(students[i].grade);
            printf("\n");
        }
        printf("List of roll numbers (via recursion)");
        printrollno(students,0,totalstudents);
        printf("\n");
        return 0;
    }