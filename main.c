/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

// Function Declarations
void displayMainMenu();
void addPatient(char names[][50], int ages[], int phoneNumbers[], char medicalHistories[][200], int *patientCount);
void searchPatient(char names[][50], int ages[], int phoneNumbers[], char medicalHistories[][200], int patientCount);
void displayAllPatients(char names[][50], int ages[], int phoneNumbers[], char medicalHistories[][200], int patientCount);
void sortPatientsByName(char names[][50], int ages[], int phoneNumbers[], char medicalHistories[][200], int patientCount);

int main() {
    char names[MAX_PATIENTS][50];
    int ages[MAX_PATIENTS];
    int phoneNumbers[MAX_PATIENTS];
    char medicalHistories[MAX_PATIENTS][200];
    
    int patientCount = 0;
    int choice;

    do {
        displayMainMenu();
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            // In case user enters non-integer input
            while (getchar() != '\n'); 
            printf("Invalid choice! Please enter a number between 1 and 5.\n\n");
            continue;
        }

        switch (choice) {
            case 1:
                addPatient(names, ages, phoneNumbers, medicalHistories, &patientCount);
                break;
            case 2:
                searchPatient(names, ages, phoneNumbers, medicalHistories, patientCount);
                break;
            case 3:
                displayAllPatients(names, ages, phoneNumbers, medicalHistories, patientCount);
                break;
            case 4:
                sortPatientsByName(names, ages, phoneNumbers, medicalHistories, patientCount);
                break;
            case 5:
                printf("Exiting System. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please select between 1 and 5.\n\n");
        }
    } while (choice != 5);

    return 0;
}

// 1. Function to display the main menu
void displayMainMenu() {
    printf("=== DENTISTRY RECORD MANAGEMENT SYSTEM ===\n");
    printf("Please Select an Operation (1-5):\n");
    printf("1- Add New Patient\n");
    printf("2- Search for Patient\n");
    printf("3- Display All Patients\n");
    printf("4- Sort Patients by Name\n");
    printf("5- Exit System\n");
}

// 2. Function to add a new patient
void addPatient(char names[][50], int ages[], int phoneNumbers[], char medicalHistories[][200], int *patientCount) {
    if (*patientCount >= MAX_PATIENTS) {
        printf("System is full! Cannot add more patients.\n\n");
        return;
    }

    printf("\nAdd New Patient\n");

    // Clear input buffer before reading string with spaces
    while (getchar() != '\n');

    // Read Patient Name (allows spaces)
    printf("Enter Patient Name: ");
    fgets(names[*patientCount], 50, stdin);
    // Remove newline character at the end of string if present
    names[*patientCount][strcspn(names[*patientCount], "\n")] = '\0';

    // Read Age
    printf("Enter Age: ");
    scanf("%d", &ages[*patientCount]);

    // Read and Validate Phone Number (between 10000 and 9999999)
    int phone;
    do {
        printf("Enter Patient Number (5-7 digits): ");
        scanf("%d", &phone);
        if (phone < 10000 || phone > 9999999) {
            printf("Invalid phone number! Must be between 10000 and 9999999.\n");
        }
    } while (phone < 10000 || phone > 9999999);
    
    phoneNumbers[*patientCount] = phone;

    // Read Medical History (single word)
    printf("Enter Medical History (single word): ");
    scanf("%s", medicalHistories[*patientCount]);

    // Increase patient count
    (*patientCount)++;

    printf("Patient added successfully!\n\n");
}

// 3. Function to search for a patient by number
void searchPatient(char names[][50], int ages[], int phoneNumbers[], char medicalHistories[][200], int patientCount) {
    if (patientCount == 0) {
        printf("\nNot found!\n\n");
        return;
    }

    int searchNum;
    printf("\nEnter Patient Number to Search: ");
    scanf("%d", &searchNum);

    for (int i = 0; i < patientCount; i++) {
        if (phoneNumbers[i] == searchNum) {
            printf("Patient Found\n");
            printf("Name: %s\n", names[i]);
            printf("Age: %d\n", ages[i]);
            printf("Number: %d\n", phoneNumbers[i]);
            printf("Medical record: %s\n\n", medicalHistories[i]);
            return;
        }
    }

    printf("Not found!\n\n");
}

// 4. Function to display all patients
void displayAllPatients(char names[][50], int ages[], int phoneNumbers[], char medicalHistories[][200], int patientCount) {
    if (patientCount == 0) {
        printf("\nNo records found.\n\n");
        return;
    }

    printf("\n%-20s | %-5s | %-10s | %-15s\n", "Name", "Age", "Number", "Medical Record");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < patientCount; i++) {
        printf("%-20s | %-5d | %-10d | %-15s\n", names[i], ages[i], phoneNumbers[i], medicalHistories[i]);
    }
    printf("\n");
}

// 5. Function to sort patients alphabetically by name
void sortPatientsByName(char names[][50], int ages[], int phoneNumbers[], char medicalHistories[][200], int patientCount) {
    if (patientCount < 2) {
        printf("\nPatients sorted by name.\n\n");
        return;
    }

    // Bubble Sort algorithm
    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            if (strcmp(names[j], names[j + 1]) > 0) {
                
                // 1. Swap Names
                char tempName[50];
                strcpy(tempName, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], tempName);

                // 2. Swap Ages
                int tempAge = ages[j];
                ages[j] = ages[j + 1];
                ages[j + 1] = tempAge;

                // 3. Swap Phone Numbers
                int tempPhone = phoneNumbers[j];
                phoneNumbers[j] = phoneNumbers[j + 1];
                phoneNumbers[j + 1] = tempPhone;

                // 4. Swap Medical Histories
                char tempHistory[200];
                strcpy(tempHistory, medicalHistories[j]);
                strcpy(medicalHistories[j], medicalHistories[j + 1]);
                strcpy(medicalHistories[j + 1], tempHistory);
            }
        }
    }

    printf("\nPatients sorted by name.\n\n");
}