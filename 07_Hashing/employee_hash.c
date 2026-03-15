#include <stdio.h>
#include <string.h>

#define SIZE 10

struct Employee {
    int id;
    char name[50];
    char department[50];
};

struct Employee hashTable[SIZE];
int occupied[SIZE] = {0};

int hashFunction(int id) {
    return id % SIZE;
}

void insertEmployee() {
    struct Employee emp;
    
    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    
    printf("Enter Name: ");
    scanf("%s", emp.name);
    
    printf("Enter Department: ");
    scanf("%s", emp.department);

    int index = hashFunction(emp.id);

    while (occupied[index]) {
        index = (index + 1) % SIZE;
    }

    hashTable[index] = emp;
    occupied[index] = 1;

    printf("Employee added successfully.\n");
}

void searchEmployee() {
    int id;
    printf("Enter Employee ID to search: ");
    scanf("%d", &id);

    int index = hashFunction(id);
    int start = index;

    while (occupied[index]) {
        if (hashTable[index].id == id) {
            printf("Employee Found:\n");
            printf("ID: %d\n", hashTable[index].id);
            printf("Name: %s\n", hashTable[index].name);
            printf("Department: %s\n", hashTable[index].department);
            return;
        }
        index = (index + 1) % SIZE;

        if (index == start)
            break;
    }

    printf("Employee not found.\n");
}

void deleteEmployee() {
    int id;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    int index = hashFunction(id);
    int start = index;

    while (occupied[index]) {
        if (hashTable[index].id == id) {
            occupied[index] = 0;
            printf("Employee deleted successfully.\n");
            return;
        }

        index = (index + 1) % SIZE;

        if (index == start)
            break;
    }

    printf("Employee not found.\n");
}

void displayEmployees() {
    printf("\nEmployee Records:\n");

    for (int i = 0; i < SIZE; i++) {
        if (occupied[i]) {
            printf("Index %d -> ID: %d | Name: %s | Dept: %s\n",
                   i,
                   hashTable[i].id,
                   hashTable[i].name,
                   hashTable[i].department);
        }
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n===== Employee Database (Hash Table) =====\n");
        printf("1. Insert Employee\n");
        printf("2. Search Employee\n");
        printf("3. Delete Employee\n");
        printf("4. Display Employees\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertEmployee();
                break;

            case 2:
                searchEmployee();
                break;

            case 3:
                deleteEmployee();
                break;

            case 4:
                displayEmployees();
                break;

            case 5:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}