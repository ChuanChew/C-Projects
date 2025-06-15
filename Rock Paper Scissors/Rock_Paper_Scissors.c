#include <stdio.h>
#include <time.h>
#include <string.h> //Use to include string manipulation functions

void Gameboard(int P1Score,int CPUScore) // Displays the game scoreboard with current scores
{
    printf("==================================\n");
    printf(" ROCK        PAPER       SCISSORS\n");
    printf("==================================\n");
    printf("P1                             CPU\n");
    printf("%d                              %d\n", P1Score,CPUScore);
    return;
}

int Score() // Asks the player to choose a "best out of" score (1, 3, or 5)
{
    int Playerchoice, score;
    int validInput = 0;
    printf("Best out of (Choose 1, 2 or 3):\n");
    printf("1. 1\n2. 3\n3. 5\n");

    while (!validInput) // Keep prompting until a valid choice (1-3) is entered
    {
        printf("Choice: ");
        scanf("%d", &Playerchoice);
        if (Playerchoice >= 1 && Playerchoice <= 3)
            validInput = 1;
        else
            printf("Please choose from 1 - 3 only!\n");
    }

    switch (Playerchoice) // Set max score based on player selection
    { 
    case 1: score = 1; break;
    case 2: score = 3; break;
    case 3: score = 5; break;
    }
    return score;
}

int Playerchoice() // Gets and validates the player's selection for each round
{
    int P1choice, valid = 0; 
    printf("1. Rock\n2. Paper\n3. Scissors\n"); 
    while (!valid) // Loop until valid choice (1–3) is entered
    {
        printf("Choice: ");
        scanf("%d", &P1choice);
        if (P1choice >= 1 && P1choice <= 3)
            valid = 1;
        else
            printf("Please choose from 1 - 3 only!\n");
    }
    return P1choice;
}

int CPUchoice() // Randomly generates CPU choice using rand() between 1 to 3
{
    int RNG;
    RNG = (rand() % 3) + 1; //variable RNG store in integer data to be used in random function (rand()) to roll and generate a random number from 1 - 3
    return RNG; // 1 = Rock, 2 = Paper, 3 = Scissors
}

int Result(int P1Selection, int CPUSelection) // Determines outcome of the round and prints result
{
    char *choices[] = {"", "ROCK", "PAPER", "SCISSORS"}; //4 string of array that display player or cpu choice from 1 to 3. Example 1 = ROCK
    int outcome;
    int outcomes[4][4] = { //matrix of player choices. Rows = P1 selection, Columns = CPU selection 
    {0}, // not used
    {0, 0, 2, 1}, // P1 = ROCK
    {0, 1, 0, 2}, // P1 = PAPER
    {0, 2, 1, 0} // P1 = SCISSORS
    }; // Outcome matrix [P1][CPU]: 0 = Draw, 1 = P1 Win, 2 = CPU Win
    outcome = outcomes[P1Selection][CPUSelection]; //Primary array on left [] represent player choice while right [] secondary array is CPU choice
    printf("         %s vs %s\n", choices[P1Selection], choices[CPUSelection]); // Display choice comparison
    switch (outcome) // Display result based on outcome
    {
    case 0: //Both choices are same
        printf("              DRAW!\n");
        break;
    case 1: //When P1 wins
        printf("            P1 WIN!\n");
        break;
    case 2: //When CPU wins
        printf("            CPU WIN!\n");
        break;
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Flush buffer
    printf("    Press Enter to continue...\n\n"); // Pause for player to view the round result
    getchar(); // Wait for Enter
    return outcome;
}

char AskReplay(int P1Score, int CPUScore, int Maxscore) // Displays final winner and asks if player wants to replay
{   
    int Redecide = 0;
    char again;
    if (P1Score == Maxscore) 
    {
        printf("         WINNER: P1\n");
    }
    else if (CPUScore == Maxscore)
    {
        printf("         WINNER: CPU\n");
    } // Show winner of the match
    printf("        Play again? YES / NO\n");
    printf("        Please key in Y/N\n");
    while (Redecide == 0) // Loop until valid response (Y/N) is given
    {
        scanf(" %c", &again); // Leading space clears leftover newline
        again = toupper(again);
        if (again == 'Y' || again == 'N')
        {
            Redecide = 1;
        }
        else
        {
            printf("        Please key in Y/N!\n");
        }
    } //Check player response for next game, terminate loop when player answer "Y or N"
    return again; // Return user decision
}

int main() // Main game loop
{
    int P1Score = 0, CPUScore = 0, End = 0;
    int Maxscore, P1Selection, CPUSelection, Outcome;
    char Replay;
    srand(time(0)); //Generate a random value at current time
    do
    {
        Gameboard(P1Score, CPUScore); // Show initial gameboard
        Maxscore = Score(); // Set win condition
        while (End == 0)
        {
            Gameboard(P1Score, CPUScore); // Display current scores
            P1Selection = Playerchoice(); //Record down value of 1,2 or 3 from player selection in Playerchoice function
            CPUSelection = CPUchoice(); //RNG selection since its CPU
            Outcome = Result(P1Selection, CPUSelection); //Outcome receive value 1 or 2 from result function
            switch (Outcome)
            {
            case 1: P1Score++; break; // P1 wins this round
            case 2: CPUScore++; break; // CPU wins this round
            default: break;
            }
            if (P1Score == Maxscore || CPUScore == Maxscore)
            {
                End = 1; //When either player reach max score, exit the game loop
            }
        }
        Gameboard(P1Score, CPUScore); //Display final scores
        Replay = AskReplay(P1Score, CPUScore, Maxscore); //Ask player for another game
        P1Score = CPUScore = End = 0; //Reset game to default setting for next game
    } while (Replay == 'Y');
    printf("        THANK YOU!\n");
    return 0;
}