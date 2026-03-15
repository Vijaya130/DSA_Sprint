#include <stdio.h>
#include <string.h>

#define MAX 10
#define INF 99999

char cities[MAX][50];
int graph[MAX][MAX];
int cityCount = 0;

int getCityIndex(char name[]) {
    for (int i = 0; i < cityCount; i++) {
        if (strcmp(cities[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

void addCity() {
    if (cityCount >= MAX) {
        printf("Maximum city limit reached.\n");
        return;
    }

    printf("Enter city name: ");
    getchar();
    fgets(cities[cityCount], sizeof(cities[cityCount]), stdin);
    cities[cityCount][strcspn(cities[cityCount], "\n")] = '\0';

    cityCount++;
    printf("City added successfully.\n");
}

void addRoad() {
    char city1[50], city2[50];
    int distance;

    printf("Enter first city name: ");
    getchar();
    fgets(city1, sizeof(city1), stdin);
    city1[strcspn(city1, "\n")] = '\0';

    printf("Enter second city name: ");
    fgets(city2, sizeof(city2), stdin);
    city2[strcspn(city2, "\n")] = '\0';

    printf("Enter distance between them: ");
    scanf("%d", &distance);

    int i = getCityIndex(city1);
    int j = getCityIndex(city2);

    if (i == -1 || j == -1) {
        printf("One or both cities not found.\n");
        return;
    }

    graph[i][j] = distance;
    graph[j][i] = distance;

    printf("Road added successfully.\n");
}

void displayMap() {
    if (cityCount == 0) {
        printf("No cities added yet.\n");
        return;
    }

    printf("\nCity Map (Adjacency Matrix):\n\n");

    printf("%15s", "");
    for (int i = 0; i < cityCount; i++) {
        printf("%15s", cities[i]);
    }
    printf("\n");

    for (int i = 0; i < cityCount; i++) {
        printf("%15s", cities[i]);
        for (int j = 0; j < cityCount; j++) {
            if (graph[i][j] == INF)
                printf("%15s", "INF");
            else
                printf("%15d", graph[i][j]);
        }
        printf("\n");
    }
}

void shortestPath() {
    char sourceName[50], destName[50];
    int dist[MAX], visited[MAX], parent[MAX];

    printf("Enter source city: ");
    getchar();
    fgets(sourceName, sizeof(sourceName), stdin);
    sourceName[strcspn(sourceName, "\n")] = '\0';

    printf("Enter destination city: ");
    fgets(destName, sizeof(destName), stdin);
    destName[strcspn(destName, "\n")] = '\0';

    int source = getCityIndex(sourceName);
    int dest = getCityIndex(destName);

    if (source == -1 || dest == -1) {
        printf("One or both cities not found.\n");
        return;
    }

    for (int i = 0; i < cityCount; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[source] = 0;

    for (int count = 0; count < cityCount - 1; count++) {
        int min = INF, u = -1;

        for (int i = 0; i < cityCount; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < cityCount; v++) {
            if (!visited[v] && graph[u][v] != INF &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[dest] == INF) {
        printf("No path exists between %s and %s.\n", sourceName, destName);
        return;
    }

    printf("Shortest distance from %s to %s = %d\n", sourceName, destName, dist[dest]);
}

int main() {
    int choice;

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = INF;
        }
    }

    while (1) {
        printf("\n===== City Navigation System =====\n");
        printf("1. Add City\n");
        printf("2. Add Road\n");
        printf("3. Display City Map\n");
        printf("4. Find Shortest Path\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCity();
                break;
            case 2:
                addRoad();
                break;
            case 3:
                displayMap();
                break;
            case 4:
                shortestPath();
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}