#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 40
#define MIN_SIZE 2
#define EMPTY_SPOT -1
#define LOOP_RESET 0
#define LOOP_BREAK 1

int menu(){
    printf("THIS IS A MENU AHAHAHAHHA");
    return 0;
}

int main(){
    int height = 0; int width = 0;
    int i, j, loopCondition = LOOP_RESET;
    int maxArtifacts, numOfArtifacts = 0;
    char input[100];
    

    /*ask user for height and width of map*/
    while (!loopCondition){
        printf("Enter map height: "); 
        while (fgets(input, sizeof(input), stdin)){
            if (sscanf(input," %d", &height) == 1){
                break;
            } else {
                printf("Error: height input is in incorrect format, re-enter with an integer value\nEnter map height: ");
            }
        }
        /*checks if height is out of bounds*/
        if (height < MIN_SIZE || height > MAX_SIZE) {
            printf("Error: height out of bounds - enter an integer between %d - %d\n", MIN_SIZE, MAX_SIZE);
            continue;
        }
        

        printf("Enter map width: "); 
        while (fgets(input, sizeof(input), stdin)){
            if (sscanf(input," %d", &width) == 1){
                break;
            } else {
                printf("Error: width input is in incorrect format, re-enter with an integer value\nEnter map width: ");
            }
        }
        /*checks if width is out of bounds*/
        if (width < MIN_SIZE || width > MAX_SIZE) {
            printf("Error: width out of bounds - enter an integer between %d - %d\n", MIN_SIZE, MAX_SIZE);
            continue;
        }
        loopCondition = LOOP_BREAK; /*exit loop*/
    }


    /*creates a 2d array based on height and width*/
    int **arr;
    arr = malloc(height * sizeof(int *));
    for (i = 0; i < height; i++) {
        *(arr + i) = malloc(width * sizeof(int));
        for (j = 0; j < width; j++) {
        *(*(arr + i) + j) = EMPTY_SPOT;
        }
    }


    /*creates the artifact amount*/
    maxArtifacts = (height * width); /*upper bound is height * width*/
    loopCondition = LOOP_RESET;
    while(!loopCondition){
        /*asks user for an amount of artifacts, checks validity*/
        printf("Enter the number of artifacts: "); 
        while (fgets(input, sizeof(input), stdin)){
            if (sscanf(input," %d", &numOfArtifacts) == 1){
                break;
            } else {
                printf(("Error: input is in incorrect format, re-enter with an integer value \nEnter the number of artifacts: "));
            }
        }
        /*checks if number of artifacts is above one and less than max*/
        if (numOfArtifacts < 1 || numOfArtifacts > maxArtifacts){
            printf("Error: number of artifacts out of bounds - enter a number between 1 - %d\n", maxArtifacts);
            continue;
        }
        loopCondition = LOOP_BREAK;
    }


    /* user adds a code to the artifact(s)*/
    char *artifactCode = malloc(5 * sizeof(char)); /*an array to store the artifact code - useful for validity and such and such*/
    char **artifactCodeIndex = malloc(numOfArtifacts * sizeof(char *)); /*an array to store the artifact codes*/
    for (i=0; i<numOfArtifacts; i++){
        *(artifactCodeIndex + i) = malloc(5 * sizeof(char));


        while(1){
            printf("Code for atrifact %d:", i + 1); 
            scanf("%4s", artifactCode);

            if (!isalpha(*(artifactCode)) || !isdigit(*(artifactCode + 1)) || !isdigit(*(artifactCode + 2)) || !isdigit(*(artifactCode + 3)) || *(artifactCode + 4) != '\0') {
            printf("Error: input is in incorrect format, re-enter with a valid code (ex. S743, y824)\n");
            continue;
        }


        int exists = 0;
        for (j = 0; j < i; j++) {
            if (strcmp(artifactCode, *(artifactCodeIndex + j)) == 0) {
                exists = 1;
                break;
            }
        }
        if(exists){
            printf("Error: code already exists in database, re-enter a different valid code (ex. S743, y824)\n");
            continue;
        }
        strcpy(*(artifactCodeIndex + i), artifactCode);
        break;
        }
    }
    

    /*put artifacts into random spot in the 2d array*/
    for (i = 0; i < numOfArtifacts; i++){
        int artifactx = rand() % (height); int artifacty = rand() % (width); /* random % (max - min + 1) + min | min = 0 */
        if (*(*(arr + artifactx) + artifacty) == -1) {
            *(*(arr + artifactx) + artifacty) = i;
        } else {
            i--;
        }
    }

    /*STUPID CHAT THING TO PRINT THE STUFF SO IK IM NOT INSANEEEE AHAHAHA*/
    printf("\nArtifact Codes and Their Locations:\n");

    for (i = 0; i < numOfArtifacts; i++) {
        printf("Code %s is at positions:\n", artifactCodeIndex[i]);
        int found = 0;
        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++) {
                if (arr[x][y] == i) {
                    printf("  (%d, %d)\n", x, y);
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("  (Not placed on the grid)\n");
        }
        printf("\n");
    }  
return EXIT_SUCCESS;
}

/*
int function menu(){
for loop
for loop    
;
}

int function dig(){
; while numOfArtifacts != 0
}

int function debug(){
    ;
}
*/
/* main()
    ask user for input, height and width
        - minimum 2, maximum 40
        - allocate that as a 2d array, using pointers
            -suggested to do this as an array of arrays

    
    Ask user to input how many artifacts they want to add
        -need input codes for each artifact
            - codes are one letter and 3 digits
            - verify correctness
                - each code will be checked
                - lowercase letter = lesser artifact(1 points) else 2 points
                - each artifact must be unique 
            - each artifact will gain a randomly assigned corrdinate


        
    User will guess where artifact is by entering x and y
        -check data if artifact was found, if so which one 
            - if fail how far away is the artifact
                -at 10 or more away mark an x, #

	Load data stuff

Function menu()
	Switch case menu
		Option 1 - function dig
		Option 2 - exit
		Option 3 - debug function

Function dig()


Function debug()

Extra things:
- error handling
    - game map must be big enough
    EOF inputs are properly caught and handled
    artifact codes are valid/not duplicated
    each assigned location for an artifact is not duplicated
    all user input is valid
    formula for distance
        - square root((player input x - artifact y)^2 + (player input y - artifact y)^2)
        - if found do a ! symbol
        - debug mode shows location of artifacts



Average user experience - entry
0 1 2 3 4 5 6
1**************
2**************
3**************
4**************
5**************
6**************


Debug mode (? - unfound, ! - found)
0 1 2 3 4 5 6
1  ?
2
3     !         ?
4
5
6       ?


Average user experience - while playing(# - farther than 9)
0 1 2 3 4 5 6
1*****#*********
2**************
3*#*************
4**********!***
5**************
6****!**********


Another user experience
0 1 2 3 4 5 6
--------------------
1|*****#*********
2|**************
3|*#*****2*******
4|**********!***
5|***1**********
6|****!**********



0 1 2 3 4 5 6
--------------------
1|*****#*********
2|**************
3|*#*****2*******
4|**********!***
5|***1**********
6|****!**********
*/