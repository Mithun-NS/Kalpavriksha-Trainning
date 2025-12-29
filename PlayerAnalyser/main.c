#include <stdio.h>
#include <string.h>
#include "players_data.h"

void displayTeamPlayers(char team[]);
void displayTeamAverageStrikeRate(char team[]);
void displayTopKPlayersOfTeam(char team[], char role[], int k);
void displayAllPlayersByRole(char role[]);

int main()
{
    int choice;
    while (1)
    {
        printf("\n================ MENU ================\n");
        printf("1. Display Players of a Team\n");
        printf("2. Display Average Strike Rate of Batsmen in a Team\n");
        printf("3. Display Top K Players of a Team (by Role)\n");
        printf("4. Display All Players of a Role Across Teams (Global Sort)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 5)
        {
            printf("Exiting...\n");
            break;
        }
        char team[50], role[50];
        int k;
        switch (choice)
        {
            case 1:
                printf("Enter Team Name (India/Australia/England/...): ");
                scanf("%s", team);
                displayTeamPlayers(team);
                break;
            case 2:
                printf("Enter Team Name: ");
                scanf("%s", team);
                displayTeamAverageStrikeRate(team);
                break;
            case 3:
                printf("Enter Team Name: ");
                scanf("%s", team);
                printf("Enter Role (Batter/Bowler/All-Rounder/WK-Batter): ");
                scanf("%s", role);
                printf("Enter K: ");
                scanf("%d", &k);
                displayTopKPlayersOfTeam(team, role, k);
                break;
            case 4:
                printf("Enter Role (Batter/Bowler/All-Rounder/WK-Batter): ");
                scanf("%s", role);
                displayAllPlayersByRole(role);
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

void displayTeamPlayers(char team[])
{
    printf("\nPlayers in %s:\n", team);
    printf("--------------------------------------\n");
    for (int i = 0; i < 50; i++)
    {
        if (strcmp(players[i].teamName, team) == 0)
        {
            printf("%-20s %-15s PI:%d\n",
                   players[i].name,
                   players[i].role,
                   players[i].performanceIndex);
        }
    }
}

void displayTeamAverageStrikeRate(char team[])
{
    float sum = 0;
    int count = 0;
    for (int i = 0; i < 50; i++)
    {
        if (strcmp(players[i].teamName, team) == 0)
        {
            if (strcmp(players[i].role, "Batter") == 0 ||
                strcmp(players[i].role, "All-Rounder") == 0 ||
                strcmp(players[i].role, "WK-Batter") == 0)
            {
                sum += players[i].performanceIndex;  
                count++;
            }
        }
    }
    if (count == 0)
    {
        printf("No batting players found in %s.\n", team);
        return;
    }
    printf("\nAverage Strike Rate (Using PI as Avg) of %s = %.2f\n",
           team, sum / count);
}

void displayTopKPlayersOfTeam(char team[], char role[], int k)
{
    Player temp[50];
    int count = 0;

    for (int i = 0; i < 50; i++)
    {
        if (strcmp(players[i].teamName, team) == 0 &&
            strcmp(players[i].role, role) == 0)
        {
            temp[count++] = players[i];
        }
    }
    if (count == 0)
    {
        printf("No players of role %s in team %s.\n", role, team);
        return;
    }
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (temp[i].performanceIndex < temp[j].performanceIndex)
            {
                Player t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    printf("\nTop %d %s of %s:\n", k, role, team);
    printf("--------------------------------------\n");

    for (int i = 0; i < k && i < count; i++)
    {
        printf("%-20s PI:%d\n", temp[i].name, temp[i].performanceIndex);
    }
}

void displayAllPlayersByRole(char role[])
{
    Player temp[50];
    int count = 0;

    for (int i = 0; i < 50; i++)
    {
        if (strcmp(players[i].role, role) == 0)
        {
            temp[count++] = players[i];
        }
    }
    if (count == 0)
    {
        printf("No players found with role %s.\n", role);
        return;
    }
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (temp[i].performanceIndex < temp[j].performanceIndex)
            {
                Player t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }
    printf("\nAll %s in ICC  (sorted by Performance Index):\n", role);
    printf("--------------------------------------------------\n");
    for (int i = 0; i < count; i++)
    {
        printf("%-20s %-5s PI:%d (%s)\n",
               temp[i].name, temp[i].role,
               temp[i].performanceIndex, temp[i].teamName);
    }
}