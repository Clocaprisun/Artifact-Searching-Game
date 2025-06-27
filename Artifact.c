#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 40
#define MIN_SIZE 2
int menu(){
    printf("THIS IS A MENU AHAHAHAHHA");
    return 0;
}

int main(){
    /*ask user for height and width of map*/
    int height = 0; int width = 0;
    int i, j, loop = 0;
    int maxArtifacts, numOfArtifacts;
    
    while(loop == 0){
        int stupidvar = 0; /*checks validity of variables(are they integers?) */
        printf("Enter map height: "); if (scanf(" %d", &height) == 1) stupidvar = 1;
        printf("Enter map width: ");  if (scanf(" %d", &width)  == 1) stupidvar = 1;
        if (stupidvar == 0){
            printf("Error: input is in incorrect format, re-enter with an integer value\n");
            height = 0; width = 0; /*reset variables*/
            continue;
        }
        /*checks if height is out of bounds*/
        if (height < MIN_SIZE || height > MAX_SIZE) {
            printf("Error: height out of bounds - enter an integer between %d - %d\n", MIN_SIZE, MAX_SIZE);
            continue;
        }
        /*checks if width is out of bounds*/
        if (width < MIN_SIZE || width > MAX_SIZE) {
            printf("Error: width out of bounds - enter an integer between %d - %d\n", MIN_SIZE, MAX_SIZE);
            continue;
        }
        loop = 1; /*exit loop*/
    }

    /*creates a 2d array based on height and width*/
    int **arr;
    arr = malloc(height * sizeof(int *));
    for (i = 0; i < height; i++) {
        *(arr + i) = malloc(width * sizeof(int));
    }

    /*creates the artifact amount*/
    maxArtifacts = (height * width); /*upper bound is height * width*/
    numOfArtifacts = 0;
    loop = 0;
    while(loop == 0){
        /*asks user for an amount of artifacts, checks validity*/
        printf("Enter the number of artifacts: "); if (scanf("%d", &numOfArtifacts) != 1){
            printf("Error: input is in incorrect format, re-enter with an integer value \n");
            numOfArtifacts = 0;
            continue;
        }
        /*checks if number of artifacts is above one and less than max*/
        if (numOfArtifacts < 1 || numOfArtifacts > maxArtifacts){
            printf("Error: number of artifacts out of bounds - enter a number between 1 - %d\n", maxArtifacts);
            continue;
        }
        loop = 1;
    }

    /* user adds a code to the artifact(s)*/
    char *artifactCode = malloc(5 * sizeof(char)); /*an array to store the artifact code - useful for validity and such and such*/
    char *artifactCodeIndex = malloc(numOfArtifacts * sizeof(char)); /*an array to store the artifact codes*/
    for (i = 0; i < numOfArtifacts; i++){
        /*user input for code*/
        printf("Code for atrifact %d:", i + 1); scanf("%s", artifactCode);
        /*checks if code is in format ex. char digit digit digit EOF-symbol*/
        if (!isalpha(*(artifactCode)) || !isdigit(*(artifactCode + 1)) || !isdigit(*(artifactCode + 2)) || !isdigit(*(artifactCode + 3)) || *(artifactCode + 4) != '\0') {
            printf("Error: input is in incorrect format, re-enter with a valid code (ex. S743, y824)\n");
            i--;
            continue;
        }
        /*checks the index if the code exists already or not(iteration)*/
        for (j=0; j < i; j++){
            if(*(artifactCodeIndex + j) == *(artifactCode)){
                printf("Error: code already exists in database, re-enter a different valid code (ex. S743, y824)\n");
                i--;
                
            }
        } 
        printf("Penis");
        *(artifactCodeIndex + i) = *(artifactCode); /*stores the first character(since the only thing needed later is if it is upper or lower case)*/
    }
    printf("Penis");

    
    /*put artifacts into random spot in the 2d array*/
    for (i = 0; i < numOfArtifacts; i++){
        int artifactx = rand() % (height); int artifacty = rand() % (width); /* random % (max - min + 1) + min | min = 0 */
        if (*(*(arr + artifactx) + artifacty) == 0){  /*same as arr[artifactx][artifacty], checks if the spot is empty(no artifacts are there); TODOOOOO compares only the first char lol crazy*/
            /*adds artifact to that spot
            TODOOOOO, only ads the first character right now i am lazy, logic is there lol*/
            *(*(arr + artifactx) + artifacty) = *(artifactCodeIndex + i);
        } else {
            i--;
        }
    }

    printf("Penis");

    /*Prints menu and collects choice*/
    menu();
    /*dig site main part*/
    
return 0;
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