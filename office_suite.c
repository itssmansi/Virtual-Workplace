#include <stdio.h>
#include <stdlib.h>

void openMSWord();
void openExcel();
void openPowerPoint();
void officeSuiteMenu();

void openMsWord() {
    // For Windows
    printf("Opening MS Word...\n");
    system("start winword");  // This assumes MS Word is installed and available in the system's PATH.
}

void openExcel() {
    // For Windows
    printf("Opening Excel...\n");
    system("start excel");  // This assumes Excel is installed and available in the system's PATH.
}

void openPowerPoint() {
    // For Windows
    printf("Opening PowerPoint...\n");
    system("start powerpnt");  // This assumes PowerPoint is installed and available in the system's PATH.
}



void officeSuitMenu(){
    int work_choice;

    do{
        printf("\n--- Office Suite ---\n");
        printf("1. MS Word\n");
        printf("2. MS Excel\n");
        printf("3. PowerPoint\n");
        printf("4. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &work_choice);

        switch(work_choice){
            case 1:
                openMsWord();
                break;
            case 2: 
                openExcel();
                break;
            case 3:
                openPowerPoint();
                break;
            case 4:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while(work_choice != 4);
}

