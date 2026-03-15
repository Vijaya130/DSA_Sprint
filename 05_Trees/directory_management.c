#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 10

struct Node {
    char name[50];
    char type[10]; // file or folder
    struct Node* children[MAX_CHILDREN];
    int childCount;
};

struct Node* createNode(char name[], char type[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    strcpy(newNode->type, type);
    newNode->childCount = 0;

    for (int i = 0; i < MAX_CHILDREN; i++) {
        newNode->children[i] = NULL;
    }

    return newNode;
}

void addNode(struct Node* parent, char name[], char type[]) {
    if (parent->childCount >= MAX_CHILDREN) {
        printf("Cannot add more children to %s\n", parent->name);
        return;
    }

    struct Node* newNode = createNode(name, type);
    parent->children[parent->childCount++] = newNode;
    printf("%s added under %s successfully.\n", name, parent->name);
}

void displayTree(struct Node* root, int level) {
    if (root == NULL) return;

    for (int i = 0; i < level; i++) {
        printf("   ");
    }

    printf("|-- %s (%s)\n", root->name, root->type);

    for (int i = 0; i < root->childCount; i++) {
        displayTree(root->children[i], level + 1);
    }
}

struct Node* searchNode(struct Node* root, char name[]) {
    if (root == NULL) return NULL;

    if (strcmp(root->name, name) == 0) {
        return root;
    }

    for (int i = 0; i < root->childCount; i++) {
        struct Node* found = searchNode(root->children[i], name);
        if (found != NULL) {
            return found;
        }
    }

    return NULL;
}

void deleteNode(struct Node* parent, char name[]) {
    if (parent == NULL) return;

    for (int i = 0; i < parent->childCount; i++) {
        if (strcmp(parent->children[i]->name, name) == 0) {
            free(parent->children[i]);

            for (int j = i; j < parent->childCount - 1; j++) {
                parent->children[j] = parent->children[j + 1];
            }

            parent->children[parent->childCount - 1] = NULL;
            parent->childCount--;

            printf("%s deleted successfully.\n", name);
            return;
        }
    }

    for (int i = 0; i < parent->childCount; i++) {
        deleteNode(parent->children[i], name);
    }
}

int main() {
    struct Node* root = createNode("Root", "folder");
    int choice;
    char parentName[50], name[50], type[10];
    struct Node* parent;

    while (1) {
        printf("\n===== Directory Management System =====\n");
        printf("1. Add File/Folder\n");
        printf("2. Display Directory Structure\n");
        printf("3. Search File/Folder\n");
        printf("4. Delete File/Folder\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter parent folder name: ");
                fgets(parentName, sizeof(parentName), stdin);
                parentName[strcspn(parentName, "\n")] = '\0';

                parent = searchNode(root, parentName);
                if (parent == NULL) {
                    printf("Parent folder not found.\n");
                    break;
                }

                printf("Enter new file/folder name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                printf("Enter type (file/folder): ");
                fgets(type, sizeof(type), stdin);
                type[strcspn(type, "\n")] = '\0';

                addNode(parent, name, type);
                break;

            case 2:
                printf("\nDirectory Structure:\n");
                displayTree(root, 0);
                break;

            case 3:
                printf("Enter file/folder name to search: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                if (searchNode(root, name) != NULL) {
                    printf("%s found in the directory.\n", name);
                } else {
                    printf("%s not found.\n", name);
                }
                break;

            case 4:
                printf("Enter file/folder name to delete: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                if (strcmp(name, "Root") == 0) {
                    printf("Root cannot be deleted.\n");
                } else {
                    deleteNode(root, name);
                }
                break;

            case 5:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
