#include <stdio.h>
#include <string.h>
#include <ctype.h> // for isspace function
#include <stdlib.h>
//#include "task_manager.h"

void addTask(char userName[]);
void viewTask(char userName[]);
void deleteTask(char userName[]);
void taskManagerMenu(char userName[]); 

struct task {
    char description[200];
    int task_status; // 0 -> pending, 1 -> completed
};

// Add Task Function
void addTask(char userName[]) {
    //struct task newTask;
    FILE *taskFile;
    int c;
    struct task *tasks;
    int n;
    int i;

    printf("Enter the number of tasks you want to create:");
    scanf("%d", &n);

    tasks = (struct task *)calloc(n, sizeof(struct task));
    if(tasks == NULL){
        printf("Memory allocation failed!");
        return;
    }

    // Clear any extra input
    while ((c = getchar()) != '\n' && c != EOF);

    for(i = 0; i < n; i++){

    printf("Enter task description: ");
    fgets(tasks[i].description, sizeof(tasks[i].description), stdin);

    // Remove trailing newline that gets added due to fgets
    tasks[i].description[strcspn(tasks[i].description, "\n")] = '\0';

    // Trim leading spaces
    char *start = tasks[i].description;
    while (*start && isspace((unsigned char)*start)) start++;

    // Trim trailing spaces
    char *end = start + strlen(start) - 1;
    while (end >= start && isspace((unsigned char)*end)) end--;

    *(end + 1) = '\0';  // here we are adding Null to terminate the trimmed string

    if (strlen(start) == 0) {
        printf("Error: Task description cannot be empty.\n");
        i--;
        return;
    }

    // Copying the trimmed input into the task description
    strcpy(tasks[i].description, start);
    tasks[i].task_status = 0;

}

    char userTaskFileName[100];
    sprintf(userTaskFileName, "%s_tasks.txt", userName);

    taskFile = fopen(userTaskFileName, "a");
    if (taskFile != NULL) {
    for(i = 0; i < n; i++){
        if(strlen(tasks[i].description) > 0){
            fprintf(taskFile, "%d|%s\n", tasks[i].task_status, tasks[i].description);
        }
    }
    printf("All valid tasks saved successfully!\n");
        fclose(taskFile);
    }
    else {
        printf("Error: Could not open file to save your task.\n");
    }
    free(taskFile);
}

// View Task Function
void viewTask(char userName[]) {
    FILE *taskFile;
    int taskCount = 0;
    char line[256];
    struct task *tasks;
    int capacity = 5;
    int i;

    tasks = (struct task *) malloc(capacity * sizeof(struct task));

    char userTaskFileName[100];
    sprintf(userTaskFileName, "%s_tasks.txt", userName);

    taskFile = fopen(userTaskFileName, "r");

    if (taskFile == NULL) {
        printf("No tasks found for %s.\n", userName);
        return;
    }

    printf("\n\n\t\t\t\tTasks for %s:\n", userName);

    while (fgets(line, sizeof(line), taskFile)) {           //reading each line from the task file
        if(taskCount == capacity){
            capacity *= 2;
        }

        //reallocate logic
        struct task *temp = realloc(tasks, capacity * sizeof(struct task));
        if(temp == NULL){
            printf("Memory allocation unsuccessful");
            free(tasks);
            fclose(taskFile);
            return;
        }

        tasks = temp; //Now we update our pointer tasks to point to the newly resized memory

        if (sscanf(line, "%d|%199[^\n]", &tasks[taskCount].task_status, tasks[taskCount].description) == 2) {
           taskCount++;
        } else {
            printf("Warning: Could not parse line: %s", line);
        }
    }

    fclose(taskFile);

   if(taskCount == 0){
    printf("No tasks to show.\n");
   }
   else{
    printf("\n\n\t\t\tTasks for %s:\n", userName);
    for(i = 0; i < taskCount; i++){
        printf("\nTasks #%d\n", i+1);
        printf("Description: %s\n", tasks[i].description);
        printf("Status: %s\n", tasks[i].task_status == 0 ? "Pending" : "Completed");
   }

    free(tasks);
}
}

//Delete task 
void deleteTask(char userName[]){
    FILE *taskFile;
    int taskCount = 0;
    char line[256];
    int taskToDelete;
    int i;
    
    // Read tasks and display them
    viewTask(userName);

    // Ask the user which task to delete
    printf("\nEnter the number of the task you want to delete: ");
    if(scanf("%d", &taskToDelete) != 1 || taskToDelete <= 0){
        printf("Invalid task number.\n");
        return;
    }

    // Open the task file to read the tasks
    char userTaskFileName[100];
    sprintf(userTaskFileName, "%s_tasks.txt", userName);
    taskFile = fopen(userTaskFileName, "r");

    if (taskFile == NULL) {
        printf("No tasks found for %s.\n", userName);
        return;
    }

    struct task *tasks = malloc(100 * sizeof(struct task)); // Dynamically allocate memory for up to 100 tasks

    while (fgets(line, sizeof(line), taskFile)) {
    if (strlen(line) > 1 && sscanf(line, "%d|%199[^\n]", &tasks[taskCount].task_status, tasks[taskCount].description) == 2) {
        taskCount++;
    } else if (strlen(line) > 1) {
        printf("Warning: Could not parse line: %s", line);
    }
}
    fclose(taskFile);

    if(taskToDelete > taskCount || taskToDelete <= 0){
        printf("Invalid task number!\n");
        free(tasks);
        return;
    }

    for(i = taskToDelete - 1; i < taskCount - 1; i++){
        tasks[i] = tasks[i + 1];
    }

    taskCount--;

    taskFile = fopen(userTaskFileName, "w");

    if(taskFile == NULL){
        printf("Error opening file to update tasks.\n");
        free(tasks);
        return;
    }

    for(i = 0; i < taskCount; i++){
        fprintf(taskFile, "%d|%s\n", tasks[i].task_status, tasks[i].description);
    }
    fclose(taskFile);
    printf("\nTask deleted successfully! :)\n");

    viewTask(userName);

    free(tasks);

}
 
// Task Manager Menu
void taskManagerMenu(char userName[]){
    int taskChoice = 0;
    int keepAsking = 1;

    while (keepAsking) {
        printf("\n\nWelcome to Task Manager, %s\n", userName);
        printf("\nSelect the task you want to perform:");
        printf("\n1. Create Task");
        printf("\n2. View Task / Update Status");
        printf("\n3. Delete Task");
        printf("\n4. Exit");
        printf("\nYour choice is: ");

        if (scanf("%d", &taskChoice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // clear input buffer
            continue;
        }

        while (getchar() != '\n'); // clear buffer

        switch (taskChoice) {
            case 1:
                addTask(userName);
                break;
            case 2:
                viewTask(userName);
                break;
            case 3:
                deleteTask(userName);
                break;            
            case 4:
                keepAsking = 0;
                printf("Exiting Task Manager. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
                break;
        }
    }

    printf("Returning to Main Menu.\n");
    return;
}
