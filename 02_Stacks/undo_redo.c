#include <stdio.h>
#include <string.h>

#define MAX_TEXT 100
#define MAX_STACK 50

typedef struct {
    char states[MAX_STACK][MAX_TEXT];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

void push(Stack *s, char text[]) {
    if (s->top < MAX_STACK - 1) {
        s->top++;
        strcpy(s->states[s->top], text);
    }
}

void pop(Stack *s, char text[]) {
    if (s->top >= 0) {
        strcpy(text, s->states[s->top]);
        s->top--;
    }
}

int main() {

    Stack undoStack, redoStack;
    initStack(&undoStack);
    initStack(&redoStack);

    char text[MAX_TEXT] = "";
    char input[MAX_TEXT];

    int choice;

    push(&undoStack, text);

    while (1) {

        printf("\nCurrent Text: \"%s\"\n", text);

        printf("1. Type/Add text\n");
        printf("2. Undo\n");
        printf("3. Redo\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {

            printf("Enter text: ");
            fgets(input, MAX_TEXT, stdin);
            input[strcspn(input,"\n")] = 0;

            push(&undoStack, text);

            strcat(text, input);

        }

        else if (choice == 2) {

            if (undoStack.top >= 0) {

                push(&redoStack, text);

                pop(&undoStack, text);

            } else {

                printf("Nothing to undo\n");

            }

        }

        else if (choice == 3) {

            if (redoStack.top >= 0) {

                push(&undoStack, text);

                pop(&redoStack, text);

            } else {

                printf("Nothing to redo\n");

            }

        }

        else if (choice == 4) {

            break;

        }

    }

    return 0;
}