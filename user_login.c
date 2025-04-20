#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "task_manager.c" 
#include "office_suite.c"
#include "calender.c"
#define ENTER 13
#define TAB 9
#define BCKSPC 8

struct user
{
    char fullName[50];
    char email[50];
    char password[50];
    char userName[50];
    char phoneNumber[50];
};

void takeInput(char ch[50])
{
    fgets(ch, 50, stdin);
    ch[strlen(ch) - 1] = 0; //ch[strcspn(ch, "\n")] = '\0'; // removes newline safely
}

char generateUsername(char email[50], char userName[50])
{
    //eg: abc123@gmail.com
    int i;

    for(i=0; i<strlen(email); i++){
        if(email[i] == '@') 
        break;
        else 
        userName[i]=email[i]; //will store abc123
    }
    userName[i] = '\0';
}

void takePassword(char pwd[50]){
    int i = 0;
    char ch;
    while(1){
        ch = getch();
        if(ch == ENTER || ch == TAB){
            pwd[i] = '\0';
            break;
        }
        else if(ch == BCKSPC){
            if(i > 0){
                i--;
                printf("\b \b");
            }
        }
        else{
            if(i<49){
          pwd[i++] = ch; 
          printf("* \b");
            }
        }
    }
}

void taskMenu(char username[]);

int main(){
    system("color 0b");
    FILE *fp;
    int option, userFound = 0;
    char confirmPassword[50];

    struct  user user;

    printf("\n\t\t\t\t----------Welcome to WorkHive - Work. Collaborate. Grow ----------");
    printf("\n\t\t\t\t-----------------Welcome to authentication system-----------------");
    printf("\nPlease choose you operation");
    printf("\n1. Signup\n2. Login\n3. Exit");

    printf("\n\nYou choice:\t");
    scanf("%d", &option);
    fgetc(stdin); //consume \n

    switch(option){
        case 1: 
        system("cls"); //to be checked
        printf("Enter your full name:\t");
        takeInput(user.fullName);
        printf("Enter your Email:\t");
        takeInput(user.email);
        printf("Enter your contact number:\t");
        takeInput(user.phoneNumber);
        printf("Enter your password:\t");
        takePassword(user.password);
        printf("\nConfirm your Password:\t");
        takePassword(confirmPassword);

        if(!strcmp(user.password, confirmPassword)){
            generateUsername(user.email, user.userName);
            fp = fopen("User.dat", "a+");
            fwrite(&user, sizeof(struct user), 1, fp);
            if(fwrite != 0){
                printf("\n\nUser registration successfull!! You username is %s", user.userName);
                taskMenu(user.userName); //new
            }
            else{
                printf("\n\nSorry! something went wrong :()");
                fclose(fp);
            }
        }
        else{
            printf("\n\nYour passwords do not match");
        }
        break;

        case 2:{
        char loginUsername[50], loginPwd[50];
        struct user login_user;
        char loggedInUser[50];//new code here
        
        printf("\nEnter your username:\t");
        takeInput(loginUsername);
        printf("Enter your password:\t");
        takePassword(loginPwd);

        system("cls");

        fp = fopen("User.dat", "r");
        while(fread(&login_user, sizeof(struct user), 1, fp)){
            if(!strcmp(login_user.userName, loginUsername)){
                if(!strcmp(login_user.password, loginPwd)){
                    //printf("\n\t\t\t\t\t\tWelcome %s", login_user.fullName);

                     //new code here 
                    strcpy(loggedInUser, login_user.userName);
                    taskMenu(loggedInUser); //calling menu
                }
                else{
                    printf("\n\nInvalid password!");
                }
                userFound = 1;
            }
        }
        if(!userFound){
            printf("\n\nUser is not registered!");
        }
        fclose(fp);
        break;
    }

    case 3:
    printf("\t\t\t\t\t\tThank you for using WorkHive!");
    return 0;
    }


    getch();
    return 0;
}

void taskMenu(char username[]){
    int choice;

    printf("\n\t\t\t\t\t\tWelcome %s", username);
    printf("\nChoose an operation:\t");
    printf("\n1. Task Manager");
    printf("\n2. Office Suite");
    printf("\n3. Calender");
    printf("\n4. View User Info");


    printf("\n\nYour choice:\t");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            taskManagerMenu(username);
            break;

        case 2:
            officeSuitMenu();
            break;

        case 3:
            calenderMenu(username);
            break;

        default:
            printf("Invalid choice. Please try again.\n");
            break;

        //add case here!!!!
    }


}