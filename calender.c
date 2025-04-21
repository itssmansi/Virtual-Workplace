#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calenderMenu(char userName[]);
void scheduleMeeting();
void setDeadline();
// void setReminder();
// void viewCalender();
// void viewCalender();

#define MAX_TITLE_LENGTH 200


typedef struct{
    FILE *meetingFile;
    char date[11];
    char time[6];
    char title[MAX_TITLE_LENGTH];
}Meeting;

void scheduleMeeting(){
    int count;
    int i;
    FILE *meetingFile;

    printf("How amny meetings do you want to schedule? ");
    scanf("%d", &count);

    getchar();
    if(count <= 0){
        printf("Invalid number of meetings!");
        return;
    }

    Meeting *meetings = (Meeting *)calloc(count, sizeof(Meeting));
    if (meetings == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    for(i = 0; i < count; i++){
        printf("\n---- Meeting %d ----", i+1);

        printf("\nEnter meeting date (DD-MM-YYYY): ");
        scanf("%s", meetings[i].date);

        printf("Enter meeting time (HH:MM - Military time): ");
        scanf("%s", meetings[i].time);
        getchar(); // clear newline

        printf("Enter meeting title: ");
        if (fgets(meetings[i].title, MAX_TITLE_LENGTH, stdin) != NULL) {
            // Remove trailing newline
            meetings[i].title[strcspn(meetings[i].title, "\n")] = '\0';
        } else {
            strcpy(meetings[i].title, "Untitled");
        }

        //  to remove any leading spaces from the title (optional polish)
        int start = 0;
        while (meetings[i].title[start] == ' ') start++;
        if (start > 0) memmove(meetings[i].title, meetings[i].title + start, strlen(meetings[i].title + start) + 1);
    }

    meetingFile = fopen("meetings.txt", "a");
    if (meetingFile == NULL) {
        printf("Could not open meetings.txt!\n");
        free(meetings);
        return;
    }

    for(i = 0; i < count; i++){
        fprintf(meetingFile, "%s | %s | %s\n", meetings[i].date, meetings[i].time, meetings[i].title);
    }

    fclose(meetingFile);
    free(meetings);
    printf("\nAll meetings scheduled successfully :)");
}

typedef struct{
    char date[11];
    char time[6];
    char D_title[MAX_TITLE_LENGTH];
}Deadline;

void setDeadline(){
    int deadlineCount;
    int i;
    FILE *deadlineFile;

    printf("Enter the number of deadlines you wqant to set: ");
    scanf("%d", &deadlineCount);
    getchar();

    if(deadlineCount <= 0){
        printf("Invalid number of deadlines! \n");
        return;
    }

    Deadline *deadlines = (Deadline *)calloc(deadlineCount, sizeof(Deadline));
    if(deadlines == NULL){
        printf("Memory allocation failed :( )");
        return;
    }

    for(i = 0; i < deadlineCount; i++){
        printf("\n--- Deadline %d ---\n", i + 1);

        printf("Enter deadline date (DD-MM-YYYY): ");
        scanf("%s", deadlines[i].date);

        printf("Enter deadline time (HH:MM - Military time): ");
        scanf("%s", deadlines[i].time);
        getchar(); // clear newline

        printf("Enter task/subject title: ");
        fgets(deadlines[i].D_title, MAX_TITLE_LENGTH, stdin);
        deadlines[i].D_title[strcspn(deadlines[i].D_title, "\n")] = '\0';
    }

    deadlineFile = fopen("deadlines.txt", "a");
    if(deadlineFile == NULL){
        printf("Could not open deadlines.txt!\n");
        free(deadlines);
        return;
    }

    for(i = 0; i < deadlineCount; i++){
        fprintf(deadlineFile, "%s | %s | %s\n", deadlines[i].date, deadlines[i].time, deadlines[i].D_title);
    }
    fclose(deadlineFile);
    free(deadlines);
    printf("\nAll deadlines successfully created :)");
}

void viewCalender(){
    printf("Opening Windows Calendar...\n");
    system("start https://calendar.google.com");
}

void calenderMenu(char userName[]){
    int choice;

    printf("\n\t\t\tTime flies, but you can keep track. Welcome! %s :)", userName);
    printf("\n--- Calendar Menu ---");

    do{
    printf("\n1. Schedule Meeting\n");
    printf("2. Set Deadline\n");
    printf("3. View calender\n");
    printf("4. Back to Main Menu\n");
    printf("Enter your choice: ");
    

    scanf("%d", &choice);

    switch(choice){
        case 1:
            scheduleMeeting();
            break;

        case 2:
            setDeadline();
            break;

        case 3:
            viewCalender();
            break;

        case 4:
            return;
        
        default:
            printf("Invalid choice");
            break;
    }
    }while(choice != 6);
}