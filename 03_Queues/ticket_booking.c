#include <stdio.h>
#include <string.h>

#define MAX 100

struct Customer {
    int customerID;
    char name[50];
    int ticketsRequired;
};

struct Customer queue[MAX];
int front = -1, rear = -1;
int isFull() {
    return rear == MAX - 1;
}

int isEmpty() {
    return front == -1 || front > rear;
}

void enqueue() {
    if (isFull()) {
        printf("\nQueue is full.\n");
        return;
    }

    struct Customer c;

    printf("\nEnter Customer ID: ");
    scanf("%d", &c.customerID);
    getchar();

    printf("Enter Customer Name: ");
    fgets(c.name, sizeof(c.name), stdin);
    c.name[strcspn(c.name, "\n")] = '\0';

    printf("Enter Tickets Required: ");
    scanf("%d", &c.ticketsRequired);

    if (front == -1)
        front = 0;

    rear++;
    queue[rear] = c;

    printf("\nCustomer added to queue.\n");
}

void dequeue() {
    if (isEmpty()) {
        printf("\nQueue empty.\n");
        return;
    }

    struct Customer served = queue[front];

    printf("\nServing Customer:\n");
    printf("ID: %d\n", served.customerID);
    printf("Name: %s\n", served.name);
    printf("Tickets: %d\n", served.ticketsRequired);

    front++;

    if (front > rear)
        front = rear = -1;
}

void displayQueue() {
    if (isEmpty()) {
        printf("\nQueue empty.\n");
        return;
    }

    printf("\nCustomers waiting:\n");

    for (int i = front; i <= rear; i++) {
        printf("\nCustomer ID: %d\n", queue[i].customerID);
        printf("Name: %s\n", queue[i].name);
        printf("Tickets: %d\n", queue[i].ticketsRequired);
    }
}

int main() {

    int choice;

    while (1) {

        printf("\n===== Ticket Booking System =====\n");
        printf("1. Add Customer\n");
        printf("2. Serve Customer\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice) {

            case 1:
                enqueue();
                break;

            case 2:
                dequeue();
                break;

            case 3:
                displayQueue();
                break;

            case 4:
                return 0;

            default:
                printf("\nInvalid choice\n");
        }
    }
}