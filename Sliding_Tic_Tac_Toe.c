#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // provides functions for character classification and character conversion
#include <time.h>

/*Create a Quick Thinking Sliding Tic Tac Toe game program. 
1. The game starts as a 2 player game, player will key in their in game name before starting the game.
2. Flip a coin to decide the winner goes first
3. Winner of flip choose either to represent symbol 'X' or 'O' before game starts
4. Game Starts with 9 empty boxes on board
5. Each player will take turn to fill in empty box with their represented symbol
6. During the game, each player can only lay a maximum of 3 player symbol on the empty space among the 9 boxes. 
7. If a player symbol is about to exceed filling 3 boxes the latest player input will replace the 1st input by making the 1st input box to become empty. 
8. When the first player manage to fill 3 boxes vertically, horizontal, or diagonal line, declare that player as the winner.
9. After the winner is declare, the player can make a respond whether to restart the game to play again.
10. If player want to stop, end the game.*/

//Create global variable to have key functions of the game. The board layout in 3x3 matrix and 2 players symbol representation.
char p1, p2, p3, p4, p5, p6, p7, p8, p9;
char playername[100];
char cpu[] = "CPU";
char PLAYER, CPU; //Player controls
int mode; //Variable mode to contain data of game mode selection between single and 2 player
int playerturn; //execute different player operation representative behavior between human and cpu 
int playersymbolcount = 0;
int CPUsymbolcount = 0;
//Each player symbol count variable is to keep track number of symbol each player place in the tic tac toe board throughout the game
int playerSymbolPosition[3] = {0};
int CPUSymbolPosition[3] = {0};
/*Each play symbol position of 3 element arrays starting from 0-2. Each element stores the tic tac toe position from 1-9 respectively during each player turn.
Example, playSymbolPosition[3] use for player 1 stores 3 position number for 3 turns with {1}, {2}, {4}*/

void playerinfo() //Step 1 
{
            printf("\nEnter your name: ");
            fgets(playername, 100, stdin);
            playername[strlen(playername) - 1] = '\0'; //Set any printf statement containing variable "name" as an output will remove all new statements

}
int TurnOrder() //Step 2
{
    int flipper;
    srand(time(0)); //Generate a random value at current time
    flipper = (rand() % 2) + 1; //variable flipper store in integer data to be used in random function (rand()) to roll and generate a random number from 1 - 2
    return flipper;
}

void SymbolSelection(int Currentplayer) //Step 3
{
    int exit = 0; //exit variable created to make a condition in while loop function

        if (Currentplayer == 1) 
        {
            printf("\nTurn Order:\nPlayer goes first!");
        }
        else
        {
            printf("\nTurn Order:\nCPU goes first!");
        }
        //Declaration of turn order depending on number generated from flipper variable in TurnOrder()
        
        printf("\nPlayer please select symbol: X / O\n");
        do
        {
            scanf(" %c", &PLAYER); // Note the space before %c to skip any whitespace characters
            PLAYER = toupper(PLAYER); //Change any small letter input to capital letters
            switch (PLAYER)
            {
                case 'X':
                    CPU = 'O'; //Give CPU player remaining representing symbol
                    exit = 1; //set exit = 1 to force the while function condition to be false. Exiting the code section loop
                    break;

                case 'O':
                    CPU = 'X'; //Give CPU player remaining representing symbol
                    exit = 1; //set exit = 1 to force the while function condition to be false. Exiting the code section loop
                    break;

                default:
                    printf("\nPlease select X or O!\n"); //Prompt user to re-enter choice between X or O
                    break;
            }
        } while (exit == 0); //If neither X or O is choicen, exit will remain 0. Thus, while loop becomes true and repeat code section
        //If flipper == 1, it would declare player 1 goes first and player 1 will select representing symbol of X or O. Giving the unselected symbol to the 2nd player
    
}

void resetBoard() //Step 4
{  
        p1 = p2 = p3 = p4 = p5 = p6 = p7 = p8 = p9 = ' '; //Each element within variable p element will be blank space
}

void printBoard() //Step 4
{
    //Game info display of player names and symbol align with tic tac toe board

    printf("\nPlayer 1: %s\t\tPlayer 2: %s", playername, cpu);
    printf("\nSymbol: %c\t\t\tSymbol: %c\n\n", PLAYER, CPU);

    //Print display of tic tac toe board design
    printf("\t\t %c | %c | %c ", p1, p2, p3);
    printf("\n\t\t---|---|---\n");
    printf("\t\t %c | %c | %c ", p4, p5, p6);
    printf("\n\t\t---|---|---\n");
    printf("\t\t %c | %c | %c ", p7, p8, p9);
    printf("\n\n");

}

int PlayerTurn() //Step 5 and 6
{
    int exit = 0; //exit variable created to make a condition in while loop function
    int position; //Variable position is created to mark which spot out of the 9 in tic tac toe board to fill
    char *cell; //variable pointer cell is used to store data from 9 position of the board p1 - p9

    do
    {
        switch (playerturn) //execute code section depending on playerturn value 
        {
        case 1: //player1 turn
            printf("\nPlayer %s: Please choose position (1-9)\n", playername);
            scanf("%d", &position);
            break;
        case 2: //cpu turn
            /*no printf statement to announce cpu turn unlike player turn because if the CPU picks an already occupied cell, it doesn't make another choice 
            immediately within the same turn. Instead, it continues with the loop and might print an announcement about choosing a position 
            which it actually hasn't successfully chosen. This can be confusing and misleading. */
            position = (rand() % 9) + 1; //variable position store in integer data to be used in random function (rand()) to roll and generate a random number from 1 - 9
            break;
        default:
            break;
        }
        switch (position)
        //From case 1 - 9, pointer cell will become representative of character variable p1 to p9 depending which case number code is executed
        {
        case 1:
            cell = &p1; //Assign data from char p1 and point its data to cell
            break;
        case 2:
            cell = &p2;
            break;
        case 3:                             //Code Section Sequence:                                             
            cell = &p3;                     // 1. User input on position number 
            break;                          // 2. Pointer cell assigned to become one of the variable from p1 to p9 depending on case number. Example case 1, cell becomes variable p1
        case 4:                             // 3. Cell now is variable p1-p9 checks on if condition whether is the space ' '
            cell = &p4;                     // 4. if cell (p1-p9) data is not ' ', execute if function code section to inform user the space is fill and choose an empty spot
            break;                          // 5. if cell (p1-p9) is ' ', execute else statement to replace pointer cell data value with PLAYER (X or O symbol)
        case 5:                             // 6. When the flow of code section is successfully executed, exit do while loop and move to next code section
            cell = &p5;
            break;
        case 6:
            cell = &p6;
            break;
        case 7:
            cell = &p7;
            break;
        case 8:
            cell = &p8;
            break;
        case 9:
            cell = &p9;
            break;
        default:
            printf("\nInvalid position!\n"); //Prompt user to choose position again if key in invalid number
            break;
        }
        
        if (*cell != ' ') //if condition to execute code section if the given position of the board is fill
        {
            if (playerturn == 1) //execute statement if either player 1 choose a fill symbol spot
            {
                printf("\nThis position is already taken! Please choose another position:\n");
            }
            else if (playerturn == 2) //execute statement if cpu choose a fill symbol spot
            {
                continue; //if cpu number generated to a fill position, skip this section of code statement to prevent game from showing cpu error
            }
        }
        else
        {  
            if (playerturn == 1) //Fill symbol in chosen position if its player 1 turn
            {
                *cell = PLAYER; //One of the given position from p1-p9 will be fill by the player 1 representative symbol
            }
            else if (playerturn == 2) //Fill symbol in chosen position if its cpu turn
            {
            *cell = CPU; //One of the given position from p1-p9 will be fill by the cpu representative symbol
            printf("\n%s has chosen position %d!\n", cpu, position);
            }
            exit = 1; //set exit = 1 to force the while function condition to be false. Exiting the code section loop
        }

    } while (exit == 0); //When one of the position chosen is successfully fill by player symbol, exit will become 1. Forcing the condition to become false and exit the loop
    Symbolcount(position);
    return position; //return position number to represent value of Playerturn() function to pass to Symbolcount() function
}

void Symbolcount(int position) //Step 7
{
    /*This function SymbolCount is responsible for keeping track of the count of symbols placed by each player (or CPU) and the positions of these symbols 
    on the tic-tac-toe board. It ensures that if a player or CPU has already placed three symbols, the oldest symbol's position is replaced with an empty 
    space (' '), and the positions of the remaining symbols are shifted to the left to accommodate the new symbol.*/
    int* playerSymbolPositions;
    int* symbolcount;

    switch (playerturn) //Depending on which player completes their turn during the game, count up their symbol placement by 1
    {
        case 1:
            playerSymbolPositions = playerSymbolPosition;           //playerSymbolPositions pointer variable will be assigned to one of the arrays 
            symbolcount = &playersymbolcount;                       //(playerSymbolPosition, or CPUSymbolPosition) based on the current player turn.
            break;                                                  //symbolcount: This pointer variable will be assigned to one of the symbol count variables                                                                  
        case 2:                                                     //(playersymbolcount, or CPUsymbolcount) based on the current player turn.
            playerSymbolPositions = CPUSymbolPosition;
            symbolcount = &CPUsymbolcount;
            break;
        default:
            return;
    }

    if (*symbolcount >= 3) //If the symbol count (*symbolcount) for the current player is greater than or equal to 3 replace the oldest symbol's position with ' ' 
    {
        // The function retrieves the position of the oldest symbol from the array playerSymbolPositions.
        int oldestPosition = playerSymbolPositions[0]; //int oldest position stores data for the 1st element of playersymbol position for each player
        switch (oldestPosition) 
        {
            case 1: p1 = ' '; break;
            case 2: p2 = ' '; break;
            case 3: p3 = ' '; break;
            case 4: p4 = ' '; break;
            case 5: p5 = ' '; break;
            case 6: p6 = ' '; break;
            case 7: p7 = ' '; break;
            case 8: p8 = ' '; break;
            case 9: p9 = ' '; break;
        }

        // Shift the positions to the left
        for (int i = 0; i < 2; i++) 
        {
            playerSymbolPositions[i] = playerSymbolPositions[i + 1];
            /*The function shifts the positions of the symbols to the left by copying each position from index i+1 to index i, 
            effectively removing the oldest position from the array. This loop runs twice to shift all positions except the last one. */
        }
        playerSymbolPositions[2] = position; //function updates the last position in the array (playerSymbolPositions[2]) with the position of the newest symbol of each player next turn
    } 
    else //If the symbol count for the player is less than 3, it means there's space for another symbol. execute the else function code section
    {
        playerSymbolPositions[*symbolcount] = position; //In this case, the function adds the position of the newest symbol to the array
        (*symbolcount)++; //increments the symbol count for each player in the pointer before moving to next player turn.
    }
}

int Wincon() //Step 8
{
    int Playerwin = 0;
    //Check for Row win condition 
    if ((p1 == p2 && p2 == p3 && p1 != ' ') || //row 1
        (p4 == p5 && p5 == p6 && p4 != ' ') || //row 2
        (p7 == p8 && p8 == p9 && p7 != ' '))   //row 3
    {
        Playerwin = 1; //Switch value to 1 in order to return Wincon() integer invoke function value back to int main function to fufill game stop condition
    }
    //Check for column win condition 
    else if ((p1 == p4 && p4 == p7 && p1 != ' ')  || //column 1
             (p2 == p5 && p5 == p8 && p2 != ' ')  || //column 2
             (p3 == p6 && p6 == p9 && p3 != ' '))    //column 3
    {
        Playerwin = 1;
    }
    //Check for diagonal win condition 
    else if ((p1 == p5 && p5 == p9 && p1 != ' ')  || //diagonal 1
             (p3 == p5 && p5 == p7 && p3 != ' '))    //diagonal 2
    {
        Playerwin = 1;
    }
    // Print tic tac toe final board result of the winning pattern
    if (Playerwin == 1)
    {
        if (p1 == PLAYER || p2 == PLAYER || p3 == PLAYER || 
            p4 == PLAYER || p5 == PLAYER || p6 == PLAYER || 
            p7 == PLAYER || p8 == PLAYER || p9 == PLAYER) //Ensure the winning pattern all contain the same symbol of the winner player
        {
            printBoard(); //print final board result
        }
        else if (p1 == CPU || p2 == CPU || p3 == CPU || 
                 p4 == CPU || p5 == CPU || p6 == CPU || 
                 p7 == CPU || p8 == CPU || p9 == CPU) //Ensure the winning pattern all contain the same symbol of the winner cpu
        {
            printBoard(); //print final board result
        }
    }
    return Playerwin;

}

// Function to print centered text
void printCentered(const char *str) 
{
    int len = strlen(str); //strlen = 6 because WINNER has 6 characters
    int totalWidth = 42; // Adjust this value based on your board's total width
    int spaces = (totalWidth - len) / 2;
    for (int i = 0; i < spaces; i++) {
        printf(" "); //Add spacebar for each loop depending max value of int spaces. 42 - 6 = 36/2 = 18 spaces
    }
    printf("%s\n", str);
}

int main(){ //Entry point of program code, any code written within { } is consider the program body of int main and it will execute from top to bottom line.

    int winner = 0;
    int exit = 0;
    char Decision;
    //Create Game intro display
    printf("\n***********************\n");
    printf("      TIC TAC TOE     ");
    printf("\n***********************\n");

    playerinfo(); //Execute code section to enter player information
    do
    {
        int Currentplayer = TurnOrder();
        /*If TurnOrder() is used inside while loop, The random function in TurnOrder() will repeatly generate random number from 1-2 if while function remain true. 
        Thus, by having integer Currentplayer to store TurnOrder(); random value, the number will remain stationary in while loop gameplay. Resulting smooth turn order.*/
        if(Currentplayer == 1) //Execute code section to decide which player starts first
        {
            printf("\nThe number roll is 1!\n");
        }
        else
        {
            printf("\nThe number roll is 2!\n");
        } 
        SymbolSelection(Currentplayer); //Execute code section for players to decide which symbol to represent in tic tac toe game
        resetBoard(); //Execute code section to set the empty state of the tic tac toe board

        while (winner == 0)
        {
            printBoard(); //Execute code section to display tic tac toe physical board
            int wincon = Wincon();
            {
                switch (Currentplayer)
                {
                case 1:
                    playerturn = 1; //value 1 represent player 1 operation
                    PlayerTurn(); //Execute code section for player 1 to mark a position in tic tac toe board
                    printBoard(); //Another printboard indicated to ensure when the first player add a symbol in a position, it will immediately be display without any delay effect
                    //The prevented delay issue happens when first player enters their position. But it only occurs after the 2nd player indicates their symbol
                    wincon = Wincon(); // Update win condition after player's move
                    if (wincon == 1)
                    {
                        printCentered("WINNER");
                        printCentered(playername); 
                        winner = 1;
                        break; //When current player completes a winning pattern, break function will force the code section to stop operating which means game is over
                    }
                    playerturn = 2; //value 2 represent cpu operation
                    printf("\nPlayer %s turn!\n", cpu);
                    /*To prevent repeated announcement of cpu turn from do while function during the game whenever executing PlayTurn() function of cpu placing its symbol on a fill spot due to random function,
                    putting printf statement on int main function to eliminate any confusion about when the CPU is actually making a move */ 
                    PlayerTurn(); //Execute code section for player cpu to mark a position in tic tac toe board
                    //2nd player do not need printBoard(cpu); since after its code section is executed, it will loop back to the starting code section of while loop where there already is printBoard(cpu)
                    wincon = Wincon(); // Update win condition after player's move
                    if (wincon == 1)
                    {
                        printCentered("WINNER");
                        printCentered(cpu); 
                        winner = 1;
                        break; //When current player completes a winning pattern, break function will force the code section to stop operating which means game is over
                    }
                    break;

                case 2:
                    playerturn = 2;
                    printf("\nPlayer %s turn!\n", cpu);
                    PlayerTurn(); //Execute code section for player cpu to mark a position in tic tac toe board
                    printBoard(); //Execute code section to display tic tac toe physical board
                    wincon = Wincon(); // Update win condition after player's move
                    if (wincon == 1)
                    {
                        printCentered("WINNER");
                        printCentered(cpu); 
                        winner = 1;
                        break; //When current player completes a winning pattern, break function will force the code section to stop operating which means game is over
                    }
                    playerturn = 1;
                    PlayerTurn(); //Execute code section for player 1 to mark a position in tic tac toe board
                    wincon = Wincon(); // Update win condition after player's move
                    if (wincon == 1)
                    {
                        printCentered("WINNER");
                        printCentered(playername); 
                        winner = 1;
                        break; //When current player completes a winning pattern, break function will force the code section to stop operating which means game is over
                    }
                    break;
                
                default:
                    break;
                }
            }        
        }
        printf("\n\tDo you want to play again?\n\t\tType Y/N: "); //Step 9
        int Redecide = 0;
        do
        {
            scanf(" %c", &Decision); // Note the space before %c to skip any whitespace characters
            Decision = toupper(Decision);
            switch (Decision)
            {
            case 'Y':
                playersymbolcount = 0;
                CPUsymbolcount = 0;
                winner = 0;
                Redecide = 1;
                break;
            case 'N':
                exit = 1;
                Redecide = 1;
                break;
            default:
                printf("\n\tPlease key in Y/N!");
                break;
            } 
        }while (Redecide == 0);
        //Prompts player to make a decision whether they want to play the game again
    } while (exit == 0);
    printf("\n");
    printCentered("GAME FINISH"); //Step 10

return 0; // Return value of 0 once program successfully execute all functions without error
} 