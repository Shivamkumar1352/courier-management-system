#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000
#define FILE_NAME "courier_data.txt"

struct Courier {
    char id[20];
    char name[50];
    char address[100];
    char phone[20];
};

void insertCourier() {
    FILE* fp;
    struct Courier courier;

    fp = fopen(FILE_NAME, "a");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("Enter courier id: ");
    scanf("%s", courier.id);
    printf("Enter courier name: ");
    scanf("%s", courier.name);
    printf("Enter courier address: ");
    scanf("%s", courier.address);
    printf("Enter courier phone: ");
    scanf("%s", courier.phone);

    fwrite(&courier, sizeof(struct Courier), 1, fp);
    fclose(fp);
}

void displayCourier() {
    FILE* fp;
    struct Courier courier;

    fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("%-20s %-20s %-30s %-20s\n", "Courier ID", "Name", "Address", "Phone");
    while (fread(&courier, sizeof(struct Courier), 1, fp)) {
        printf("%-20s %-20s %-30s %-20s\n", courier.id, courier.name, courier.address, courier.phone);
    }

    fclose(fp);
}

void searchCourier() {
    FILE* fp;
    struct Courier courier;
    char id[20];
    int found = 0;

    fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("Enter courier id to search: ");
    scanf("%s", id);

    while (fread(&courier, sizeof(struct Courier), 1, fp)) {
        if (strcmp(courier.id, id) == 0) {
            printf("%-20s %-20s %-30s %-20s\n", "Courier ID", "Name", "Address", "Phone");
            printf("%-20s %-20s %-30s %-20s\n", courier.id, courier.name, courier.address, courier.phone);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Courier with id %s not found\n", id);
    }

    fclose(fp);
}

void deleteUpdateCourier() {
    FILE* fp;
    FILE* temp;
    struct Courier courier;
    char id[20];
    int found = 0;
    int choice;

    fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error creating temp file\n");
        fclose(fp);
        return;
    }

    printf("Enter courier id to delete/update: ");
    scanf("%s", id);

    while (fread(&courier, sizeof(struct Courier), 1, fp)) {
        if (strcmp(courier.id, id) == 0) {
            found = 1;
            printf("1. Delete courier\n");
            printf("2. Update courier\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
                        switch(choice) {
                case 1:
                    // Delete courier
                    printf("Courier with id %s will be deleted\n", courier.id);
                    break;
                case 2:
                    // Update courier
                    printf("Courier with id %s will be updated\n", courier.id);
                    printf("Enter courier name (or '-' to keep existing value): ");
                    scanf("%s", courier.name);
                    printf("Enter courier address (or '-' to keep existing value): ");
                    scanf("%s", courier.address);
                    printf("Enter courier phone (or '-' to keep existing value): ");
                    scanf("%s", courier.phone);
                    break;
                default:
                    printf("Invalid choice\n");
                    break;
            }
        } else {
            fwrite(&courier, sizeof(struct Courier), 1, temp);
        }
    }

    if (!found) {
        printf("Courier with id %s not found\n", id);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
}

void sortCourier() {
    FILE* fp;
    struct Courier couriers[MAX_SIZE];
    struct Courier temp;
    int i, j, n = 0;

    fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    while (fread(&couriers[n], sizeof(struct Courier), 1, fp)) {
        n++;
    }

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (strcmp(couriers[i].id, couriers[j].id) > 0) {
                temp = couriers[i];
                couriers[i] = couriers[j];
                couriers[j] = temp;
            }
        }
    }

    fclose(fp);

    fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    for (i = 0; i < n; i++) {
        fwrite(&couriers[i], sizeof(struct Courier), 1, fp);
    }

    fclose(fp);

    printf("Courier data sorted by ID\n");
}

int main() {
    int choice;

    while (1) {
        printf("\nCourier Management System\n");
        printf("1. Insert courier\n");
        printf("2. Display all couriers\n");
        printf("3. Search courier\n");
        printf("4. Delete/update courier\n");
        printf("5. Sort couriers by ID\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                insertCourier();
                break;
            case 2:
                displayCourier();
                break;
            case 3:
                searchCourier();
                break;
            case 4:
                deleteUpdateCourier();
                break;
            case 5:
                sortCourier();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}

