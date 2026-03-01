#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

typedef struct {
    int patientID;
    char name[50];
    int age;
    char disease[50];
    char doctor[50];
} Patient;

void addPatient(Patient patients[], int *count) {
    if (*count >= MAX_PATIENTS) {
        printf("\n Patient list is full!\n");
        return;
    }

    Patient p;

    printf("\nEnter Patient ID: ");
    scanf("%d", &p.patientID);

    // Check unique ID
    for (int i = 0; i < *count; i++) {
        if (patients[i].patientID == p.patientID) {
            printf("\n Patient ID already exists. Try a unique ID.\n");
            return;
        }
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", p.name);

    printf("Enter Age: ");
    scanf("%d", &p.age);

    printf("Enter Disease/Diagnosis: ");
    scanf(" %[^\n]", p.disease);

    printf("Enter Doctor Assigned: ");
    scanf(" %[^\n]", p.doctor);

    patients[*count] = p;
    (*count)++;

    printf("\n Patient record added successfully!\n");
}

void deletePatient(Patient patients[], int *count) {
    if (*count == 0) {
        printf("\n No patient records to delete.\n");
        return;
    }

    int id;
    printf("\nEnter Patient ID to delete: ");
    scanf("%d", &id);

    int foundIndex = -1;
    for (int i = 0; i < *count; i++) {
        if (patients[i].patientID == id) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("\n Patient with ID %d not found.\n", id);
        return;
    }

    // Shift left to delete
    for (int i = foundIndex; i < *count - 1; i++) {
        patients[i] = patients[i + 1];
    }
    (*count)--;

    printf("\n Patient record deleted successfully!\n");
}

void displayPatients(Patient patients[], int count) {
    if (count == 0) {
        printf("\n No patient records available.\n");
        return;
    }

    printf("\n========== ALL PATIENT RECORDS ==========\n");
    for (int i = 0; i < count; i++) {
        printf("\nPatient %d:\n", i + 1);
        printf("Patient ID      : %d\n", patients[i].patientID);
        printf("Name            : %s\n", patients[i].name);
        printf("Age             : %d\n", patients[i].age);
        printf("Disease/Diagnosis: %s\n", patients[i].disease);
        printf("Doctor Assigned : %s\n", patients[i].doctor);
    }
    printf("\n=========================================\n");
}

int main() {
    Patient patients[MAX_PATIENTS];
    int count = 0;
    int choice;

    while (1) {
        printf("\n\n===== HOSPITAL PATIENT RECORD SYSTEM =====");
        printf("\n1. Add New Patient Record");
        printf("\n2. Delete Patient Record (by ID)");
        printf("\n3. Display All Patient Records");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPatient(patients, &count);
                break;
            case 2:
                deletePatient(patients, &count);
                break;
            case 3:
                displayPatients(patients, count);
                break;
            case 4:
                printf("\n Exiting... Bye!\n");
                return 0;
            default:
                printf("\n Invalid choice. Try again.\n");
        }
    }
}
