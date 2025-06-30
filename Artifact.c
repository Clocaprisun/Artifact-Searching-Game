#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

/* constant that Initalizes variables */
#define INITALIZE 0
/* loop variables for reseting and breaking loops */
#define LOOP_RESET 0
#define LOOP_BREAK 1
/* the max and min for the map */
#define MAX_SIZE 40
#define MIN_SIZE 2
/* array checkers, numeral values that represent certain events in the array */
#define EMPTY_SPOT -1
#define FOUND_TREASURE -2
#define OUT_OF_RANGE -3
/* menu instance: changes the output of the map depending on user choice/first instance */
#define FIRST_LOAD 0
#define DEBUG 1
#define LOAD_PLAY 2
#define EXISTS 1
int main(){
    /* game state control*/
    int mapStatus = FIRST_LOAD; /* controls map display mode*/
    int loopCondition = LOOP_RESET; /* controls exit of main game loop*/
    int menuChoice = INITALIZE;
    /*map dimesnsions*/
    int height = INITALIZE; int width = INITALIZE;
    /*artifact variables*/
    int maxArtifacts = INITALIZE;
    int numOfArtifacts = INITALIZE;
    int foundArtifacts = INITALIZE;
    int pointCounter = INITALIZE; /* counts total points */ int points = INITALIZE; /* amount of points (1 or 2)*/
    /*loop and temporary usage*/
    int i = INITALIZE; int j = INITALIZE; 
    int artifactIndex = INITALIZE;
    int closestArtifact = INITALIZE; /* stores minimum distance to the nearest artifact*/
    int codeInDatabase = INITALIZE;
    /* user input for searching*/
    int userX = INITALIZE; int userY = INITALIZE;
    /*artifact placement*/
    int *artifactx; int *artifacty;
    int *distance;
    /* game maps*/
    int **internalDigsite; int **digSite;
    /*code management - */
    char **artifactCodeIndex;
    char *foundCode; char *artifactCode;
    char *input; /* input buffer */

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
        loopCondition = LOOP_BREAK;
    }


    /*creates a 2d array based on height and width - stores where artifacts are placed and their index*/
    internalDigsite = malloc(height * sizeof(int *));
    for (i = 0; i < height; i++) {
        *(internalDigsite + i) = malloc(width * sizeof(int));
        for (j = 0; j < width; j++) {
        *(*(internalDigsite + i) + j) = EMPTY_SPOT;
        }
    }
    /*user dig history*/
    digSite = malloc(height * sizeof(int *));
    for (i = 0; i < height; i++){
        *(digSite + i) = malloc(width * sizeof(int));
        for (j = 0; j < width; j++) {
            *(*(digSite + i) + j) = EMPTY_SPOT;  /* initially nothing dug*/
        }
    }
    /*creates 2 arrays for x, y of artifacts - used for determining how far the closest artifact is compared to a users guess*/
    artifactx = malloc(numOfArtifacts * sizeof(int)); artifacty = malloc(numOfArtifacts * sizeof(int));
    

    /*creates the artifact amount via user input*/
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
            printf("Code for artifact %d: ", i + 1); 
            scanf("%4s", artifactCode);
            /*uses ctype library; parses the artifact code into unsigned chars to check if they follow the correct order of types including EOF /0 (the reason it is size 5 and not 4)*/
            if (!isalpha((unsigned char) * (artifactCode)) || !isdigit((unsigned char) * (artifactCode + 1)) || !isdigit((unsigned char) * (artifactCode + 2)) || !isdigit((unsigned char) * (artifactCode + 3)) || ((unsigned char) * (artifactCode + 4)) != '\0') {
            printf("Error: input is in incorrect format, re-enter with a valid code (ex. S743, y824)\n");
            continue;
        } else {
            loopCondition = LOOP_BREAK;
        }

        /*checks if an artifact code is already in the artifact code index */
        for (j = 0; j < i; j++) {
            if (strcmp(artifactCode, *(artifactCodeIndex + j)) == 0) { /*uses string compare to compare the entered code with each code in the index and flags duplicatesssssss*/
                codeInDatabase = EXISTS;
                break;
            }
        }
        /*asks the user again if the code is invalid instead of copying it to the index*/
        if(codeInDatabase){
            printf("Error: code already exists in database, re-enter a different valid code (ex. S743, y824)\n");
            continue;
        }
        strcpy(*(artifactCodeIndex + i), artifactCode); /*string copy to copy the code into the index*/
        break;
        }
    }
    

    /*put artifacts into random spot in the 2d array - checks if the spot if empty*/
    for (i = 0; i < numOfArtifacts; i++){
        *(artifacty + i) = rand() % (height); *(artifactx + i) = rand() % (width); /* random % (max - min + 1) + min | min = 0 */
        if (*(*(internalDigsite + *(artifacty + i)) + *(artifactx + i)) == EMPTY_SPOT) { /* if the random spot is empty, this is where the artifact goes*/
            *(*(internalDigsite + *(artifacty + i)) + *(artifactx + i)) = i;
        } else { /* if the random spot already has an artifact, retry*/
            i--;
        }
    }


    /*Print the map - without anything extra*/
    loopCondition = LOOP_RESET;
    /*prints the map header - this never changes so yeah*/
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
        /*on first load just print empty spaces for map :D*/
        if(mapStatus == FIRST_LOAD){
          for (i = 0; i < height; i++) {
            if (i < 10){
                printf("     0%d|", i); /*if the number is les than 10, adds a 0 for better readability*/
            } else {
                printf("     %2d|", i);
            }
            for (j = 0; j < width; j++) {
                printf(" ");
            }
            printf("\n");
            }  
        } else {
            for (i = 0; i < height; i++) {
                printf("     %2d|", i);
                for (j = 0; j < width; j++) {
                    /*if user is in debug mode, print map WITH hidden artifacts*/
                    if (mapStatus == DEBUG && (*(*(internalDigsite + i) + j) != EMPTY_SPOT) && (*(*(internalDigsite + i) + j) != FOUND_TREASURE) && (*(*(digSite + i) + j) == EMPTY_SPOT)){ /*if not empty(treasure) and unfound*/ 
                        printf("?");
                    } else if (*(*(digSite + i) + j) == FOUND_TREASURE){
                        printf("!");
                    } else if (*(*(digSite + i) + j) >= 1 && (*(*(digSite + i) + j) <= 9)) { /*if the dig spot is a number between 1-9 print(this is the closest aritfact)*/
                        printf("%d",*(*(digSite + i) + j));
                    } else if (*(*(digSite + i) + j) == OUT_OF_RANGE){ /*if the user chooses a spot that is beyond 9 spaces*/
                        printf("#");
                    } else {
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }

        
        /*if all variables are found display a message and exit*/
        for (i = 0; i < height; i++){
            for (j = 0; j < width; j++){
                if (*(*(internalDigsite + i) + j) == FOUND_TREASURE){
                    foundArtifacts ++;
                }
            }  
        }
        /*if the amount of found artifacts is equal to all artifacts - you found all of them yay*/
        if (foundArtifacts == numOfArtifacts){
            printf("\nCongratulations! You have found all artifacts.\nTotal points: %d\n", pointCounter);
            loopCondition = LOOP_BREAK; /*exit main loop*/
            continue;
        }
        /* main switch menu logic*/
        printf("1: Dig at a spot\n2: Exit\n3: Activate debug mode\n -> ");
        scanf("%d", &menuChoice);
        while (getchar() != '\n'); /*consumes newline - does a little error without it*/
        switch(menuChoice){
            case 1:
                mapStatus = LOAD_PLAY; /*makes mapStatus not equal debug or first load*/
                /*user x and y inputs - check if they are within the bounds of the map*/
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
                

                /*extra cases based on user x and y - found artifact(how many points? - checks if code starts with a upper or lower)*/
                artifactIndex = *(*(internalDigsite + userY) + userX);
                if (artifactIndex != EMPTY_SPOT && artifactIndex != FOUND_TREASURE){
                    foundCode = *(artifactCodeIndex + artifactIndex);
                    points = isupper((unsigned char) * (foundCode)) ? 2 : 1; /*parses foundCode to unsigned char; is it upper? if yes points = 2; if no points = 1*/
                    printf("You have found an artifact! (Artifact code: %s, %d point(s))\n", foundCode, points);
                    pointCounter += points; /*add point counter by the amount of points*/
                    *(*(internalDigsite + userY) + userX) = FOUND_TREASURE; *(*(digSite + userY) + userX) = FOUND_TREASURE; /*flags this spot as a found artifact*/
                } else if (*(*(digSite + userY) + userX) == FOUND_TREASURE){ /*checks if the artifact was already found*/
                    printf("You have already found this artifact\n");
                } else if (*(*(digSite + userY) + userX) != EMPTY_SPOT){ /*checks if the spot was already dug(not an artifact)*/
                    printf("You already dug here\n");
                } else {
                    /*calculates the distance between user coord and closest artifact*/
                    distance = malloc(numOfArtifacts * sizeof(int));
                    for (i = 0; i < numOfArtifacts; i++){
                        *(distance + i) = (int)(sqrt((userX - *(artifactx + i)) * (userX - *(artifactx + i)) + (userY - *(artifacty + i)) * (userY - *(artifacty + i))));   
                    }
                    closestArtifact = *(distance); /*makes closest artifact the first index of distance array*/
                    for (i=0; i < numOfArtifacts; i++){
                        if (*(distance + i) < closestArtifact){ /*if index i is less than closestArtifact - replace it with index i*/
                            closestArtifact = *(distance + i);
                        }
                    }
                    free(distance);
                    if (closestArtifact <= 9){ /*if the closest artifact is within the 1-9 range, records the coordinate in the digsite arrays*/
                        *(*(internalDigsite + userY) + userX) = closestArtifact;
                        *(*(digSite + userY) + userX) = closestArtifact;
                    } else if (closestArtifact > 9) { /*if the closest is larger than 9 - becomes out of range*/
                        *(*(internalDigsite + userY) + userX) = OUT_OF_RANGE;
                        *(*(digSite + userY) + userX) = OUT_OF_RANGE;
                    }
                }
                continue;
            case 2:
                loopCondition = LOOP_BREAK; /*breaks out of big loop and goes to freeing memory*/
                break;
            case 3:
                printf("Debug mode activated \n\n");
                mapStatus = DEBUG; /*changes mapStatus to debug mode - when looping back it will include debug stuff*/
                continue;
        }
    } 
    /*free the memory from its cages*/
    for (i = 0; i < height; i++) {
        free(*(internalDigsite + i));
        free(*(digSite + i));
    }
    free(digSite);
    free(internalDigsite);
    for (i = 0; i < numOfArtifacts; i++) {
        free(*(artifactCodeIndex + i));
    }  
    free(artifactCodeIndex);
    free(artifactCode);
    printf("Exiting...");
    return EXIT_SUCCESS;
}