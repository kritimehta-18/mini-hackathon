#include <stdio.h>
#include <string.h>

#define MAX_EXPENSES 100
#define NUM_CATEGORIES 5


char categoryNames[5][15] = {
    "Food", "Transport", "Entertainment", "Bills", "Other"
};

char expDescription[100][30];
int expCategory[100];
float expAmount[100];
float categoryTotals[5] = {0};
int expenseCount = 0;


void recordExpense(char description[], int category, float amount) {
    if (expenseCount >= MAX_EXPENSES) {
        printf("Expense list is full!\n");
        return;
    }

    if (category < 0 || category >= NUM_CATEGORIES || amount <= 0) {
        printf("Invalid expense details!\n");
        return;
    }

    strcpy(expDescription[expenseCount], description);
    expCategory[expenseCount] = category;
    expAmount[expenseCount] = amount;
    expenseCount++;

    printf("Expense added successfully!\n");
}


void calculateCategoryTotals() {
    int i;

    for (i = 0; i < NUM_CATEGORIES; i++)
        categoryTotals[i] = 0;

    for (i = 0; i < expenseCount; i++)
        categoryTotals[expCategory[i]] += expAmount[i];
}


float calculateOverallTotal() {
    float total = 0;
    int i;

    for (i = 0; i < expenseCount; i++)
        total += expAmount[i];

    return total;
}


int findHighestCategory() {
    int i, highest = 0;

    if (expenseCount == 0)
        return -1;

    for (i = 1; i < NUM_CATEGORIES; i++) {
        if (categoryTotals[i] > categoryTotals[highest])
            highest = i;
    }

    return highest;
}


void checkBudget(float budget, float totalExpenses) {
    float remaining = budget - totalExpenses;

    printf("\n--- Budget Status ---\n");
    printf("Monthly Budget : Rs. %.2f\n", budget);
    printf("Total Expenses : Rs. %.2f\n", totalExpenses);
    printf("Remaining      : Rs. %.2f\n", remaining);

    if (totalExpenses > budget)
        printf("WARNING: Budget exceeded!\n");
    else if (totalExpenses == budget)
        printf("Your entire budget is used.\n");
    else
        printf("Your expenses are under control.\n");
}


void showReport(float budget, float expenses[], float totalSpent) {
    int i, highest = 0;

    printf("\n===== SmartSpend Report =====\n");

    if (totalSpent == 0) {
        printf("No expenses recorded yet.\n");
        checkBudget(budget, totalSpent);
        return;
    }

    for (i = 0; i < NUM_CATEGORIES; i++) {
        printf("%-15s: Rs. %.2f\n",
               categoryNames[i], expenses[i]);

        if (expenses[i] > expenses[highest])
            highest = i;
    }

    printf("-----------------------------\n");
    printf("Total Expenses : Rs. %.2f\n", totalSpent);
    printf("Highest Expense: %s (Rs. %.2f)\n",
           categoryNames[highest], expenses[highest]);

    checkBudget(budget, totalSpent);
}


int main() {
    float budget, amount, total;
    int choice = 0, category, i;
    char description[30];

    printf("===== Personal Expense Tracker =====\n");
    printf("Enter your monthly budget: ");
    scanf("%f", &budget);

    while (budget <= 0) {
        printf("Invalid budget! Enter again: ");
        scanf("%f", &budget);
    }

    printf("Budget set successfully: Rs. %.2f\n", budget);

    while (choice != 5) {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Add Expense\n");
        printf("2. View Category Totals\n");
        printf("3. View Report\n");
        printf("4. Check Budget Status\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter expense description: ");
                scanf("%29s", description);

                printf("\nSelect Category:\n");
                for (i = 0; i < NUM_CATEGORIES; i++)
                    printf("%d. %s\n", i + 1, categoryNames[i]);

                printf("Enter category number: ");
                scanf("%d", &category);

                printf("Enter amount: ");
                scanf("%f", &amount);

                recordExpense(description, category - 1, amount);
                break;

            case 2:
                calculateCategoryTotals();

                printf("\n--- Category Totals ---\n");
                for (i = 0; i < NUM_CATEGORIES; i++)
                    printf("%s: Rs. %.2f\n",
                           categoryNames[i], categoryTotals[i]);
                break;

            case 3:
                calculateCategoryTotals();
                total = calculateOverallTotal();
                showReport(budget, categoryTotals, total);
                break;

            case 4:
                total = calculateOverallTotal();
                checkBudget(budget, total);
                break;

            case 5:
                printf("Thank you for using SmartSpend!\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
