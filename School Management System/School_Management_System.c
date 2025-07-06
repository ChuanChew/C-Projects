#include <stdio.h>
#include <windows.h>
#include <string.h>
typedef struct
{
    char NRIC[10], Name[50], Gender[10], Course[50];
    int Age;
} StudentDetails; //For student data input

StudentDetails Data;
FILE *ptr;
WIN32_FIND_DATAA fileData; // Struct that holds file info (used by Windows file search)
HANDLE hFind; // Handle returned by FindFirstFile to loop through files
#define Directory "C:\\Users\\ohchu\\OneDrive - 81 Demolition Service\\Desktop\\C Program\\C Code Files\\Project\\School Management System\\Student Files\\"
const char *folderPath = "C:\\Users\\ohchu\\OneDrive - 81 Demolition Service\\Desktop\\C Program\\C Code Files\\Project\\School Management System\\Student Files\\*.txt"; //Find any txt file in given directory in windows
char Filename[150], Filepath[300];

void DisplayMainMenu(int *Choice) //Choose one of following application to manage student info
{
    printf("=== School Management System ===\n");
    printf("1. Add Student\n");
    printf("2. Student Courses\n");
    printf("3. Search Student\n");
    printf("4. Edit Student Info\n");
    printf("5. Student Count\n");
    printf("6. Delete Student\n");
    printf("7. Exit\n");
    *Choice = DecisionMaking("Enter (1-7): ", 1, 7);
    printf("\n=== School Management System ===\n");
}

void StudentRegistration(int Option, char *Gender[2], char *Courses[3]) //Add Student into the School Management Data System
{
    printf("Enter details:\n");
    printf("Enter student NRIC (e.g., T1234567G): "); // Get the NRIC input from the user (e.g., T1234567G)
    scanf("%9s", Data.NRIC);
    Data.NRIC[0] = toupper(Data.NRIC[0]);
    Data.NRIC[8] = toupper(Data.NRIC[8]); // Convert first and last character of NRIC to uppercase (standard NRIC format)
    while (getchar() != '\n');  // Flush the newline character
    //Enter Student Name
    printf("Name: ");
    fgets(Data.Name, sizeof(Data.Name), stdin); // Read full name (allows spaces)
    Data.Name[strcspn(Data.Name, "\n")] = '\0';  // Remove newline character
    //Enter Student Age
    printf("Age: ");
    scanf("%d", &Data.Age); 

    printf("Gender:\n");
    printf("1. Male\n2. Female\n");
    Option = DecisionMaking("Enter (1/2): ", 1, 2);
    strcpy(Data.Gender, Gender[Option]); // Set student gender based on selected option
    while (getchar() != '\n');  // Flush the newline character

    printf("Course:\n");
    printf("1. Business Management\n");
    printf("2. Common Engineering\n");
    printf("3. Cyber Security\n");
    Option = DecisionMaking("Enter (1-3): ", 1, 3);
    strcpy(Data.Course, Courses[Option]); // Set student course based on selected option

    //Open File to create student file
    strcpy(Filename, Data.NRIC); //Copy NRIC string to Filename
    FileDirectory(Filepath, sizeof(Filepath), Filename); // Build full path to student file (e.g., T1234567G.txt)
    ptr = fopen(Filepath, "r"); // Check if a file with this NRIC already exists
    if (ptr != NULL)
    {   //If file already exist
        printf("Student is already registered in the system!\n");
        return;
    }
    else if (ptr == NULL)
    {   //If file is new
        ptr = fopen(Filepath, "w");
        fprintf(ptr, "%s\n%s\n%d\n%s\n%s\n", Data.NRIC, Data.Name, Data.Age, Data.Gender, Data.Course); //Record all variable data into NRIC.txt file
        printf("Student successfully register!\n");
        fclose(ptr);
    }
}

void StudentCourseList(int Option, char *Courses[3]) //View all students in their respective course
{
    int i = 1;
    char line[20], course[50];
    hFind = FindFirstFileA(folderPath, &fileData); // Begin looping through all .txt files in folder
    printf("Enter Course:\n");
    printf("1. Business Management\n");
    printf("2. Common Engineering\n");
    printf("3. Cyber Security\n");
    Option = DecisionMaking("Enter (1-3): ", 1, 3);
    strcpy(course, Courses[Option]); // Set student course based on selected option
    if (hFind == INVALID_HANDLE_VALUE) { //If no txt file present in window directory
        printf("No student found.\n");
        return;
    }
    else
    {   //Display table
        printf("\n%-22s\n", course);
        printf("===================================================\n");
        printf("No.| %-22s | %-5s | %-7s |\n", "Name", "Age", "Gender");
        printf("===================================================\n");
        do {
            snprintf(Filepath, sizeof(Filepath), Directory"%s", fileData.cFileName); //Convert printf filepath statement to string that contain current NRIC filename.txt
            
            ptr = fopen(Filepath, "r"); //Open current student file to read all data
            if (ptr != NULL) {
                ReadStudentFile(ptr, &Data);
                if (strcmp(Data.Course, course) == 0) // Only print student if course matches selected course
                {
                    printf("%-3d| %-22s | %-5d | %-7s |\n",i, Data.Name, Data.Age, Data.Gender); // Print student info (Name, Age, Gender only)
                    i++; // Increase count for each matching student
                }
                fclose(ptr);
            }
        } while (FindNextFileA(hFind, &fileData) != 0); //Repeat until the last file in Student Files folder
    }
    printf("===================================================\n");
    FindClose(hFind);
}

void StudentSearch(char *StudentID) //Search specify student using NRIC
{
    printf("Enter student NRIC (e.g., T1234567G): ");
    scanf("%s", StudentID);  // No need for '&' since StudentID is already a character array (string)
    StudentID[0] = toupper(StudentID[0]);
    StudentID[8] = toupper(StudentID[8]); //Set both first and last letter of NRIC as capital
    FileDirectory(Filepath, sizeof(Filepath), StudentID); // Build full path to student file (e.g., T1234567G.txt)
    ptr = fopen(Filepath, "r"); //Open current student file to read all data
    if (ptr != NULL)
    {
        ReadStudentFile(ptr, &Data); // Read and display student details if file exists
        fclose(ptr);
        // Display result
        printf("Student: %s\n", Data.NRIC);
        printf("Name: %s\n", Data.Name);
        printf("Age: %d\n", Data.Age);
        printf("Gender: %s\n", Data.Gender);
        printf("Course: %s\n", Data.Course);
    }
    else
    {
        printf("Student info does not exist\n");
    }
}

void EditStudentInfo(char *StudentID, int Option, char *Courses[3]) // Allow user to choose what field to edit (Name, Age, or Course)
{
    printf("Enter student NRIC (e.g., T1234567G): ");
    scanf("%s", StudentID);  // No need for '&' since StudentID is already a character array (string)
    StudentID[0] = toupper(StudentID[0]);
    StudentID[8] = toupper(StudentID[8]); //Set both first and last letter of NRIC as capital
    FileDirectory(Filepath, sizeof(Filepath), StudentID); // Build full path to student file (e.g., T1234567G.txt)
    ptr = fopen(Filepath, "r");
    if (ptr == NULL)
    {
        printf("Student info does not exist\n");
    }
    else
    {
        ReadStudentFile(ptr, &Data); // Read student details if file exists
        fclose(ptr);

        printf("Select info:\n");
        printf("1. Name\n");
        printf("2. Age\n");
        printf("3. Course\n");
        Option = DecisionMaking("Option: ", 1, 3);
        switch (Option)
        {
        case 1: //Change student name
            printf("Enter new name: ");
            while (getchar() != '\n');  // Flush the newline character
            fgets(Data.Name, sizeof(Data.Name), stdin);
            Data.Name[strcspn(Data.Name, "\n")] = '\0';  // Strip newline
            break;
        case 2: //Change student age
            printf("Age: ");
            scanf("%d", &Data.Age);
            break;
        case 3: //Change student course
            printf("Change Course:\n");
            printf("1. Business Management\n");
            printf("2. Common Engineering\n");
            printf("3. Cyber Security\n");
            Option = DecisionMaking("Enter (1-3): ", 1, 3);
            strcpy(Data.Course, Courses[Option]); //Copy string of respective courses into Course variable
            break;
        default:
            break;
        }
        ptr = fopen(Filepath, "w");
        printf("Student info has been modified!\n");
        fprintf(ptr, "%s\n%s\n%d\n%s\n%s\n", Data.NRIC, Data.Name, Data.Age, Data.Gender, Data.Course); //Rewrite student data with new inputs
        fclose(ptr);
    }
}

void StudentCount() // Loop through all student files and count how many exist
{
    int Total = 0;
    hFind = FindFirstFileA(folderPath, &fileData);
    if (hFind == INVALID_HANDLE_VALUE) 
    {
        printf("No student found.\n");
        return;
    }
    else
    {
        do
        {
            snprintf(Filepath, sizeof(Filepath), Directory"%s", fileData.cFileName); //Convert printf filepath statement to string that contain current NRIC filename.txt
            ptr = fopen(Filepath, "r");
            if (ptr != NULL) //Check whether student file exist
            {
                Total++; //Whenever an student file is found, increase total students by 1
                fclose(ptr);
            }
        } while (FindNextFileA(hFind, &fileData) != 0); //Repeat until all student file are identify
        printf("Total students: %d\n", Total); //Display total number of students
    }
}

void DeleteStudentByID(char *StudentID, int Option) // Confirm deletion with user before removing the file
{
    printf("Enter student ID (E.g, T***1234G): ");
    scanf("%s", StudentID); // No need for '&' since StudentID is already a character array (string)
    StudentID[0] = toupper(StudentID[0]);
    StudentID[8] = toupper(StudentID[8]); //Set both first and last letter of NRIC as capital
    FileDirectory(Filepath, sizeof(Filepath), StudentID);
    ptr = fopen(Filepath, "r");
    if (ptr == NULL)
    {
        printf("Student does not exist!\n");
    }
    else
    {
        ReadStudentFile(ptr, &Data);
        fclose(ptr);
        printf("Confirm deletion of student %s:\n", Data.Name);
        printf("1. Delete\n2. Cancel\n");
        Option = DecisionMaking("Enter option (1/2): ", 1, 2);
        switch (Option)
        {
        case 1:
            ptr = fopen(Filepath, "w");
            fclose(ptr);
            if (remove(Filepath) == 0)
            {
                printf("Student deleted!"); //Show file is deleted
            }
            else
            {
                printf("Student does not exist!\n");
            }
            break;
        case 2: break;
        default:
            break;
        }
    }
}

void PromptToContinue(int Option, int *End) //Check with user whether they want to continue using Student Management System
{
    printf("\nDo you wish to continue?\n");
    printf("1. Continue\n");
    printf("2. Exit\n");
    Option = DecisionMaking("Option: ", 1, 2);
    if (Option == 2)
    {
        *End = 1;
    }
}

int DecisionMaking(const char *prompt, int min , int max) //Prompt user to make decision whenever system prompts an multiple choice question
{
    int input;
    do
    {
        printf("%s", prompt);
        scanf("%d", &input);
        if (input < min || input > max)
        {
            printf("Please enter options from %d to %d!\n", min, max);
        }
    } while (input < min || input > max); //Repeat user input whenever user does not choose the available options
    return input;
}

void FileDirectory(char *FilePath, size_t size, const char *FileName)
{
    snprintf(FilePath, size, Directory"%s.txt", FileName); //Convert printf filepath statement to string that contain current NRIC filename.txt
}

void ReadStudentFile(FILE *ptr, StudentDetails *data)
{
    char line[50]; // temporary buffer to read raw input from the file and convert or clean it before storing it in your Data struct
    // Read line 1: NRIC
    fgets(line, sizeof(line), ptr); // Read the line from the file into `line`
    sscanf(line, "%s", Data.NRIC); // Extract string from `line` into `Data.NRIC`
    // Read line 2: Name
    fgets(Data.Name, sizeof(Data.Name), ptr); // Directly read because we want spaces
    Data.Name[strcspn(Data.Name, "\n")] = '\0'; // Strip newline character
    // Read line 3: Age
    fgets(line, sizeof(line), ptr); // Read line into buffer
    sscanf(line, "%d", &Data.Age); // Convert string into integer
    // Read line 4: Gender
    fgets(Data.Gender, sizeof(Data.Gender), ptr);
    Data.Gender[strcspn(Data.Gender, "\n")] = '\0';
    //Read 5th line (Course)
    fgets(Data.Course, sizeof(Data.Course), ptr);
    Data.Course[strcspn(Data.Course, "\n")] = '\0'; // Remove newline
}

int main() {
    int Choice, Option, End = 0;
    char StudentID[20];
    char *Courses[] = {" ", "Business Management", "Common Engineering", "Cyber Security"}, *Gender[] = {" ", "Male", "Female"};
    while (End == 0)
    {
    DisplayMainMenu(&Choice);
    switch (Choice)
    {
    case 1: StudentRegistration(Option, Gender, Courses); break;
    case 2: StudentCourseList(Option, Courses); break;
    case 3: StudentSearch(StudentID); break;
    case 4: EditStudentInfo(StudentID, Option, Courses); break;
    case 5: StudentCount(); break;
    case 6: DeleteStudentByID(StudentID, Option); break;
    case 7: return 0; break;
    default:
        break;
    }
    PromptToContinue(Option, &End);
    }
    return 0;
}