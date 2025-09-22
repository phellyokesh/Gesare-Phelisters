#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_NAME_LEN 50
#define MAX_RATINGS 100

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int ratings[MAX_RATINGS];
    int ratingCount;
} FoodItem;

FoodItem items[MAX_ITEMS];
int itemCount = 0;
int nextId = 1;

void addItem() {
    if (itemCount >= MAX_ITEMS) {
        printf("Item list is full!\n");
        return;
    }
    printf("Enter food name: ");
    getchar(); // clear leftover newline
    fgets(items[itemCount].name, MAX_NAME_LEN, stdin);
    items[itemCount].name[strcspn(items[itemCount].name, "\n")] = 0; // remove newline
    items[itemCount].id = nextId++;
    items[itemCount].ratingCount = 0;
    itemCount++;
    printf("Food item added with ID %d.\n", items[itemCount-1].id);
}

FoodItem* findItemById(int id) {
    for (int i = 0; i < itemCount; i++) {
        if (items[i].id == id) return &items[i];
    }
    return NULL;
}

void rateItem() {
    int id, rating;
    printf("Enter item ID: ");
    scanf("%d", &id);
    FoodItem* f = findItemById(id);
    if (!f) {
        printf("Item not found!\n");
        return;
    }
    if (f->ratingCount >= MAX_RATINGS) {
        printf("Too many ratings for this item.\n");
        return;
    }
    printf("Enter rating (1-5): ");
    scanf("%d", &rating);
    if (rating < 1 || rating > 5) {
        printf("Invalid rating!\n");
        return;
    }
    f->ratings[f->ratingCount++] = rating;
    printf("Rating recorded.\n");
}

double averageRating(FoodItem* f) {
    if (f->ratingCount == 0) return 0.0;
    int sum = 0;
    for (int i = 0; i < f->ratingCount; i++) sum += f->ratings[i];
    return (double)sum / f->ratingCount;
}

void showItem() {
    int id;
    printf("Enter item ID: ");
    scanf("%d", &id);
    FoodItem* f = findItemById(id);
    if (!f) {
        printf("Item not found!\n");
        return;
    }
    printf("ID: %d\nName: %s\nAverage Rating: %.2f (%d ratings)\n",
           f->id, f->name, averageRating(f), f->ratingCount);
    if (f->ratingCount > 0) {
        printf("Ratings: ");
        for (int i = 0; i < f->ratingCount; i++) {
            printf("%d ", f->ratings[i]);
        }
        printf("\n");
    }
}

void listItems() {
    if (itemCount == 0) {
        printf("No items yet.\n");
        return;
    }
    printf("\n%-5s %-20s %-10s %-10s\n", "ID", "Name", "Avg", "Count");
    printf("---------------------------------------------\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%-5d %-20s %-10.2f %-10d\n", 
            items[i].id, items[i].name, averageRating(&items[i]), items[i].ratingCount);
    }
}

void saveToFile() {
    FILE* f = fopen("ratings.txt", "w");
    if (!f) {
        printf("Failed to save.\n");
        return;
    }
    for (int i = 0; i < itemCount; i++) {
        fprintf(f, "%d|%s|", items[i].id, items[i].name);
        for (int j = 0; j < items[i].ratingCount; j++) {
            fprintf(f, "%d", items[i].ratings[j]);
            if (j < items[i].ratingCount - 1) fprintf(f, ",");
        }
        fprintf(f, "\n");
    }
    fclose(f);
    printf("Data saved.\n");
}

void loadFromFile() {
    FILE* f = fopen("ratings.txt", "r");
    if (!f) {
        printf("No file to load.\n");
        return;
    }
    itemCount = 0;
    nextId = 1;
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        FoodItem fi;
        fi.ratingCount = 0;
        char* idStr = strtok(line, "|");
        char* nameStr = strtok(NULL, "|");
        char* ratingsStr = strtok(NULL, "\n");
        if (!idStr || !nameStr) continue;
        fi.id = atoi(idStr);
        strncpy(fi.name, nameStr, MAX_NAME_LEN);
        fi.name[MAX_NAME_LEN - 1] = '\0';
        if (ratingsStr) {
            char* token = strtok(ratingsStr, ",");
            while (token && fi.ratingCount < MAX_RATINGS) {
                fi.ratings[fi.ratingCount++] = atoi(token);
                token = strtok(NULL, ",");
            }
        }
        items[itemCount++] = fi;
        if (fi.id >= nextId) nextId = fi.id + 1;
    }
    fclose(f);
    printf("Data loaded.\n");
}

void menu() {
    printf("\n--- Food Rating System ---\n");
    printf("1) Add new food item\n");
    printf("2) Rate an item\n");
    printf("3) Show item details\n");
    printf("4) List all items\n");
    printf("5) Save to file\n");
    printf("6) Load from file\n");
    printf("0) Exit\n");
    printf("Choose option: ");
}

int main() {
    int choice;
    loadFromFile(); // auto load if file exists
    while (1) {
        menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: addItem(); break;
            case 2: rateItem(); break;
            case 3: showItem(); break;
            case 4: listItems(); break;
            case 5: saveToFile(); break;
            case 6: loadFromFile(); break;
            case 0: 
                saveToFile();
                printf("Goodbye!\n");
                exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
