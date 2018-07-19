#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <assert.h>

void scrub(char* temp){
    int index = 0;
    while (index != '\0'){
        temp[index] = ' ';
        index++;
    }
}

int main(){
    int menuSelection;
        //git command variables
    char add[40];
    char commit[80];
    char checkout[40];
    char push[40];
    char temp[50];

        //add git commands
    strcpy(add,"git status");
    strcpy(commit, "git status");
    strcpy(checkout,"git status");
    strcpy(push,"git status");
        
        //GitHub API variables

        //display the menu
    do {
        printf("\n\tM**********************");
        printf("\n\t*I*************** *****");
        printf("\n\t**M***********   ******");
        printf("\n\t***O**********   ******");
        printf("\n\t****S*tm******* *******");
        printf("\n\t*****A********   ******");
        printf("\n\t***********************");
        printf("\n\t* Welcome Tech Writer *");
        printf("\n\t***********************\n");
        printf("\n\tSelect:");
        printf("\n\t  1. Submit a new pull request");
        printf("\n\t  2. Exit\n\n");
        printf("\t--->");

        scanf("%d",&menuSelection);
        if (menuSelection == 1) {
                //get commit
            scrub(temp);
            printf("\n\tEnter your commit message (under 50 characters): ");
            scanf("%s",&temp);
            printf(temp);
            snprintf(commit, 80, "%s%s%s","git commit -m \"", temp, "\"");
            
                //get branch name
            scrub(temp);
            printf("\n\tEnter your branch name: ");
            scanf("%s",&temp);
            snprintf(checkout, 40, "%s%s","git checkout -b ", temp);
           
                //set git push
            snprintf(push, 40, "%s%s","git push -u origin ", temp);
           
                //give a chance to cancel
            printf("\n\tYour commit: ");
            printf(commit);
           
            printf("\n\tYour checkout: ");
            printf(checkout);
            
            printf("\n\tYour push: ");
            printf(push);

            printf("\n\n\tEnter 1 to proceed or 2 to cancel: ");
            scanf("%d",&menuSelection);

            if (menuSelection == 1) {
                    //run the git commands
                system(add);
                system(commit);
                system(checkout);
                system(push);

            } else {
               menuSelection = 2;
            } 

        }

    } while(menuSelection != 2);

        //get the menu selections

        //connect to github
        //submit the pull request
        //display success message

return 0;
}
