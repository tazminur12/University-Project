#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    float value;
} Record;

void addRecord(Record **records, int *size) {
    *records = realloc(*records, (*size + 1) * sizeof(Record));
    if (*records == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &(*records)[*size].id);
    printf("Enter Name: ");
    getchar();  
    fgets((*records)[*size].name, 50, stdin);
    (*records)[*size].name[strcspn((*records)[*size].name, "\n")] = '\0'; 
    printf("Enter Value (e.g., GPA): ");
    scanf("%f", &(*records)[*size].value);

    (*size)++;
    printf("Record added successfully.\n");
}

void displayRecords(Record *records, int size) {
    printf("\n--- All Records ---\n");
    for (int i = 0; i < size; i++) {
        printf("ID: %d | Name: %s | Value: %.2f\n", records[i].id, records[i].name, records[i].value);
    }
}


void updateRecord(Record *records, int size) {
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < size; i++) {
        if (records[i].id == id) {
            printf("Enter new Name: ");
            getchar();
            fgets(records[i].name, 50, stdin);
            records[i].name[strcspn(records[i].name, "\n")] = '\0';
            printf("Enter new Value: ");
            scanf("%f", &records[i].value);
            printf("Record updated successfully.\n");
            return;
        }
    }
    printf("Record with ID %d not found.\n", id);
}


void deleteRecord(Record **records, int *size) {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *size; i++) {
        if ((*records)[i].id == id) {
            for (int j = i; j < *size - 1; j++) {
                (*records)[j] = (*records)[j + 1];
            }
            *records = realloc(*records, (*size - 1) * sizeof(Record));
            (*size)--;
            printf("Record deleted successfully.\n");
            return;
        }
    }
    printf("Record with ID %d not found.\n", id);
}


void searchRecord(Record *records, int size) {
    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < size; i++) {
        if (records[i].id == id) {
            printf("ID: %d | Name: %s | Value: %.2f\n", records[i].id, records[i].name, records[i].value);
            return;
        }
    }
    printf("Record with ID %d not found.\n", id);
}


int main() {
    Record *records = NULL;
    int size = 0, choice;

    do {
        printf("\n====== CRUD Menu ======\n");
        printf("1. Add Record\n");
        printf("2. Display Records\n");
        printf("3. Update Record\n");
        printf("4. Delete Record\n");
        printf("5. Search Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addRecord(&records, &size); break;
            case 2: displayRecords(records, size); break;
            case 3: updateRecord(records, size); break;
            case 4: deleteRecord(&records, &size); break;
            case 5: searchRecord(records, size); break;
            case 6: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 6);

    free(records); 
    return 0;
}
