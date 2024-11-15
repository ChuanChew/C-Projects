#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

/*BANK MANAGEMENT SYSTEM PROJECT

The banking sector occupies a large part of the tertiary sector because which data maintained is too much by a single application. 
Using C language we can create an application that can manage the data of the Bank,  we use basic knowledge of C like string, array, structures, etc.
The functionality of the Bank Management System Application is mentioned below:

1. Transfer Money to the Account
2. Creation of Account
3. Check Amount
4. Login Functionality */

typedef struct
{
    char PhoneNumber[20];
    char UserIC[12];
    char FirstName[20];
    char LastName[20];
    char Password[25];
    char Sex;
    char DateofBirth[12]; // DD/MM/YYYY
    char Race[15];
    char Religion[15];
    char Occupation[20];
    float Balance;
    
} AccountDetails;

FILE *ptr;
char Filename[150];
AccountDetails Account, Account1; //Account1 represent receiver file for bank transfer

void getPassword(char *password, int maxLength) { //Password censorship
    int i = 0;
    char ch;

    // Read characters until Enter (newline) is pressed
    while (i < maxLength - 1) {
        ch = _getch(); // Use _getch() to read a single character without echoing it

        if (ch == '\r') { // Check for Enter key (carriage return)
            break;
        } else if (ch == '\b') { // Check for Backspace
            if (i > 0) {
                printf("\b \b"); // Erase the last asterisk
                i--;
            }
        } else {
            password[i++] = ch;
            printf("*"); // Print an asterisk
        }
    }

    password[i] = '\0'; // Null-terminate the string
    printf("\n");
}

int Menu ()
{
    int exit = 0;
    int choice;

    //Select Login or Register
    printf("SELECT||\n");
    printf("\n1. LOGIN\n2. Register\n\n");
    
    //Outcome of int choice
    do
    {
        printf("Option: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
            exit = 1;
            break;
            
            case 2:
            exit = 1;
            break;

            default:
            printf("Please select 1 or 2!\n");
            break;
        }
    } while (exit == 0);
    return choice;
}

int Login()
{
    int success = 0;
    char PhoneNumber[20];
    char Password[25];

    printf("=====================\n");
    // Prompt for User ID
    printf("LOGIN||\n");
    printf("ID: ");
    scanf("%s", &PhoneNumber);
    while (getchar() != '\n');  // Flush the newline character

    // Prompt for Password
    printf("Password: ");
    getPassword(Password, sizeof(Password)); // Use the same getPassword function as in Register

    // Open the file
    strcpy(Filename, PhoneNumber);
    ptr = fopen(strcat(Filename,".dat"),"r");

    if (ptr == NULL) {
        printf("Error opening account. User ID may be incorrect.\n");
        return;
    }
    else
    {
        //Read file struct data 
        fread(&Account,sizeof(AccountDetails),1,ptr);
        fclose(ptr);

        if ((!strcmp(Password, Account.Password)) && (!strcmp(PhoneNumber, Account.PhoneNumber))) //Check if variable data for login information the same as data in struct files bank account
        {
            printf("Login successful!\n");
            success = 1;
            // Proceed with login actions (e.g., show account details, menu)
        }
        else 
        {
            printf("Invalid User ID or Password.\n");
        } 
    }
    return success;
}

void Register() {

    printf("=====================\n");
    // Enter account ID
    printf("ACCOUNT DETAILS||\n");
    printf("HP: ");
    scanf("%s", Account.PhoneNumber);

    // Enter account IC
    printf("IC: ");
    scanf("%s", Account.UserIC);

    while (getchar() != '\n');  // Flush the newline character

    // Enter account first name
    printf("First Name: ");
    fgets(Account.FirstName, 100, stdin);
    Account.FirstName[strlen(Account.FirstName) - 1] = '\0'; //Set any printf statement containing variable "name" as an output will remove all new statements

    // Enter account last name
    printf("Last Name: ");
    fgets(Account.LastName, 100, stdin);
    Account.LastName[strlen(Account.LastName) - 1] = '\0'; //Set any printf statement containing variable "name" as an output will remove all new statements

    // Enter account password
    printf("Password: ");
    getPassword(Account.Password, sizeof(Account.Password));

    // Enter Sex
    do {
        printf("Sex (M / F): ");
        scanf(" %c", &Account.Sex);
        Account.Sex = toupper(Account.Sex);
        if (Account.Sex != 'M' && Account.Sex != 'F') 
        {
            printf("Please enter F / M!\n");
        }
    } while (Account.Sex != 'M' && Account.Sex != 'F');

    // Enter account Date of Birth
    printf("Date of Birth (DD/MM/YYYY): ");
    scanf("%s", Account.DateofBirth);
    while (getchar() != '\n');  // Flush the newline character

    // Enter account race
    printf("Race (Chinese/Malay/ ... etc): ");
    fgets(Account.Race, 100, stdin);
    Account.Race[strlen(Account.Race) - 1] = '\0'; //Set any printf statement containing variable "name" as an output will remove all new statements

    // Enter account Religion
    printf("Religion (Buddhism/Islam/ ... Etc): ");
    fgets(Account.Religion, 100, stdin);
    Account.Religion[strlen(Account.Religion) - 1] = '\0'; //Set any printf statement containing variable "name" as an output will remove all new statements

    // Enter account Occupation
    printf("Occupation: ");
    scanf("%s", Account.Occupation);

    Account.Balance = 0.00;

    // File opening method
    strcpy(Filename,Account.PhoneNumber);
    ptr = fopen(strcat(Filename,".dat"),"w");

    if (ptr == NULL) {
        printf("Error opening account file for writing\n");
        perror("Error");
        return;
    }

    // Write account details to the file
    fwrite(&Account,sizeof(AccountDetails),1,ptr);
    if(fwrite != 0)
    {
        printf("Account succesfully registered\n");
    }
    else 
    {
        printf("Something went wrong please try again\n");
    }

    fclose(ptr);
}

int BankOperation(float Amount)
{
    int Option;
    int Decision = 0;
    char choice;
    char PhoneNumber[20];
    char CurrentPassword[25];
    char Password[25];
    char ConfirmPassword[25];

    //Set local current time after every transaction
    time_t CurrentTime;
    time(&CurrentTime);
    struct tm *localTime = localtime(&CurrentTime);
    
    //User Bank Operation Menu
    printf("WELCOME %s\n\n", Account.FirstName);
    printf("1. Account Details\n");
    printf("2. Transfer\n");
    printf("3. Withdrawal\n");
    printf("4. Deposit\n");
    printf("5. Change Password\n");
    printf("6. Account Termination\n");
    printf("\nOption: ");
    scanf("%d", &Option);
    switch (Option)
    {
    case 1: //Review user account details
        printf("=====================\n");
        printf("ACCOUNT DETAILS||\n");
        printf("Balance: $%.2f\n", Account.Balance);
        printf("HP: %s\n", Account.PhoneNumber);
        printf("IC: %s\n", Account.UserIC);
        printf("First Name: %s\n",Account.FirstName);
        printf("Last Name: %s\n", Account.LastName);
        printf("Password: %s\n", Account.Password);
        printf("Sex (M / F): %c\n", Account.Sex);
        printf("Date of Birth (DD/MM/YYYY): %s\n", Account.DateofBirth);
        printf("Race (Chinese/Malay/ ... etc): %s\n", Account.Race);
        printf("Religion (Buddhism/Islam/ ... Etc): %s\n", Account.Religion);
        printf("Occupation: %s\n\n", Account.Occupation);
        break;
        
    case 2: //Perform online transfer
        printf("=====================\n");
        printf("Enter receiver phone number: ");
        scanf("%s", &PhoneNumber);
        printf("Enter transfer amount: ");
        scanf("%f", &Amount);
        strcpy(Filename, PhoneNumber); //Copy and paste PhoneNumber string to Filename
        //Open file of receiver bank account
        ptr = fopen(strcat(Filename,".dat"),"r"); //Open following file bank account base on PhoneNumber
        fread(&Account1,sizeof(AccountDetails),1,ptr); //Read file data to check if account number exist
        if ((!strcmp(PhoneNumber, Account1.PhoneNumber)))
        {
            if (Account.Balance < Amount)
            {
                printf("Transaction failed!\n");
                printf("Reason: Insufficient account balance\n");
            }
            else
            {
                ptr = fopen(Filename,"w");
                Account1.Balance = Account1.Balance + Amount;
                fwrite(&Account1,sizeof(AccountDetails),1,ptr); //Rewrite receiver balance amount
                fclose(ptr);
                
                if (ptr != NULL) //If pointer ptr is not equal to NULL, it means account data type exist in file struct which will be rewritten
                {
                    //Online Receipt
                    printf("Transaction successful of $%2.f to %s\n", Amount, Account1.FirstName);
                    printf("Date and time of transfer: %02d/%02d/%d %02d:%02d:%02d\n", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900, localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
                    strcpy(Filename, Account.PhoneNumber);
                    ptr = fopen(strcat(Filename, ".dat"),"r");
                    Account.Balance = Account.Balance - Amount;
                    fwrite(&Account,sizeof(AccountDetails),1,ptr); //Rewrite user balance amount
                    fclose(ptr);
                    printf("New balance: $%2.f\n", Account.Balance);
                }
            }   
        }
        else 
        {
            printf("Bank account not registered.\n");
        }
        break;

    case 3: //Withdrawal of account balance
        printf("=====================\n");
        printf("Enter withdrawal amount: ");
        scanf("%f", &Amount);
        if (Account.Balance < Amount) //if user account balance is lesser than withdrawal amount
        {
            printf("Withdrawal failed!\n");
            printf("Reason: Insufficient account balance\n");
        }
        else
        {
            ptr = fopen(Filename, "w");
            Account.Balance = Account.Balance - Amount; //Deduct user balance base on withdrawal amount
            fwrite(&Account,sizeof(AccountDetails),1,ptr); //Rewrite user balance amount
            fclose(ptr);
            if (fwrite != NULL)
            {
                //Online Receipt
                printf("Withdrawal successful of $%2.f\n", Amount);
                printf("Date and time of withdrawal: %02d/%02d/%d %02d:%02d:%02d\n", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900, localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
                printf("New balance: $%2.f\n", Account.Balance);
            }
        }
        break;
    
    case 4: //Deposit money to user account
        printf("=====================\n");
        printf("Enter deposit amount: ");
        scanf("%f", &Amount);
        ptr = fopen(Filename, "w");
        Account.Balance = Account.Balance + Amount; //Add user balance base on deposit amount
        fwrite(&Account,sizeof(AccountDetails),1,ptr); //Rewrite user balance amount
        fclose(ptr);
        if (fwrite != NULL)
        {
            //Online Receipt
            printf("Deposit successful of $%2.f\n", Amount);
            printf("Date and time of withdrawal: %02d/%02d/%d %02d:%02d:%02d\n", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900, localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
            printf("New balance: $%2.f\n", Account.Balance);
        }
        break;
    
    case 5: //Change password
        printf("=====================\n");
        printf("Current password: ");
        getPassword(CurrentPassword, sizeof(CurrentPassword));
        printf("New password: ");
        getPassword(Password, sizeof(Password));
        printf("Confirm password: ");
        getPassword(ConfirmPassword, sizeof(ConfirmPassword));

        ptr = fopen(Filename,"w");
        if (!strcmp(CurrentPassword, Account.Password)) //if current password key in the same as account password in struct data file
        {   
            if (!strcmp(Password, CurrentPassword))
            {
                printf("You are not allowed to use your previous password as the new password\n");
            }
            else
            {
                if (!strcmp(Password, ConfirmPassword))
                {
                    strcpy(Account.Password, ConfirmPassword);
                    fwrite(&Account,sizeof(AccountDetails),1,ptr);
                    if (fwrite != NULL)
                    {
                        printf("Password successfully changed!\n");
                    }
                }
                else
                {
                    printf("New password does not match with confirm password\n");
                } 
            }
        }
        else
        {
            printf("Current password is incorrect\n");
        }
        break;
    
    case 6: //Account Termination
        char AccountPassword[25];
        printf("Are you sure you want to terminate your account? [Y/N]\n");
        scanf(" %c", &choice);
        choice = toupper(choice);
        if (choice == 'Y');
        {
            printf("Please enter password to withdraw account balance $%.2f\n", Account.Balance);
            printf("Password: ");
            getPassword(CurrentPassword, sizeof(CurrentPassword));
            fread(&Account,sizeof(AccountDetails),1,ptr);
            fclose(ptr);
            if (!strcmp(CurrentPassword, Account.Password)) //if current password key in the same as account password in struct data file
            {
                if(remove(Filename) == 0) //if function to execute its code section when condition is met
                {
                    printf("$%2.f has been successfully withdraw!\n", Account.Balance);
                    printf("Account successfully deleted!\n"); //printf statement to show file is deleted
                    Decision = 1;
                }
                else //alternate code section to execute when if function condition is not met
                {
                    printf("Password enter is incorrect!\n"); //printf statement to show file remains
                }
            }

        }
        return Decision; //Return output of decision = 1 back to main function to declare account successfully deleted
        break;

    default:
        printf("Invalid Option!\n");
        break;
    }


}

int main(){
    int exit = 0;
    int Menuchoice, AccountDeletion, AccountLogin;
    char choice;
    float Amount;
    //Header Title
    printf("=====================\n");
    printf("BANK MANAGEMENT SYSTEM\n");

    //Enter main menu option
    do
    {
        printf("=====================\n");
        Menuchoice = Menu();
        switch (Menuchoice)
        {
        case 1:
            AccountLogin = Login();
            if (AccountLogin == 1)
            {
                exit = 1;
            }
            else
            {
                exit = 0;
            }
            break;
        
        case 2:
            Register();
            break;
        }
    } while (exit == 0);
    
    //Bank Functions
    do
    {
        printf("=====================\n");
        AccountDeletion = BankOperation(Amount);
        if (AccountDeletion == 1) //Condition is TRUE when account is successfully deleted
        {
            choice = "Y"; //Set choice to "Y" to end do while loop since there is no more account to continue transaction
        }
        else
        {
           printf("Do you wish to continue the transaction? [Y/N]\n");
           scanf(" %c", &choice);
           choice = toupper(choice);
        }
    } while (choice == 'Y'); //Exit when user does not want to continue transactiot by choosing 'N'

    printf("=====================\n");
    printf("THANK YOU!\n");
    return 0;
}