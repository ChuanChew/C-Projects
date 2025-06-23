#include <stdio.h>
#include <time.h>
#include <string.h>

void Header() //Display game design
{
  printf("=================\n");
  printf("  HANGMAN GAME\n");
  printf("=================\n");
  return;
}

void Instructions() //Teach player how to play the game
{
  printf("Rules:\n");
  printf("1. The player guesses letters one at a time\n");
  printf("2. If the guessed letter is in the word, the letter is revealed in its correct positions\n");
  printf("3. If the guessed letter is not in the word, a body part is added to the hangman drawing\n");
  printf("4. The player continues guessing letters until either the word is guessed correctly or the hangman is fully drawn\n\n");
  printf("Press Enter to continue...\n");
  getchar(); // Wait for Enter to move next step of the game
  return;
}

void InitializeGameState(int *QuestionNumber, int *life, int *correct, int *Wordsize, char *Word, char *lines) //Set the starting stage of the game
{
  (*QuestionNumber) = (rand() % 5) + 1; //variable Question store in integer data to be used in random function (rand()) to roll and generate a random number from 1 - 5
  switch (*QuestionNumber)
  {
  case 1:
    (*Wordsize) = 4; //SOAP
    strcpy(Word, "SOAP");
    break;
  case 2:
    (*Wordsize) = 9; //SNOKEFLAKE
    strcpy(Word, "SNOWFLAKE");
    break;
  case 3:
    (*Wordsize) = 8; //POPSICLE
    strcpy(Word, "POPSICLE");
    break;
  case 4:
    (*Wordsize) = 7; //LETTUCE
    strcpy(Word, "LETTUCE");
    break; 
  case 5:
    (*Wordsize) = 4; //RAIN
    strcpy(Word, "RAIN");
    break; 
  default: //Assign variable pointed to main function Word to hold the question answer
    break; //Assign variable pointed to main function Wordsize to determine number of letters needed to be guess depending on string *Word
  }
  for (int i = 0; i < *Wordsize; i++)
  {
    lines[i] = '_'; //For each letter, create an empty line
  }
  lines[*Wordsize] = '\0'; //Final index should be NULL to prevent buffer
  (*life) = 0;
  (*correct) = 0; //Set both life and correct answer as 0 to begin game in default setting
  return;
}

void HangMan(char *Stickmanempty[7]) //Hangman Design
{
  printf("  ________________\n");
  printf(" |\t\t |\n");
  printf(" |\t         %s\n", Stickmanempty[0]);
  printf(" |\t       %2s%1s%2s\n", Stickmanempty[2], Stickmanempty[1], Stickmanempty[3]);
  printf(" |\t         %s\n", Stickmanempty[4]);
  printf(" |\t        %s%2s\n", Stickmanempty[5],Stickmanempty[6]);
  printf(" |\t\t \n\n");
  return;
}

void Question(int QuestionNumber) //Display random question depending on random number roll from variable QuestionNumber in Size function
{
  switch (QuestionNumber) //There are total 5 different questions
  {
  case 1:
    printf("What gets smaller every time it takes a bath?\n");
    break;
  case 2:
    printf("I'm not a blanket, yet I cover the ground; a crystal from heaven that doesn't make a sound. What am I?\n");
    break;
  case 3:
    printf("I'm sweet and cold with a stick to hold; a treat on a hot day, worth more than gold. What am I?\n");
    break;
  case 4:
    printf("What has a head but no brain?\n");
    break; 
  case 5:
    printf("What comes down but never goes up?\n");
    break; 
  default:
    break;
  }
  return;
}

void Guess(int Wordsize, int *isCorrectGuess, int *correct, char *lines, char *Word, char *letter, char *sameletter) //Player enter an letter to guess the word
{
  for (int i = 0; i < Wordsize; i++)
  {
    printf("%c ", lines[i]); //Create lines for letter guessing "_"
  }
  printf("\nGuess the letters: ");
  scanf(" %c", letter); //no need & operator letter is already a char *, it’s already pointing to the memory address of letter in main()
  *letter = toupper(*letter); //convert all letters to capital
  for (int j = 0; j < Wordsize; j++) //loop through the string
  {
    if (*letter == Word[j] && lines[j] == '_') //check whether the guess letter is the same as any index in the array and its only guessed once by checking whether the index is "_"
    {
      lines[j] = *letter; //Assign the current letter line into the correct letter
      (*isCorrectGuess) = 1; //Assign isCorrectGuess as 1 to show player guessed correctly
      (*correct)++; //Increase number of correct answer by 1
    }
  }
  return;
}

void Result(int *life, int *isCorrectGuess, char *Stickmanempty[7], char *bodyparts[7], char *letter, char *sameletter) //Show output result of player guesses
{
  int ch;
  if (*letter == *sameletter || *isCorrectGuess != 1) //Check whether player guess is wrong or player have guess the same letter
  {
    printf("You guessed wrong!\n");
    Stickmanempty[*life] = bodyparts[*life]; //Draw a piece of hangman to indicated player guess wrong
    (*life)++; //Increment life by 1 to keep track number of wrong guesses
  }
  else if (*isCorrectGuess == 1) //Check whether player guess correctly
  {
    printf("You guessed correct!\n");
    *sameletter = *letter; //Assign sameletter variable the same as current correct guess letter to keep track of same potential next letter guess
  }
  while ((ch = getchar()) != '\n' && ch != EOF); // Flush buffer
  printf("Press Enter to continue...\n"); //Give players time to check the status of game before flashing the next guess input
  getchar();
  return;
}

void Conclusion(int *playAgain, int *gameOver, char *Stickmanempty[7]) //Check if player wants to replay the game
{
  int choice, exit = 0;
  printf("Play again?\n");
  printf("1. Yes\n2. No\n");
  while (exit == 0)
  {
    printf("Enter 1 or 2: ");
    scanf("%d", &choice);
    if (choice != 1 && choice != 2)
    {
      printf("Please enter 1 or 2!\n");
    }
    else
    {
      exit = 1; //If player chooses option 1 or 2, exit the loop by setting exit to 1
    }
  }
  if (choice == 2)
  {
    (*playAgain) = 0; //End the program if player does not want to replay
  }
  else if (choice == 1)
  {
    (*playAgain) = 1;
    (*gameOver) = 0; //Reset variable end to 0 to restart the gameplay loop
    for (int i = 0; i < 7; i++)
    {
      Stickmanempty[i] = " "; //Reset stickman state back to default
    }
  }
  return;
}

int main() {
  
  int QuestionNumber, Wordsize , life, correct;
  int isCorrectGuess = 0, gameOver = 0, playAgain = 1;
  char Word[20], lines[20];
  char letter, sameletter; // Used to store player's guess and prevent repeated guesses
  char *Stickmanempty[7] = {" ", " ", " ", " ", " ", " "," "}, *bodyparts[7] = {"O", "|", "--", "--", "|", "/", "\\"};
  srand(time(0)); //Generate a random value at current time

  Header(); //Game entry scene
  Instructions(); //Teach players how to play hangman game
  while (playAgain == 1) //As long as restart is true (1), game will reset after finishing current game
  {
    InitializeGameState(&QuestionNumber, &life, &correct, &Wordsize, Word, lines); //Set game state to default setting

    while (gameOver == 0) // Main gameplay loop — keeps running until player either wins or loses
    {
      Header(); //Game display
      HangMan(Stickmanempty); //Current state of hangman
      Question(QuestionNumber); //Display question for players to guess the word
      isCorrectGuess = 0; //Default setting for player current guess to be false
      Guess(Wordsize, &isCorrectGuess, &correct, lines, Word, &letter, &sameletter); //Player guess the letter within the word
      Result(&life, &isCorrectGuess, Stickmanempty, bodyparts, &letter, &sameletter); //Outcome to check whether player guess the correct letter
      if (life == 7 || correct == Wordsize) //Check whether player life has run out or has complete guessing the all letters of the word
      {
        gameOver = 1; //Set end = 1 to end the game in the while loop
      }
    }
    Header(); 
    HangMan(Stickmanempty); //Show final state of the game
    if (life == 7) //If player use up all 7 lifes from guessing wrong letters
    {
      printf("Lose! Answer is %s\n", Word); //Inform player the correct answer
    }
    else if (correct == Wordsize) //If player guess all letters of the word
    {
      printf("Win!\n");
    }
    Conclusion(&playAgain, &gameOver, Stickmanempty); //Asked player whether to play again
  }

  return 0;
}