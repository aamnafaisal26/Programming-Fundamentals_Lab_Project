// BUDGET TRACKER - PF Semester 1
// Build: gcc -Wall budgetTracker.c -o budget.exe

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_EXPENSES   1000
#define MAX_DESC       50
#define NUM_CATEGORIES 8

struct Expense {
    int    id;
    int    day, month, year;
    int    category;            // 0..7
    double amount;
    char   description[MAX_DESC];
};

struct Settings {
    double monthlyIncome;
    double monthlyLimit;        // 0 = no limit
};

const char *CATEGORY_NAMES[NUM_CATEGORIES] = {
    "Food", "Transport", "Rent", "Utilities",
    "Entertainment", "Education", "Health", "Other"
};


//FILE

int loadExpensesFromFile(struct Expense list[]);
// Opens ExpenseFile.csv, skips the header line, reads every row into list.
// Returns how many were read. If the file does not exist, returns 0.

void saveExpensesToFile(struct Expense list[], int count);
// Opens ExpenseFile.csv for writing, writes the header line,
// then one comma-separated line per record.

void loadSettingsFromFile(struct Settings *s);
// Reads monthly income and limit from settings.csv.
// If the file does not exist, sets both to 0 and creates it.

void saveSettingsToFile(struct Settings *s);
// Writes the header line and the two numbers to settings.csv.

//FILE END


//INPUT

int inputWholeNumber(const char *prompt, int min, int max);
// Shows the prompt, reads the typed line, pulls out a whole number.
// Keeps asking until the number is between min and max.

double inputAmount(const char *prompt, double min);
// Same as above but for a decimal number, only a minimum (expenses use 1).

void inputText(const char *prompt, char string[], int size);
// Reads a whole line with spaces into string, removes the newline.
// Asks again if the line is empty.

int inputYesNo(const char *prompt);
// Returns 1 for y/Y, 0 for n/N, asks again for anything else.

void inputDate(int *day, int *month, int *year);
// Asks day, month, year using inputWholeNumber.
// Asks all three again until isDateReal returns 1.

int inputCategory(void);
// Shows the category list, asks for 1-8, returns the answer minus 1.

//INPUT END


//DATE

int isDateReal(int day, int month, int year);
// Returns 1 if the day exists in that month (leap year included),
// the year is 2000 or later, and the date is not after today.

void getTodayDate(int *day, int *month, int *year);
// Gets today's date from the system clock (month +1, year +1900).

int dateToNumber(int day, int month, int year);
// Returns year*10000 + month*100 + day, e.g. 20261108, so dates can be compared.

//DATE END


//ADD

int addExpense(struct Expense list[], int count, struct Settings *s);
// Stops if list is full. Fills one record using the input functions,
// adds it to list, saves the file, prints "Added", shows the budget warning.
// Returns the new count.

int generateNextId(struct Expense list[], int count);
// Returns the biggest id in list plus 1. Empty list gives 1.

void removeCommas(char string[]);
// Replaces every comma in string with a space so the CSV does not break.

void showCategoryList(void);
// Prints the 8 categories numbered 1 to 8.

double calculateMonthSpending(struct Expense list[], int count, int month, int year);
// Adds up the amounts of all records in that month and year.

void showBudgetWarning(struct Expense list[], int count, struct Settings *s, int month, int year);
// Compares that month's spending with the limit.
// Prints over budget, or careful at 80%, or a normal status. Silent if limit is 0.

//ADD END


//VIEW


//VIEW

double calculateTotal(struct Expense list[], int count)
{
    double total = 0;

    for (int i = 0; i < count; i++) {
        total += list[i].amount;
    }

    return total;
}

int findBiggestExpense(struct Expense list[], int count)
{
    if (count == 0)
        return -1;

    int biggest = 0;

    for (int i = 1; i < count; i++) {
        if (list[i].amount > list[biggest].amount)
            biggest = i;
    }

    return biggest;
}

void calculateCategoryTotals(struct Expense list[], int count, double totals[])
{
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        totals[i] = 0;
    }

    for (int i = 0; i < count; i++) {
        if (list[i].category >= 0 &&
            list[i].category < NUM_CATEGORIES) {
            totals[list[i].category] += list[i].amount;
        }
    }
}

int findBiggestCategory(struct Expense list[], int count)
{
    if (count == 0)
        return -1;

    double totals[NUM_CATEGORIES];

    calculateCategoryTotals(list, count, totals);

    int biggest = 0;

    for (int i = 1; i < NUM_CATEGORIES; i++) {
        if (totals[i] > totals[biggest])
            biggest = i;
    }

    return biggest;
}

int isBefore(struct Expense a, struct Expense b, int mode)
{
    if (mode == 1)
        return a.id < b.id;

    if (mode == 2)
        return dateToNumber(a.day, a.month, a.year) <
               dateToNumber(b.day, b.month, b.year);

    if (mode == 3)
        return a.amount > b.amount;

    return 0;
}

void sortExpenses(struct Expense list[], int count, int mode)
{
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {

            if (isBefore(list[j + 1], list[j], mode)) {
                struct Expense temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

void showExpenseTable(struct Expense list[], int count)
{
    printf("\n%-5s %-12s %-16s %-12s %-30s\n",
           "ID", "Date", "Category", "Amount", "Description");

    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-5d %02d/%02d/%-7d %-16s %-12.2f %-30.30s\n",
               list[i].id,
               list[i].day,
               list[i].month,
               list[i].year,
               CATEGORY_NAMES[list[i].category],
               list[i].amount,
               list[i].description);
    }

    printf("-------------------------------------------------------------------------------\n");
}

void showCategoryChart(struct Expense list[], int count)
{
    double totals[NUM_CATEGORIES];
    double total = calculateTotal(list, count);
    double biggest = 0;

    calculateCategoryTotals(list, count, totals);

    for (int i = 0; i < NUM_CATEGORIES; i++) {
        if (totals[i] > biggest)
            biggest = totals[i];
    }

    printf("\nCATEGORY SPENDING CHART\n");

    if (biggest == 0 || total == 0) {
        printf("No spending to display.\n");
        return;
    }

    for (int i = 0; i < NUM_CATEGORIES; i++) {
        if (totals[i] > 0) {
            int bars = (int)(totals[i] / biggest * 20);
            double percent = totals[i] / total * 100;

            printf("%-16s ", CATEGORY_NAMES[i]);

            for (int j = 0; j < bars; j++) {
                printf("#");
            }

            printf(" %.2f (%.1f%%)\n", totals[i], percent);
        }
    }
}

void showSummary(struct Expense list[], int count)
{
    if (count == 0) {
        printf("\nNo expenses to summarize.\n");
        return;
    }

    int day, month, year;

    getTodayDate(&day, &month, &year);

    double total = calculateTotal(list, count);
    double monthly = calculateMonthSpending(list, count, month, year);

    int biggestExpense = findBiggestExpense(list, count);
    int biggestCategory = findBiggestCategory(list, count);

    double totals[NUM_CATEGORIES];

    calculateCategoryTotals(list, count, totals);

    printf("\nEXPENSE SUMMARY\n");
    printf("Total spent: %.2f\n", total);
    printf("This month's spending: %.2f\n", monthly);

    if (biggestCategory != -1) {
        printf("Biggest category: %s (%.2f)\n",
               CATEGORY_NAMES[biggestCategory],
               totals[biggestCategory]);
    }

    if (biggestExpense != -1) {
        printf("Biggest single expense: %s (%.2f)\n",
               list[biggestExpense].description,
               list[biggestExpense].amount);
    }
}

void viewExpenses(struct Expense list[], int count)
{
    if (count == 0) {
        printf("\nNo expenses found.\n");
        return;
    }

    struct Expense copy[MAX_EXPENSES];

    for (int i = 0; i < count; i++) {
        copy[i] = list[i];
    }

    printf("\n1. Sort by ID");
    printf("\n2. Sort by Date");
    printf("\n3. Sort by Amount\n");

    int mode = inputWholeNumber("Choose sort order: ", 1, 3);

    sortExpenses(copy, count, mode);

    showExpenseTable(copy, count);
    showCategoryChart(copy, count);
    showSummary(copy, count);
}

//VIEW END



//SEARCH

void searchExpenses(struct Expense list[], int count);
// Asks 1 category / 2 month / 3 description, runs that search into a results
// array, shows the results. Total is shown only for a month search.

int searchByCategory(struct Expense list[], int count, struct Expense results[]);
// Asks a category, copies matching records into results, returns how many.

int searchByMonth(struct Expense list[], int count, struct Expense results[]);
// Asks month and year, then calls filterByMonth.

int filterByMonth(struct Expense list[], int count, int month, int year, struct Expense results[]);
// Copies records of that month into results, returns how many. Also used by Budget.

int searchByDescription(struct Expense list[], int count, struct Expense results[]);
// Asks a word, copies records whose description contains it, returns how many.

int containsIgnoreCase(const char text[], const char word[]);
// Returns 1 if word appears inside text, ignoring upper/lower case.

void showSearchResults(struct Expense results[], int found, int showTotal);
// Prints "nothing found", or the table of results, plus the total if showTotal is 1.

//SEARCH END


//EDIT

void editExpense(struct Expense list[], int count, struct Settings *s);
// Asks an id, finds it (-1 = not found, stop), shows it, asks which field
// to change (date / category / amount / description), changes it, saves, warns.

int findById(struct Expense list[], int count, int id);
// Returns the index of the record with that id, or -1 if none.

void showOneExpense(struct Expense e);
// Prints one record, each field on its own line.

//EDIT END



//DELETE

void removeAtIndex(struct Expense list[], int count, int index)
{
    for (int i = index; i < count - 1; i++) {
        list[i] = list[i + 1];
    }
}

int deleteExpense(struct Expense list[], int count)
{
    if (count == 0) {
        printf("\nNo expenses to delete.\n");
        return count;
    }

    int id = inputWholeNumber("Enter expense ID to delete: ", 1, 999999);
    int index = findById(list, count, id);

    if (index == -1) {
        printf("\nExpense not found.\n");
        return count;
    }

    printf("\nExpense found:\n");
    showOneExpense(list[index]);

    int confirm = inputYesNo("Are you sure you want to delete? (y/n): ");

    if (confirm == 0) {
        printf("\nDeletion cancelled.\n");
        return count;
    }

    removeAtIndex(list, count, index);

    count--;

    saveExpensesToFile(list, count);

    printf("\nExpense deleted successfully!\n");

    return count;
}

//DELETE END


//BUDGET

void showBudget(struct Expense list[], int count, struct Settings *s);
// Asks month and year. Prints income, spent, remaining, limit, status,
// and a category chart for that month only.

double calculateRemaining(struct Settings *s, double spent);
// Returns income minus spent.

void showBudgetStatus(double spent, struct Settings *s);
// Prints OK (green), CAREFUL at 80% (yellow), or OVER BUDGET (red).
// Prints "no limit set" if limit is 0.

//BUDGET END


//SETTINGS

void changeSettings(struct Settings *s);
// Shows settings, asks 1 income / 2 limit / 0 back, reads the new value, saves.

void showSettings(struct Settings *s);
// Prints monthly income and limit ("none" if 0).

//SETTINGS END


//MENU

void showMenu(void);
// Prints the title and options:
// 1 Add  2 View  3 Search  4 Edit  5 Delete  6 Budget  7 Settings  0 Exit

void clearScreen(void);
// system("cls")

void pauseScreen(void);
// Prints "Press Enter to continue" and waits for Enter.

int main(void);
// Loads both files. Loops: clearScreen, showMenu, read choice 0-7,
// call that option, pauseScreen. Add and Delete give back the new count.

//MENU END
