#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define INITALIZE 0

#define LOOP_RESET 0
#define LOOP_BREAK 1

#define MAX_SIZE 40
#define MIN_SIZE 2

#define EMPTY_SPOT -1
#define FOUND_TREASURE -2
#define OUT_OF_RANGE -3

#define FIRST_LOAD 0
#define DEBUG 1
#define LOAD_PLAY 2

int main(){
    int mapStatus = FIRST_LOAD;
    int height = INITALIZE;
    int width = INITALIZE;
    int maxArtifacts = INITALIZE;
    int numOfArtifacts = INITALIZE;
    int i = INITALIZE; 
    int j = INITALIZE; 
    int loopCondition = LOOP_RESET;
    int menuChoice = INITALIZE;
    int userX = INITALIZE; 
    int userY = INITALIZE;
    int pointCounter = INITALIZE;
    int pointsEarned = INITALIZE;
    int artifactIndex = INITALIZE;
    int foundAll = INITALIZE;
    int min = INITALIZE;
    int exists = INITALIZE;
    int *artifactx;
    int *artifacty;
    int *distance;
    char *foundCode;
    int **arr;
    int **digSite;
    char *artifactCode;
    char **artifactCodeIndex;
    char *input;
    
    input = malloc(100 * sizeof(int *));

    /*ask user for height and width of map*/
    while (!loopCondition){
        printf("Enter map height (2 - 40): "); 
        while (fgets(input, 100, stdin)){
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
        while (fgets(input, 100, stdin)){
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
    arr = malloc(height * sizeof(int *));
    for (i = 0; i < height; i++) {
        *(arr + i) = malloc(width * sizeof(int));
        for (j = 0; j < width; j++) {
        *(*(arr + i) + j) = EMPTY_SPOT;
        }
    }

    digSite = malloc(height * sizeof(int *));
    for (i = 0; i < height; i++){
        *(digSite + i) = malloc(width * sizeof(int));
        for (j = 0; j < width; j++) {
            *(*(digSite + i) + j) = EMPTY_SPOT;  /* initially nothing dug*/
        }
    }

    artifactx = malloc(numOfArtifacts * sizeof(int)); artifacty = malloc(numOfArtifacts * sizeof(int));
    
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
    artifactCode = malloc(5 * sizeof(char)); /*an array to store the artifact code - useful for validity and such and such*/
    artifactCodeIndex = malloc(numOfArtifacts * sizeof(char *)); /*an array to store the artifact codes*/
    for (i=0; i<numOfArtifacts; i++){
        *(artifactCodeIndex + i) = malloc(5 * sizeof(char));
        loopCondition = LOOP_RESET;
        while(!loopCondition){
            printf("Code for atrifact %d: ", i + 1); 
            scanf("%4s", artifactCode);

            if (!isalpha((unsigned char) * (artifactCode)) || !isdigit((unsigned char) * (artifactCode + 1)) || !isdigit((unsigned char) * (artifactCode + 2)) || !isdigit((unsigned char) * (artifactCode + 3)) || ((unsigned char) * (artifactCode + 4)) != '\0') {
            printf("Error: input is in incorrect format, re-enter with a valid code (ex. S743, y824)\n");
            continue;
        } else {
            loopCondition = LOOP_BREAK;
        }

        /*FIX THIS BRUVV */
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
        *(artifacty + i) = rand() % (height); *(artifactx + i) = rand() % (width); /* random % (max - min + 1) + min | min = 0 */
        if (*(*(arr + *(artifacty + i)) + *(artifactx + i)) == EMPTY_SPOT) {
            *(*(arr + *(artifacty + i)) + *(artifactx + i)) = i;
        } else {
            i--;
        }
    }


    /*Print the map - without anything extra*/
    loopCondition = LOOP_RESET;
    while(!loopCondition){
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
        foundAll = 0;
        for (i = 0; i < height; i++){
            for (j = 0; j < width; j++){
                if (*(*(arr + i) + j) == FOUND_TREASURE){
                    foundAll ++;
                }
            }  
        }
        if (foundAll == numOfArtifacts){
            printf("\nCongratulations! You have found all artifacts.\nTotal points: %d\n", pointCounter);
            loopCondition = LOOP_BREAK; /*exit main loop*/
            continue;
        }

        menuChoice = 0;
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
                
                artifactIndex = *(*(arr + userY) + userX);
                if (artifactIndex != EMPTY_SPOT && artifactIndex != FOUND_TREASURE){
                    foundCode = *(artifactCodeIndex + artifactIndex);
                    pointsEarned = isupper((unsigned char) * (foundCode)) ? 2 : 1;
                    printf("You have found an artifact! (Artifact code: %s, %d point%s)\n", foundCode, pointsEarned, pointsEarned > 1 ? "s" : "");
                    pointCounter += pointsEarned;
                    *(*(arr + userY) + userX) = FOUND_TREASURE;
                    *(*(digSite + userY) + userX) = FOUND_TREASURE;
                } else if (*(*(digSite + userY) + userX) == FOUND_TREASURE){
                    printf("You have already found this artifact\n");
                } else if (*(*(digSite + userY) + userX) != EMPTY_SPOT){
                    printf("You already dug here\n");
                } else {
                    distance = malloc(numOfArtifacts * sizeof(int));
                    for (i = 0; i < numOfArtifacts; i++){
                        *(distance + i) = (int)(sqrt((userX - *(artifactx + i)) * (userX - *(artifactx + i)) + (userY - *(artifacty + i)) * (userY - *(artifacty + i))));   
                    }
                    min = 100;
                    for (i=0; i < numOfArtifacts; i++){
                        if (*(distance + i) < min){
                            min = *(distance + i);
                        }
                    }
                    free(distance);
                    if (min <= 9){
                        *(*(arr + userY) + userX) = min;
                        *(*(digSite + userY) + userX) = min;
                    } else if (min > 9) {
                        *(*(arr + userY) + userX) = OUT_OF_RANGE;
                        *(*(digSite + userY) + userX) = OUT_OF_RANGE;
                    }
                }
                
                continue;
            case 2:
                loopCondition = LOOP_BREAK;
                break;
            case 3:
                printf("Debug mode activated \n\n");
                mapStatus = DEBUG;
                continue;
        }
    } 
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
}