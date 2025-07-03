# Artifact Searching Game
Artifact searching game where the user specifies the game map and can guess coordinates where treasure may be 
in c language using pointers and pointer arithmetic

## Features
- user input
    - height and length of game map
    - amount of artifacts to be found - these are radomly placed in the game map and the user does not know where they are
    - artifact codes (must be in this format: S765, u475 etc) 
      - give 2 points if they start with an upper case letter otherwise 1 point

- game map
    - you can guess a coordinate to find treasure
    - if the guess is 10 or more away a # is displayed on the game board
    - if the guess is under 10 a number corresponding to how close the closest artifact is, is displayed
    - if an artifact is found a ! is displayed

- debug mode
    - you can see where artifacts are and if the user has found them or not
    - you can see everything from normal game map printing
 
- if all treasure is found the game exists, points are calculated based on artifact code and displayed

## Folder/File Structure 

- /src
  - Artifact.c
  - Makefile
