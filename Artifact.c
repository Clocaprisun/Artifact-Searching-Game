#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 40
#define MIN_SIZE 2

#define EMPTY_SPOT -1
#define FOUND_TREASURE -2
#define OUT_OF_RANGE -3

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
    char *input;
    input = malloc(100 * sizeof(int *));
    int menuChoice = INITALIZE;
    int userX, userY = INITALIZE;
    int pointCounter = INITALIZE;
    int distance;
    

    /*ask user for height and width of map*/
    while (!loopCondition){
        printf("Enter map height (2 - 40): "); 
        while (fgets(input, sizeof(input), stdin)){
            if (sscanf(input," %d", &height) == 1){
                break;
            } else {
                printf("Error: height input is in incorrect format, re-enter with an integer value\nEnter map height (2 - 40): ");
            }
        }
        /*checks if height is out of bounds*/
        if (height < MIN_SIZE || height > MAX_SIZE) {
            printf("Error: height out of bounds - enter an integer between %d - %d\n", MIN_SIZE, MAX_SIZE);
            continue;
        }
        

        printf("Enter map width (2 - 40): "); 
        while (fgets(input, sizeof(input), stdin)){
            if (sscanf(input," %d", &width) == 1){
                break;
            } else {
                printf("Error: width input is in incorrect format, re-enter with an integer value\nEnter map width (2 - 40): ");
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

    int **digSite = malloc(height * sizeof(int *));
    for (i = 0; i < height; i++){
        *(digSite + i) = malloc(width * sizeof(int));
        for (j = 0; j < width; j++) {
            *(*(digSite + i) + j) = EMPTY_SPOT;  // initially nothing dug
        }
    }
    
    /*creates the artifact amount*/
    maxArtifacts = (height * width); /*upper bound is height * width*/
    loopCondition = LOOP_RESET;
    while(!loopCondition){
        /*asks user for an amount of artifacts, checks validity*/
        printf("Enter the number of artifacts (1 - %d): ", maxArtifacts); 
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
            printf("Code for atrifact %d: ", i + 1); 
            scanf("%4s", artifactCode);

            if (!isalpha(*(artifactCode)) || !isdigit(*(artifactCode + 1)) || !isdigit(*(artifactCode + 2)) || !isdigit(*(artifactCode + 3)) || *(artifactCode + 4) != '\0') {
            printf("Error: input is in incorrect format, re-enter with a valid code (ex. S743, y824)\n");
            continue;
        }

        /*FIX THIS BRUVV */
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
                printf("     %2d|", i);
                for(j=0; j < width; j++){
                    if(*(*(digSite + i) + j) == FOUND_TREASURE){
                        printf("!");
                    } else if (*(*(digSite + i) + j) >= 1 && *(*(digSite + i) + j) <= 9){
                        printf("%d", *(*(digSite + i) + j));
                    } else if (*(*(digSite + i) + j) == OUT_OF_RANGE){
                        printf("#");
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
                    if (*(*(digSite + i) + j) == FOUND_TREASURE){
                        printf("!");
                    } else if (*(*(digSite + i) + j) >= 1 && (*(*(digSite + i) + j) <= 9)) {
                        printf("%d",*(*(digSite + i) + j));
                    } else if (*(*(digSite + i) + j) == OUT_OF_RANGE){
                        printf("#");
                    } else if (*(*(arr + i) + j) != EMPTY_SPOT && (*(*(arr + i) + j) != FOUND_TREASURE)){ /*if empty and not user point*/
                        printf("?");
                    } else {
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
                if (*(*(arr + i) + j) != EMPTY_SPOT){
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

        printf("1: Dig at a spot\n2: Exit\n3: Activate debug mode\n -> ");
        scanf("%d", &menuChoice);
        while (getchar() != '\n');
        switch(menuChoice){
            case 1:
                mapStatus = LOAD_PLAY;
                printf("x = "); 
                    while (fgets(input, 100, stdin)){
                        if (sscanf(input," %d", &userX) == 1){
                            break;
                        } else {
                        printf("Error: x input is in incorrect format, re-enter with an integer value\nx = ");
                    }
                }
                printf("\ny = "); 
                    while (fgets(input, 100, stdin)){
                        if (sscanf(input," %d", &userY) == 1){
                            break;
                        } else {
                        printf("Error: y input is in incorrect format, re-enter with an integer value\ny = ");
                    }
                }
                
                if (userX < 0 || userX >= height || userY < 0 || userY >= width){
                    printf("Error: coordinates out of bounds\n");
                    continue;
                }
                
                int artifactIndex = *(*(arr + userY) + userX);
                if (artifactIndex != EMPTY_SPOT && artifactIndex != FOUND_TREASURE){
                    char *foundCode = *(artifactCodeIndex + artifactIndex);
                    int pointsEarned = isupper(*(foundCode)) ? 2 : 1;
                    printf("You have found an artifact! (Artifact code: %s, %d point%s)\n", foundCode, pointsEarned, pointsEarned > 1 ? "s" : "");
                    pointCounter += pointsEarned;
                    *(*(arr + userY) + userX) = FOUND_TREASURE;
                    *(*(digSite + userY) + userX) = FOUND_TREASURE;
                } else if (*(*(digSite + userY) + userX) == FOUND_TREASURE){
                    printf("You have already found this artifact\n");
                } else if (*(*(digSite + userY) + userX) != EMPTY_SPOT){
                    printf("You already dug here\n");
                } else {
                    for (i = 0; i < height; i++){
                        for (j = 0; j < width; j++){
                            if ((*(*(arr + i) + j) != EMPTY_SPOT) && (*(*(arr + i) + j) != FOUND_TREASURE)){
                                int dx = userX - i;
                                int dy = userY - j;
                                distance = distance = (int)round(sqrt((userX - artifactX) * (userX - artifactX) + (userY - artifactY) * (userY - artifactY)));
;
                            }
                        }
                    }
                }
                if (distance <= 9){
                    *(*(arr + userY) + userX) = distance;
                    *(*(digSite + userY) + userX) = distance;
                } else {
                    *(*(arr + userY) + userX) = OUT_OF_RANGE;
                    *(*(digSite + userY) + userX) = OUT_OF_RANGE;
                }
                continue;
            case 2:
                for (i = 0; i < height; i++) {
                    free(*(arr + i));
                    free(*(digSite + i));
                }
                free(digSite);
                free(arr);
                for (i = 0; i < numOfArtifacts; i++) {
                    free(*(artifactCodeIndex + i));
                }  
                free(artifactCodeIndex);
                free(artifactCode);
                printf("Exiting...");
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



- it always accepts the case input when you dig, i will press 1 for the menu and it will do an error message for x = and then let me ask after
- there is a space between x and y inputs
- have to have the number of spaces closest to the nearest artifact, ex. if i choose a space 2 away it will have a 2, formula for distance 
        - square root((player input x - artifact y)^2 + (player input y - artifact y)^2)
- when an artifact is found it stops showing up on the debug mode, instead it should chnage to a !
- if a space is 10 away from any artifct and user guesses it there is a #
- it only shows the current dig, make an array that stores digs and then compare those
*/