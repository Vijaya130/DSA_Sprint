#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Task {
    int id;
    char title[100];
    char status[20];
    struct Task* next;
};

struct Task* head = NULL;

void addTask() {
    struct Task* newTask = (struct Task*)malloc(sizeof(struct Task));
    struct Task* temp;

    printf("Enter Task ID: ");
    scanf("%d", &newTask->id);
    getchar();

    printf("Enter Task Title: ");
    fgets(newTask->title, sizeof(newTask->title), stdin);
    newTask->title[strcspn(newTask->title, "\n")] = '\0';

    strcpy(newTask->status, "Pending");

    newTask->next = NULL;

    if (head == NULL) {
        head = newTask;
    } else {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newTask;
    }

    printf("Task added successfully!\n");
}

void deleteTask() {
    int id;
    struct Task *temp = head, *prev = NULL;

    printf("Enter Task ID to delete: ");
    scanf("%d", &id);

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Task not found.\n");
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Task deleted successfully!\n");
}

void markTaskDone() {
    int id;
    struct Task* temp = head;

    printf("Enter Task ID to mark as completed: ");
    scanf("%d", &id);

    while (temp != NULL) {
        if (temp->id == id) {
            strcpy(temp->status, "Completed");
            printf("Task marked as completed.\n");
            return;
        }
        temp = temp->next;
    }

    printf("Task not found.\n");
}

void displayTasks() {
    struct Task* temp = head;

    if (head == NULL) {
        printf("No tasks available.\n");
        return;
    }

    printf("\n==== To-Do List ====\n");

    while (temp != NULL) {
        printf("Task ID: %d\n", temp->id);
        printf("Title: %s\n", temp->title);
        printf("Status: %s\n", temp->status);
        printf("-------------------\n");

        temp = temp->next;
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n==== To-Do List Menu ====\n");
        printf("1. Add Task\n");
        printf("2. Delete Task\n");
        printf("3. Mark Task as Done\n");
        printf("4. Display All Tasks\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                addTask();
                break;

            case 2:
                deleteTask();
                break;

            case 3:
                markTaskDone();
                break;

            case 4:
                displayTasks();
                break;

            case 5:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}