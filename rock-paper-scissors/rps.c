#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//  Possible options
enum options
{
    /* 0: */ rock, 
    /* 1: */ paper,
    /* 2: */ scissors,
};

//  Possible game outcomes
enum result {win, lose, tie};

//  Returns winner.
//  Might as well structure better these statements.
enum result checkWinner (  const int humanChoice, 
                    const int computerChoice )
{
    if ( humanChoice == 0 && computerChoice == 1 )
    {
        //  Computer wins: rock < paper
        printf("Computer wins!\n\n");
        return lose;
    }
        
    if ( humanChoice == 0 && computerChoice == 2 )
    {
        //  Human wins: rock > scissors
        printf("Human wins!\n\n");
        return win;
    }

    if ( humanChoice == 1 && computerChoice == 0 )
    {
        //  Human wins: paper > rock
        printf("Human wins!\n\n");
        return win;
    }

    if ( humanChoice == 1 && computerChoice == 2 )
    {
        //  Computer wins: paper < scissors
        printf("Computer wins!\n\n");
        return lose;
    }

    if ( humanChoice == 2 && computerChoice == 0 )
    {
        //  Computer wins: scissors > rock
        printf("Computer wins!\n\n");
        return lose;
    }

    if ( humanChoice == 2 && computerChoice == 1 )
    {
        //  Human wins: scissors > paper
        printf("Human wins!\n\n");
        return win;
    }

    //  Every other possible case is a tie
    if ( (humanChoice == 0 && computerChoice == 0) ||
         (humanChoice == 1 && computerChoice == 1) ||
         (humanChoice == 2 && computerChoice == 2) )
    { printf("Tie!\n\n"); return tie; }
}

int main()
{
    printf("Rock, paper, scissors! BO3\n\n");

    //  Init points
    int hP = 0; 
    int cP = 0;
    
    //  Number of rounds
    int rounds = 3;
    
    //  Rounds still to play or any player has not got to two points
    while( rounds != 0 || ( hP != 2 && cP != 2 ))
    {
        //  Generate random seed
        //  Consider the options as: {0: rock, 1: paper, 2: scissors}.
        srand( time(NULL) ); 
        //  Random number must be [0, 2]
        int computerChoice = rand() % (2 - 0 + 1) + 0;
        int humanChoice;

        bool validHumanChoice = false;

        //  Go on until human choice is valid
        while ( !validHumanChoice )
        {
            printf("Choose an option: (0) rock, (1) paper, (2) scissors: ");
            //  User input. PLEASE only numbers. A character will fuck up the program
            scanf("%d", &humanChoice);
            
            //  Obtain the two player's choices
            switch ( humanChoice )
            {
                case 0:
                    printf("Your choice: rock\n");
                    validHumanChoice = true;
                    break;
                case 1:
                    printf("Your choice: paper\n");
                    validHumanChoice = true;
                    break;
                case 2:
                    printf("Your choice: scissors\n");
                    validHumanChoice = true;
                    break;
                default:
                    printf("Invalid option! Try again.\n");
                    break;
            }

            switch ( computerChoice )
            {
                case 0:
                    printf("Computer choice: rock\n");
                    break;
                case 1:
                    printf("Computer choice: paper\n");
                    break;
                case 2:
                    printf("Computer choice: scissors\n");
                    break;
                default:
                    break;
            }       
        }   
   
        //  Once the player picks a valid option, this block runs.
        if ( validHumanChoice )
        {
            //  Decide winner. Increments points or not.
            switch (  checkWinner(humanChoice, computerChoice) )
            {
                case win:
                    //  human wins
                    hP++; break;
                case lose:
                    //  computer wins
                    cP++; break;
                case tie:
                    //  no increment
                    break;
                default:
                    break;
            }

            printf("Your points: %d\n", hP);
            printf("Computer points: %d\n\n", cP);

            rounds--;
        }
        
    }
    printf("Game over!\n");

    //  If game has been played at least once
    if ( cP != 0 && hP != 0 )
    {
        //  Wins whoever got most points
        if ( cP > hP ) printf("Computer wins!\n");
        else { printf("Human wins!\n"); }
    }
    return 0;
}
