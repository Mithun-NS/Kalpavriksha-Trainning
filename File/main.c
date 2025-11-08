#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#define FILENAME "user.txt"
struct user {
    int id;
    char name[50];
    int age;
};

void createuser() {
    struct user u, temp;
    FILE *fp, *check;
    printf("Please enter your id:\n");
    scanf("%d", &u.id);
    getchar();
    check = fopen(FILENAME, "r");
    if (check != NULL) {
        int dup = 0;
        while (fscanf(check, "%d,%49[^,],%d\n", &temp.id, temp.name, &temp.age) == 3) {
            if (temp.id == u.id) {
                dup = 1;
                break;
            }
        }
        fclose(check);
        if (dup) {
            printf("Error: ID already exists!\n");
            return;
        }
    }
    printf("Please enter your name:\n");
    fgets(u.name,sizeof(u.name),stdin);
    size_t len = strlen(u.name);
    if (len > 0 && u.name[len - 1] == '\n')
        u.name[len - 1] = '\0';
    printf("Please enter your age:\n");
    scanf("%d", &u.age);

    fp = fopen(FILENAME, "a");
    if (fp == NULL) {
        printf("File could not be opened\n");
        return;
    }
    fprintf(fp, "%d,%s,%d\n", u.id, u.name, u.age);
    fclose(fp);

    printf("User added successfully!\n");
}

void displayuser() {
    FILE *fp = fopen(FILENAME,"r");
    if (fp == NULL) {
        printf("File could not be opened\n");
        return;
    }
    struct user u;
    printf("\n--- User Records ---\n");
    while (fscanf(fp, "%d,%49[^,],%d\n", &u.id, u.name, &u.age) == 3) {
        printf("ID: %d | Name: %s | Age: %d\n", u.id, u.name, u.age);
    }
    fclose(fp);
}

void updateuser() {
    FILE *fp = fopen(FILENAME,"r");
    if (fp == NULL) {
        printf("File could not be opened\n");
        return;
    }
    FILE *temp = fopen("temp.txt","w");
    struct user u;
    int id, found = 0;
    printf("Please enter your id to update:\n");
    scanf("%d",&id);
    getchar();
    while (fscanf(fp,"%d,%49[^,],%d\n", &u.id, u.name, &u.age) == 3) {
        if (u.id == id) {
            found = 1;
            printf("Enter new name:\n");
            fgets(u.name,sizeof(u.name),stdin);
            size_t len = strlen(u.name);
            if (len > 0 && u.name[len - 1] == '\n') {
                u.name[len - 1] = '\0';
            }
            printf("Enter new age:\n");
            scanf("%d",&u.age);
        }
        fprintf(temp, "%d,%s,%d\n",u.id,u.name,u.age);
    }
    fclose(fp);
    fclose(temp);
    remove(FILENAME);
    rename("temp.txt",FILENAME);
    if (found) {
        printf("File updated successfully!\n");
    } else {
        printf("File could not be updated\n");
    }
}

void removeuser() {
    FILE *fp = fopen(FILENAME,"r");
    if (fp == NULL) {
        printf("File could not be opened\n");
        return;
    }
    FILE *temp = fopen("temp.txt","w");
    struct user u;
    int id, found = 0;
    printf("Please enter your id to remove:\n");
    scanf("%d",&id);
    while (fscanf(fp, "%d,%49[^,],%d\n", &u.id, u.name, &u.age) == 3) {
        if (u.id == id) {
            found = 1;
            continue;
        }
        fprintf(temp,"%d,%s,%d\n",u.id,u.name,u.age);
    }
    fclose(fp);
    fclose(temp);
    remove(FILENAME);
    rename("temp.txt",FILENAME);

    if (found) {
        printf("User removed successfully!\n");
    } else {
        printf("User not found!\n");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n-- Welcome to User Management --\n");
        printf("1.Add User\n");
        printf("2.Display User\n");
        printf("3.Update User\n");
        printf("4.Remove User\n");
        printf("5.Exit\n");
        printf("Enter a Choice:\n");
        scanf("%d",&choice);
        switch(choice) {
            case 1: createuser(); break;
            case 2: displayuser(); break;
            case 3: updateuser(); break;
            case 4: removeuser(); break;
            case 5: printf("Exiting...\n");
            return 0;
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}
