#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 100
#define DESCRIPTION_LENGTH 50
#define DATE_LENGTH 11

typedef struct {
    char description[DESCRIPTION_LENGTH];
    float amount;
    char date[DATE_LENGTH];
} Expense;

Expense expenses[MAX_EXPENSES];
int expenseCount = 0;

void loadExpenses();
void saveExpenses();
void addExpense();
void viewExpenses();
void deleteExpense();

int main() {
    loadExpenses();

    int choice;
    do {
        printf("\nExpense Tracker Menu:\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Delete Expense\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                viewExpenses();
                break;
            case 3:
                deleteExpense();
                break;
            case 4:
                saveExpenses();
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

void loadExpenses() {
    FILE *file = fopen("expenses.txt", "r");
    if (file) {
        while (fscanf(file, "%49[^,],%f,%10s\n", expenses[expenseCount].description, &expenses[expenseCount].amount, expenses[expenseCount].date) != EOF) {
            expenseCount++;
        }
        fclose(file);
    }
}

void saveExpenses() {
	int i;
    FILE *file = fopen("expenses.txt", "w");
    for ( i = 0; i < expenseCount; i++) {
        fprintf(file, "%s,%.2f,%s\n", expenses[i].description, expenses[i].amount, expenses[i].date);
    }
    fclose(file);
}

void addExpense() {
    if (expenseCount >= MAX_EXPENSES) {
        printf("Expense limit reached. Cannot add more expenses.\n");
        return;
    }

    printf("Enter description: ");
    scanf(" %[^\n]s", expenses[expenseCount].description);
    printf("Enter amount: ");
    scanf("%f", &expenses[expenseCount].amount);
    printf("Enter date (YYYY-MM-DD): ");
    scanf("%10s", expenses[expenseCount].date);
    
    expenseCount++;
    printf("Expense added successfully.\n");
}

void viewExpenses() {
	int i;
    if (expenseCount == 0) {
        printf("No expenses recorded.\n");
        return;
    }

    printf("\nExpenses:\n");
    for (i = 0; i < expenseCount; i++) {
        printf("%d. %s: $%.2f on %s\n", i + 1, expenses[i].description, expenses[i].amount, expenses[i].date);
    }
}

void deleteExpense() {
    int index,i;
    printf("Enter the index of the expense to delete: ");
    scanf("%d", &index);
    
    if (index < 1 || index > expenseCount) {
        printf("Invalid index.\n");
        return;
    }

    for ( i = index - 1; i < expenseCount - 1; i++) {
        expenses[i] = expenses[i + 1];
    }
    expenseCount--;
    printf("Expense deleted successfully.\n");
}

