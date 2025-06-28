#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 40
#define MIN_SIZE 2
#define EMPTY_SPOT -1
#define LOOP_RESET 0
#define LOOP_BREAK 1
#define INITALIZE 0

#define FIRST_LOAD 0
#define DEBUG 1
#define LOAD_PLAY 2

int main(){
    int mapStatus = FIRST_LOAD;

    int height, width = INITALIZE;
    int maxArtifacts, numOfArtifacts = INITALIZE;
    int i, j = INITALIZE; 
    int loopCondition = LOOP_RESET;
    char input[100];
    int menuChoice = INITALIZE;
    int userX, userY = INITALIZE;
    int pointCounter = INITALIZE;
    

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


    /*Print the map - without anything extra*/
    loopCondition = LOOP_RESET;
    
    while(!loopCondition){
        /*if map status is not first load(this can happen after the first load display)*/
        
        
        /*TODO, if an artifact is found(user x and y match a artifact) print ex. You have found an artifact! (Artifact code: T011, 2 points)*/


        /*check if user x and y match, then find the code, then check if the letter in the code is upper(2 points) or lower(1 point), display these and add to point counter*/

        printf("Map:\n\t");
        for (i = 0; i < width; i++) {
            printf("%d", i / 10);
        }
        printf("\n\t");
        for (i = 0; i < width; i++) {
            printf("%d", i % 10);
        }
        printf("\n\t");
        for (i = 0; i < width; i++) {
            printf("-");
        }
        printf("\n");
        
        if(mapStatus == FIRST_LOAD){
          for (i = 0; i < height; i++) {
            if (i < 10){
                printf("     0%d|", i);
            } else {
                printf("     %2d|", i);
            }
            for (j = 0; j < width; j++) {
                printf(" ");
            }
            printf("\n");
            }  
        }
        if (mapStatus == LOAD_PLAY){
            for (i = 0; i < height; i++){
                printf("     %2d", i);
                for(j=0; j < width; j++){
                    if (i == userX && j == userY){
                        if(arr[i][j] != EMPTY_SPOT){
                            printf("!");
                        } else {
                            printf("x");
                        }
                    } else {
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
        if (mapStatus == DEBUG){
            for (i = 0; i < height; i++) {
                printf("     %2d|", i);
                for (j = 0; j < width; j++) {
                    /*if array point = user point => "!"*/
                    /*if array EMPTY AND user point => "x"*/
                    if (arr[i][j] != EMPTY_SPOT) {
                        printf("?");
                    } else { /*if empty and not user point*/
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
        
        /*if all variables are found display a message and exit - maybe a found variables variable and when it equals the numOfVariable*/
        int foundAll = 1;
        for (i = 0; i < height; i++){
            for (j = 0; j < width; j++){
                if (arr[i][j] != EMPTY_SPOT){
                    foundAll = 0;
                    break;
                }
            }
            if (!foundAll){
            break;
            }
        }

        if (foundAll){
            printf("\nCongratulations! You have found all artifacts.\nTotal points: %d\n", pointCounter);
            loopCondition = LOOP_BREAK; /*exit main loop*/
        }

        printf("1: Dig at a spot\n2:Exit\n3:Activate debug mode\n ->");
        scanf("%d", &menuChoice);
        switch(menuChoice){
            case 1:
                mapStatus = LOAD_PLAY;
                printf("x = ");
                scanf("%d", &userX);
                printf("\ny = ");
                scanf("%d", &userY);
                
                if (userX < 0 || userX >= height || userY < 0 || userY >= width){
                    printf("Error: coordinates out of bounds, BAD BAD\n");
                    continue;
                }
                
                int artifactIndex = arr[userX][userY];
                if (artifactIndex != EMPTY_SPOT){
                    char *foundCode = artifactCodeIndex[artifactIndex];
                    int pointsEarned = isupper(foundCode[0]) ? 2 : 1;
                    printf("You have found an artifact! (Artifact code: %s, %d point%s)\n", foundCode, pointsEarned, pointsEarned > 1 ? "s" : "");
                    pointCounter += pointsEarned;
                    arr[userX][userY] = EMPTY_SPOT;
                }
                continue;
            case 2:
                for (i = 0; i < height; i++) {
                    free(arr[i]);
                }
                free(arr);
                for (i = 0; i < numOfArtifacts; i++) {
                    free(artifactCodeIndex[i]);
                }  
                free(artifactCodeIndex);
                free(artifactCode);
                return EXIT_SUCCESS;
            case 3:
                printf("Debug mode activated \n\n");
                mapStatus = DEBUG;
                continue;
        }
    } 
return EXIT_SUCCESS;
}

/*
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
*/