#include <stdio.h>
#include <time.h>
#include <string.h> //Use to include string manipulation functions

int Totalplayers, Playerscores[4], Player = 0; //Totalplayers = number of players playing the game, Playerscores = display all participant points, Player = Current player turn
char playernames[4][3], position[101][4], winner[4][7] = {" ", " ", " ", " "}; //playernames = Representation of participants, position = all placement number in gameboard, winner = Show winner message

void PlayerMenu() //Procedure to carry out multiplayer selection
{
    printf("Key in number of players: (2 - 4 Players)\n");
    do
    {
        scanf("%d", &Totalplayers);
        if (Totalplayers <= 1 || Totalplayers > 4) //Outcome whenever user choose a non viable option
        {
            printf("You can only have 2 to 4 players!\n");
            printf("Please key in valid number of players (2-4):\n"); //Prompt player to key in available options
        }
    } while (Totalplayers <= 1 || Totalplayers > 4); //Repeat multiplayer input whenever user choose non viable option

    while (getchar() != '\n'); //Clear the input buffer after scanf
    
    for (int i = 0; i < Totalplayers; i++) //Total loop determine by multiplayer (Totalplayers) input
    {
        sprintf(playernames[i], "P%d", i+1); //Initialize player name in string
        Playerscores[i] = 0; //Initialize player starting scores
    }
}

void Gameboard(char position[][4]) //Display gameboard state
{
    printf("\t\t\t\tSNAKE LADDER GAME\n");
    printf("+------+------+------+------+------+------+------+------+------+------+----------------+\n");
    printf("| %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | UP:            |\n", position[91], position[92], position[93], position[94], position[95], position[96], position[97], position[98], position[99], position[100]);
    printf("+------+------+------+------+------+------+------+------+------+------+ 88 moves to 95 |\n");
    printf("| %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | 68 moves to 78 |\n", position[81], position[82], position[83], position[84], position[85], position[86], position[87], position[88], position[89], position[90]);
    printf("+------+------+------+------+------+------+------+------+------+------+ 47 moves to 61 |\n");
    printf("| %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | 24 moves to 43 |\n", position[71], position[72], position[73], position[74], position[75], position[76], position[77], position[78], position[79], position[80]);
    printf("+------+------+------+------+------+------+------+------+------+------+  4 moves to 15 |\n");
    printf("| %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  |                |\n", position[61], position[62], position[63], position[64], position[65], position[66], position[67], position[68], position[69], position[70]);
    printf("+------+------+------+------+------+------+------+------+------+------+                |\n");
    printf("| %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | DOWN:          |\n", position[51], position[52], position[53], position[54], position[55], position[56], position[57], position[58], position[59], position[60]);
    printf("+------+------+------+------+------+------+------+------+------+------+ 93 moves to 62 |\n");
    printf("| %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | 71 moves to 59 |\n", position[41], position[42], position[43], position[44], position[45], position[46], position[47], position[48], position[49], position[50]);
    printf("+------+------+------+------+------+------+------+------+------+------+ 55 moves to 45 |\n");
    printf("| %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | 39 moves to 22 |\n", position[31], position[32], position[33], position[34], position[35], position[36], position[37], position[38], position[39], position[40]);
    printf("+------+------+------+------+------+------+------+------+------+------+ 12 moves to  7 |\n");
    printf("| %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  |                |\n", position[21], position[22], position[23], position[24], position[25], position[26], position[27], position[28], position[29], position[30]);
    printf("+------+------+------+------+------+------+------+------+------+------+                |\n");
    printf("| %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  |                |\n", position[11], position[12], position[13], position[14], position[15], position[16], position[17], position[18], position[19], position[20]);
    printf("+------+------+------+------+------+------+------+------+------+------+                |\n");
    printf("| %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  | %3s  |                |\n", position[1], position[2], position[3], position[4], position[5], position[6], position[7], position[8], position[9], position[10]);
    printf("+------+------+------+------+------+------+------+------+------+------+----------------+\n");
    printf("|SCOREBOARD:                       |\n");
    for (int i = 0; i < Totalplayers; i++)
    {
        printf("|%s: %-3d   %7s                 |\n", playernames[i], Playerscores[i], winner[i]); 
        //%-3d makes an fixed-width format (for at least 3 spaces, padded on the left with spaces if necessary) to prevent output string grows longer, causing the alignment of the right-side box to shift
    }
    printf("*----------------------------------*\n");
}

int Diceroll() //Random number generated from 1-6
{
    int Dice; //Dice variable record down the result of dice roll
    Dice = (rand() % 6) + 1; //variable Dice store in integer data to be used in random function (rand()) to roll and generate a random number from 1 - 6
    return Dice; //Return dice roll result to add in player scores
}

Multispot() //Operate whenever 2 or more player are in the same board position
{
    int Found = 0; //Check if other players except the current one are in the same position (TRUE(1) / FALSE (0))
    for (int i = 0; i < Totalplayers; i++)
    {
        if (i != Player && Playerscores[Player] == Playerscores[i]) //Check if index is not current Player turn and current player score is the same as another player score
        {
            Found = 1; //Another player shares the same position. Set Found as TRUE
            strcpy(position[Playerscores[Player]], playernames[i]); //Copy another playername to replace current playername before moving to next position
            break; //End loop
        }
    }

    if (Found == 0) //If there is no replacement of playername (FALSE)
    {
        sprintf(position[Playerscores[Player]], "%d", Playerscores[Player]); //Reset string of current position back to its original number in reference to integer data of current player
    }
}

void Ladder() //Special position effect to move current player to a different position
{
    switch (Playerscores[Player]) //Moving up or down the board depending on current player score
    {
    //Move UP any player landed on the following positions
    case 88:
        Playerscores[Player] = 95;
        printf("%s landed on 88! Move up to 95!\n", playernames[Player]);
        break;
    case 68:
        Playerscores[Player] = 78;
        printf("%s landed on 68! Move up to 78!\n", playernames[Player]);
        break;
    case 47:
        Playerscores[Player] = 61;
        printf("%s landed on 47! Move up to 61!\n", playernames[Player]);
        break;
    case 24:
        Playerscores[Player] = 43;
        printf("%s landed on 24! Move up to 43!\n", playernames[Player]);
        break;    
    case 4:
        Playerscores[Player] = 15;
        printf("%s landed on 4! Move up to 15!\n", playernames[Player]);
        break;
    //Move DOWN any player landed on the following positions
    case 93:
        Playerscores[Player] = 62;
        printf("%s landed on 93! Move down to 62!\n", playernames[Player]);
        break;
    case 71:
        Playerscores[Player] = 59;
        printf("%s landed on 71! Move down to 59!\n", playernames[Player]);
        break;
    case 55:
        Playerscores[Player] = 45;
        printf("%s landed on 55! Move down to 45!\n", playernames[Player]);
        break;
    case 39:
        Playerscores[Player] = 22;
        printf("%s landed on 39! Move down to 22!\n", playernames[Player]);
        break;
    case 12:
        Playerscores[Player] = 7;
        printf("%s landed on 12! Move down to 7!\n", playernames[Player]);
        break;
    default:
        break;
    }
}

void Playerturn() //Execute game mechanic of each player turn
{
    int number; //number shown from dice roll
    printf("Player %s press Enter to roll dice...\n", playernames[Player]);
    getchar(); //Prompts user to press enter to roll the dice
    number = Diceroll(); //Records down result obtain from Diceroll function
    printf("%s roll %d!\n", playernames[Player], number);

    Multispot(); //Execute function when 2 or more player are in the same board position
    Playerscores[Player] += number; //Add dice roll value to current player score
    Ladder(); //Function checks for player score landing in any special position
    if (Playerscores[Player] > 100) //Check for any player reaching scores beyond 100
    {
        Playerscores[Player] = 100; //Set current player score to 100 since there are no position number that are over 100
    }
    strcpy(position[Playerscores[Player]], playernames[Player]); //Copy current player name to mark on its new score position
}

void NextPlayer() //Move to next player turn
{
    if (Player == Totalplayers - 1 || Playerscores[Player] == 100) //Check whether player count is the last player or current player score has reach 100
    {
        Player = 0; //Reset player turn back to first player to begin another multiplayer rotation or an new game
    }
    else //FALSE condition outcome
    {
        Player++; //Increment player count by 1 to move to next player turn
    }
}

int win() //Check if any player has met win condition
{
    if (Playerscores[Player] == 100) //Check if current player score reach 100
    {
       strcpy(winner[Player], "WINNER!"); //Release output state to declare winning player
       Gameboard(position); //Display gameboard state of winner
       strcpy(winner[Player], " "); //Remove winner statement for next game
       return 1; //Return output as TRUE
    }
    else //FALSE condition outcome
    {   
        printf("Press enter to continue...\n");
        getchar(); //Prompt player to press enter to move forward with the game
        return 0; //Return output as FALSE
    }
}

int Replay() //Ask whether players want to play again
{
    int Playagain; //record down user input decision
    printf("Do you want to play again? [1/2]\n");
    do
    {
        printf("1. YES\n2. NO\nChoice: ");
        scanf("%d", &Playagain);
        if (Playagain < 1 || Playagain > 2) //Outcome whenever user choose a non viable option
        {
            printf("Please key in 1 or 2!\n");
        }
    } while (Playagain < 1 || Playagain > 2); //Repeat multiplayer input whenever user choose non viable option
    return Playagain; //Return user input result to function
}

int main() //Main Program Flow
{
    int i , Playagain; // i = index of each position, Playagain = Output status of replay option
    srand(time(0)); // Seed the random number generator
    do
    {
        for (i = 1; i <= 100; i++) //Loop 100 times for 100 positions
        {
            sprintf(position[i], "%d", i); //Initialize all position numbers in gameboard in string
        }
        printf("SNAKE LADDER GAME\n");
        PlayerMenu(); //Procedure to carry out multiplayer selection
        int winner = 0; // winner = TRUE(1) / FALSE(0) status of game
        while (winner == 0) //Each loop execute game mechanic until a player fufills win condition
        {
            Gameboard(position); //Display gameboard of players current status
            Playerturn(); //Current player attempts dice roll to earn as much cumulated score as possible
            winner = win(); //Check if any player fufill win condition of scoring 100 points
            NextPlayer(); //Move to next player turn
        } 
        Playagain = Replay(); //Prompt user to decide whether to play the game again
    } while (Playagain != 2); //Replay the game as long as player does not choose option 2

    return 0;
}